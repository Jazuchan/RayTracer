cmake_minimum_required(VERSION 2.6)

project(PARALLELRAYTRACER)

include_directories(
source
contrib
)

if(MSVC)
  include_directories(
    contrib/msvc-2017-windows-x86/SDL2/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/SDL2/lib
  )
else()
  include_directories(
    /usr/X11R6/include
    /usr/local/include
  )

  link_directories(
    /usr/X11R6/lib
    /usr/local/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(parallelraytracer
  
source/parallelraytracer/main.cpp

)


add_library(tracer

source/tracer/Camera.cpp
source/tracer/Camera.h

source/tracer/Geometry.cpp
source/tracer/Geometry.h

source/tracer/Ray.cpp
source/tracer/Ray.h

source/tracer/Tracer.cpp
source/tracer/Tracer.h

source/tracer/Sphere.cpp
source/tracer/Sphere.h

)

  target_link_libraries(parallelraytracer tracer)

if(MSVC)
  target_link_libraries(tracer
    SDL2
  )
else()
  target_link_libraries(tracer
    SDL2
  )
endif()

if(MSVC)

  add_custom_command(TARGET parallelraytracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:parallelraytracer>"
  )
endif()
