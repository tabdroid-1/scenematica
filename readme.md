
![MaineCoon](/resources/logo/Maine_Coon_Logo_Name_1024x256.png?raw=true "MaineCoon")

Ligth weight crossplatform application framework.

(Maine Coon is a cat breed, not a slur. -_-)

External Dependencies
-------------------
- Bundled with engine
  - ImGui
  - glad2
  - sdl2 
  - imguizmo
  - spdlog
  - stb_image
  - tracy profiler
  - OpenAL-Soft 

Supported Graphics Apis
-----------------------
- OpenGL 3.3
- OpenGL 3.0 es

Supported Platforms
-------------------
- Linux
- Windows (not tested)
- MacOS
- Web (not tested in a while)
- Android (not tested in a while)

Compiling
---------

You might have to install some libraries for building.
For building web install emscriptem from their git repo. Installing from package manager may give compilation errors.

- Native
  - For Unix:  
    1. ```shell
       git clone https://github.com/tabdroid-1/MaineCoon.git && mkdir MaineCoon/build && cd MaineCoon/build
        ```
    2. ```shell
       cmake .. && make
        ```
    
  - For Windows:  
    1. ```shell
        Todo
        ```

  - For Android 
    1. ```shell
       # It should build out of the box when built from Android Studio
       ```

- For Web 

  1. ```shell
     git clone https://github.com/tabdroid-1/MaineCoon.git && mkdir MaineCoon/build && cd MaineCoon/build
        ```

  2. ```shell
     emcmake cmake .. && make
        ```

  3. ```shell
     python3 -m http.server 8080
        ```
     
Special Thanks
 --------------
- Jonny Hotbody
- Peppino Spaghetti
- Soilder from TF2
- 2008 Toyota Corolla
- Bon
