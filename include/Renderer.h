#ifndef RENDERER_H
#define RENDERER_H

#include "EntityManager.h"
#include "MapManager.h"
#include "Shader.h"
#include "FontFactory.h"
#include "Character.h"
#include "Ground.h"
#include "Item.h"
#include "Camera.h"
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>


class Renderer {
    private:
        Shader* shader;
        Shader* textshader;
    public:
        Renderer(std::string shader_vsf, std::string shader_fsf, std::string text_vsf, std::string text_fsf);
        ~Renderer();
        void draw(EntityManager* entityman, MapManager* mapman, FontFactory* ffactory);
};
#endif
