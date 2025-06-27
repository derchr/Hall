# Hall
This repository contains the Hall implementation for wueHans and for Desktop. The Desktop version uses raylib to emulate the wueHans hardware. To set these differences apart, the wueHans target is called "Hall" and the desktop target is called "Hall_Desktop". Because these two require different toolchains, cmake can only build one of them in one project. "Hall" is the default one, however "Hall_Desktop" can be selected by adding -DDESKTOPBUILD" to the cmake call.

There are some difference between these two implementations:
- "Hall_DESKTOP" does not support arbitrary memory access
- "HALL_DESKTOP" handles the audio restrictions rather losely. It supports up to 8 stereo channels, whereas wueHans actually only supports 4 stereo channels
