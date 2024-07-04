#ifdef MC_PLATFORM_LINUX

#include "MaineCoon/Core/Input/Input.h"
#include "mcpch.h"

#include "MaineCoon/Core/Application.h"
#include "MaineCoon/Math/Math.h"
#include <SDL.h>

namespace MaineCoon {

bool Input::IsKeyPressed(const KeyCode key)
{
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    SDL_Scancode sdlKey = static_cast<SDL_Scancode>(key);
    return keyState[sdlKey] == 1;
}

bool Input::IsMouseButtonPressed(const MouseCode button)
{
    Uint32 buttons = SDL_GetMouseState(NULL, NULL);
    return (buttons & SDL_BUTTON(static_cast<int>(button))) != 0;
}

// glm::vec2 Input::GetMouseScroll()
// {
//     int x, y;
//     // SDL_GetMouse;
//     return { static_cast<float>(x), static_cast<float>(y) };
// }

glm::vec2 Input::GetMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return { static_cast<float>(x), static_cast<float>(y) };
}

float Input::GetMouseX()
{
    return GetMousePosition().x;
}

float Input::GetMouseY()
{
    return GetMousePosition().y;
}

// Controller
int Input::GetNumOfGamepads()
{
    return SDL_NumJoysticks();
}

float Input::GetGamepadAxis(int index, GamepadAxis axis)
{
    float result = 0.0f;

    if (!Input::Get()->gamepads[index].SDL_Gamepad)
        return result;

    if (Input::Get()->gamepads[index].isGamepad) {
        result = SDL_GameControllerGetAxis((SDL_GameController*)Input::Get()->gamepads[index].SDL_Gamepad, static_cast<SDL_GameControllerAxis>(axis));
    } else {
        result = SDL_JoystickGetAxis((SDL_Joystick*)Input::Get()->gamepads[index].SDL_Gamepad, axis);
    }

    // Dividing to clamp it to be between -1 and 1
    result /= 32767.0f;

    if (Math::Abs(result) >= Input::Get()->gamepads[index].deadZone)
        return result;
    else
        return 0;
}

bool Input::IsGamepadButtonPressed(int index, GamepadButtons button)
{
    if (!Input::Get()->gamepads[index].SDL_Gamepad)
        return false;

    if (button == Gamepad::Buttons::GAMEPAD_BUTTON_LEFT_TRIGGER)
        return GetGamepadAxis(index, Gamepad::Axis::GAMEPAD_AXIS_LEFT_TRIGGER) > 0 ? true : false;
    else if (button == Gamepad::Buttons::GAMEPAD_BUTTON_RIGHT_TRIGGER)
        return GetGamepadAxis(index, Gamepad::Axis::GAMEPAD_AXIS_RIGHT_TRIGGER) > 0 ? true : false;

    if (Input::Get()->gamepads[index].isGamepad)
        return SDL_GameControllerGetButton((SDL_GameController*)Input::Get()->gamepads[index].SDL_Gamepad, static_cast<SDL_GameControllerButton>(button));
    else
        return SDL_JoystickGetButton((SDL_Joystick*)Input::Get()->gamepads[index].SDL_Gamepad, button);
}

}

#endif
