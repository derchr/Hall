project("Hall")

add_compile_options(
  -fno-exceptions
  -nostdlib
  -fno-unwind-tables
  -fno-rtti
  -march=rv32im
  -Os
  -ffreestanding
  -Bstatic
  -nostdinc
)

add_link_options(
  -nostdlib
  -T ${WUEHANS_LINKERSCRIPT}
  -Wl,--gc-sections
  -ffreestanding
  -Bstatic
  -nostdlib
)

add_library(Hall STATIC
  "source/Audio.cpp"
  "source/System.cpp"
  "source/Video.cpp"
)

include_directories(Hall
  PUBLIC include
  PUBLIC SYSTEM ${WUEHANS_ROOT}/include/newlib
)

target_link_libraries(Hall
  ${WUEHANS_ROOT}/lib/newlib/libc.a
  ${WUEHANS_ROOT}/lib/newlib/libg.a
  ${WUEHANS_ROOT}/lib/newlib/libgloss.a
  ${WUEHANS_ROOT}/lib/newlib/libm.a
)
