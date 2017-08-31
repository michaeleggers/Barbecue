cmake_minimum_required(VERSION 3.6)

project(Barbecue)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.5")

set(SDL2_IMAGE_LIBRARY "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_image-2.0.1/lib/x64/SDL2_image.lib")
set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_image-2.0.1/include")

find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} 
                    ${SDL2_IMAGE_INCLUDE_DIR}
                     )

set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY})

add_executable(Barbecue src/main.cpp src/Sprite.cpp src/SpriteSheet.cpp inc/Sprite.h inc/SpriteSheet.h)
source_group("resources" FILES ${RESOURCES})
target_link_libraries(Barbecue ${SDL2_LIBRARIES} 
							   ${SDL2_IMAGE_LIBRARIES}
							   )