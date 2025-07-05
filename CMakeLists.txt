cmake_minimum_required(VERSION 3.20)

project("Hall")

#If you want to build for desktop, use the flag -DDESKTOPBUILD, when running cmake
option(DESKTOPBUILD "Replaces the Hall library with Hall_Desktop. Hall_Desktop is for Desktop builds.")

if(DESKTOPBUILD)
	set(RAYLIB_VERSION 5.5)
	find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
	if (NOT raylib_FOUND) # If there's none, fetch and build raylib
		include(FetchContent)
		FetchContent_Declare(
		  	raylib
		  	DOWNLOAD_EXTRACT_TIMESTAMP OFF
		  	URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
		)
		FetchContent_GetProperties(raylib)
		if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
			set(FETCHCONTENT_QUIET NO)
			FetchContent_MakeAvailable(raylib)
		endif()
	endif()

	#This library contains the desktop implementation of Hall with Raylib as base
	add_library(Hall_Desktop STATIC
		"source/Desktop/System.cpp"
		"source/Desktop/Audio.cpp"
	  	"source/Desktop/Video.cpp"
	)

	target_link_libraries(Hall_Desktop
	  	raylib
	)

	target_include_directories(Hall_Desktop
	  	PUBLIC SYSTEM include
	)

	target_compile_definitions(Hall_Desktop PRIVATE DESKTOP)
else()

	#This library cointains the bare metal implementation of Hall for wueHans
  #In order to build this target without the Softwaretemplate, you need to add and use another toolchain (see softwaretemplate/cmake and softwaretemplate/CMakeLists.txt)
	add_library(Hall STATIC
	  "source/wueHans/Audio.cpp"
	  "source/wueHans/System.cpp"
	  "source/wueHans/Video.cpp"
	)

	target_compile_options(Hall
	  PRIVATE -fno-exceptions
	  PRIVATE -nostdlib
	  PRIVATE -fno-unwind-tables
	  PRIVATE -fno-rtti
	  PRIVATE -march=rv32im
	  PRIVATE -Os
	  PRIVATE -Bstatic
	  PRIVATE -nostdinc
	)

	target_link_options(Hall
	  PRIVATE -nostdlib
	  PRIVATE -Wl,--gc-sections
	  PRIVATE -Bstatic
	  PRIVATE -nostdlib
	)

	target_include_directories(Hall
	  PUBLIC SYSTEM include
	)

	target_compile_definitions(Hall PRIVATE WUEHANS)

endif()
