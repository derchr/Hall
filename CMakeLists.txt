project("Hall")

add_compile_options(-nostdlib
                    -DHAVE_MMAP=0 # don't compile MMAP
                    -D_LDBL_EQ_DBL=0 # no long double support
                    -fno-exceptions
)

add_link_options(-nostdlib)

add_library(Hall STATIC
  "source/Audio.cpp"
  "source/System.cpp"
  "source/Video.cpp"
)

include_directories(Hall
  PUBLIC include
)

target_link_libraries(Hall
  ${WUEHANS_ROOT}/lib/newlib/libc.a
  ${WUEHANS_ROOT}/lib/newlib/libg.a
  ${WUEHANS_ROOT}/lib/newlib/libgloss.a
  ${WUEHANS_ROOT}/lib/newlib/libm.a
)
