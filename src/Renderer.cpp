#include "Renderer.h"
#include <iostream>

Renderer::Renderer(std::string shader_vsf, std::string shader_fsf, std::string text_vsf, std::string text_fsf) {
    shader = new Shader(shader_vsf, shader_fsf);
    textshader = new Shader(text_vsf, text_fsf);
    shader->compile();
    textshader->compile();
    fpsVal = "0";
}

Renderer::~Renderer() {
    delete shader;
    delete textshader;
}

void Renderer::draw(EntityManager* entityman, MapManager* mapman, FontFactory* ffactory) {
    
    //Need, Camera, characterlist, groundlist, itemlist, fontfactory
    std::vector<Ground*>* groundList = entityman->getGroundList();
    std::vector<Character*>* characterList = entityman->getCharacterList();
    std::vector<Item*>* itemList = entityman->getItemList();
    Camera* cam = entityman->getCamera();
    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->enable();
    GLint cameraloc = glGetUniformLocation(shader->shaderProgram, "camera");
    glUniformMatrix4fv(cameraloc, 1, GL_FALSE, cam->GetTransform()->mat);

    for(auto it : (*characterList)){
            it->draw(shader);
    }
    
    for(auto it : (*groundList)){
            it->draw(shader);
    }

    for(auto it : (*itemList)){
            it->draw(shader);
    }

    shader->disable();

    //To test font rendering **Move out to another class soon
    textshader->enable();

    std::string m = "map";
    ffactory->renderString(m, -1, -0.8f, textshader);

    std::string NameToPrint = mapman->getMapName();
    ffactory->renderString(NameToPrint, -0.87f, -0.8f, textshader);

    std::string f = "fps";
    ffactory->renderString(f, -1, -0.9f, textshader);

    ffactory->renderString(fpsVal, -0.9f,-0.9f, textshader);

    textshader->disable();
    //End of font testing
}
