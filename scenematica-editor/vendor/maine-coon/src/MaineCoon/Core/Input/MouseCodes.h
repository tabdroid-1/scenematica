#pragma once

// Quirks of C++. Do not touch
#include "../vendor/SDL2/include/SDL_mouse.h"
// #include "../../vendor/SDL2/include/SDL_mouse.h"

namespace MaineCoon {
using MouseCode = uint32_t;

namespace Mouse {
    enum : MouseCode {
        Button0 = SDL_BUTTON_LEFT,
        Button1 = SDL_BUTTON_RIGHT,
        Button2 = SDL_BUTTON_MIDDLE,
        Button3 = SDL_BUTTON_X1,
        Button4 = SDL_BUTTON_X2,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,

        ButtonLast = Button7,
        ButtonLeft = Button0,
        ButtonRight = Button1,
        ButtonMiddle = Button2
    };
}
}
