cmake_minimum_required(VERSION 3.6)

project(Barbecue)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#set(SDL2_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.5")

set(SDL2_LIBRARY "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.8/lib/x64/SDL2.lib")
set(SDL2_MAIN_LIBRARY "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.8/lib/x64/SDL2main.lib")
set(SDL2_TEST_LIBRARY "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.8/lib/x64/SDL2test.lib")
set(SDL2_IMAGE_LIBRARY "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_image-2.0.3/lib/x64/SDL2_image.lib")

set(SDL2_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2-2.0.8/include")
set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_image-2.0.3/include")

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)

## executable target


## ! executable target

include_directories(${SDL2_INCLUDE_DIRS} 
                    ${SDL2_IMAGE_INCLUDE_DIR}
                     )

set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY})
set(SDL2_LIBRARIES ${SDL2_LIBRARY}
				   ${SDL2_MAIN_LIBRARY}
				   ${SDL2_TEST_LIBRARY}
					)

add_executable(Barbecue 
	src/main.cpp
	src/Map.cpp
	src/GraphicsCore.cpp
	src/InputCore.cpp
	src/Sprite.cpp 
	src/SpriteSheet.cpp
	src/GameState.cpp
	src/GameObject.cpp
	src/Player.cpp
	src/BitmapFont.cpp
	src/TileMap.cpp
	src/Tile.cpp
	src/TileInterface.cpp
	inc/Map.h
	inc/GraphicsCore.h
	inc/InputCore.h
	inc/Sprite.h 
	inc/SpriteSheet.h
	inc/GameState.h
	inc/GameObject.h
	inc/Player.h
	inc/BitmapFont.h
	inc/TileMap.h
	inc/Tile.h
	inc/TileInterface.h
	inc/globals.h
	inc/Particle.h
	)

source_group("resources" FILES ${RESOURCES})
target_link_libraries(Barbecue ${SDL2_LIBRARIES} 
							   ${SDL2_IMAGE_LIBRARIES}
							   )
