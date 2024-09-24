cmake_minimum_required(VERSION 3.10.2)
project( Live_Video_Streamimg )
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable( broadcast_images src/broadcast_images.cpp )
target_link_libraries( broadcast_images ${OpenCV_LIBS} )

add_executable( receiver src/receiver.cpp )
target_link_libraries( receiver ${OpenCV_LIBS} )

