cmake_minimum_required(VERSION 4.0)

project("Hall")

add_library(Hall_Desktop STATIC
  "source/Desktop/Audio.cpp"
  "source/Desktop/System.cpp"
  "source/Desktop/Video.cpp"
)

add_library(Hall STATIC
  "source/wueHans/Audio.cpp"
  "source/wueHans/System.cpp"
  "source/wueHans/Video.cpp"
)

target_compile_options(Hall
  PUBLIC -fno-exceptions
  PUBLIC -nostdlib
  PUBLIC -fno-unwind-tables
  PUBLIC -fno-rtti
  PUBLIC -march=rv32im
  PUBLIC -Os
  PUBLIC -ffreestanding
  PUBLIC -Bstatic
  PUBLIC -nostdinc
)

target_link_options(Hall
  PUBLIC -nostdlib
  PUBLIC -Wl,--gc-sections
  PUBLIC -ffreestanding
  PUBLIC -Bstatic
  PUBLIC -nostdlib
)

target_include_directories(Hall
  PUBLIC SYSTEM include
)
