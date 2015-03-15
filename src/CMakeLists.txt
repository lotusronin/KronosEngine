include_directories(${Platformer_SOURCE_DIR}/include)
set(MY_SOURCES main.cpp Camera.cpp Character.cpp DataReader.cpp Entity.cpp
    EntityManager.cpp FontFactory.cpp GUIManager.cpp GameManager.cpp Glyph.cpp
    Ground.cpp Item.cpp KeyListener.cpp Map.cpp MapManager.cpp Matrix.cpp
    PhysicsManager.cpp PhysicsSquare.cpp PlayerControl.cpp ResourceManager.cpp
    Shader.cpp Sound.cpp Texture.cpp Vector.cpp Window.cpp)

add_executable(Platformer ${MY_SOURCES})
target_link_libraries(Platformer SDL2 GL freeimage GLEW alut openal freetype)
