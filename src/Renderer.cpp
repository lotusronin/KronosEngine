#include "Renderer.h"
#include <iostream>

Renderer::Renderer(std::string shader_vsf, std::string shader_fsf, std::string text_vsf, std::string text_fsf) : bkgvertsuv{ -300.0f, -220.0f, 340.0f, -220.0f, 340.0f, 260.0f, -300.0f, 260.0f, 0, 0, 1, 0, 1, 1, 0, 1} {
    shader = new Shader(shader_vsf, shader_fsf);
    textshader = new Shader(text_vsf, text_fsf);
    shader->compile();
    textshader->compile();
    fpsVal = "0";

    glGenBuffers(1,&bkgVerts);
    glBindBuffer(GL_ARRAY_BUFFER, bkgVerts);
    glBufferData(GL_ARRAY_BUFFER, 16*sizeof(float), bkgvertsuv, GL_STATIC_DRAW);
}

Renderer::~Renderer() {
    delete shader;
    delete textshader;
}

void Renderer::draw(EntityManager* entityman, MapManager* mapman, FontFactory* ffactory, ResourceManager* resman) {
    
    //Need, Camera, characterlist, groundlist, itemlist, fontfactory
    std::vector<Ground*>* groundList = entityman->getGroundList();
    std::vector<Character*>* characterList = entityman->getCharacterList();
    std::vector<Item*>* itemList = entityman->getItemList();
    Camera* cam = entityman->getCamera();
    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->enable();
    GLint cameraloc = glGetUniformLocation(shader->shaderProgram, "camera");
    glUniformMatrix4fv(cameraloc, 1, GL_FALSE, cam->GetTransform()->mat);

    //Draw Bkg
    //TODO Clean this up, maybe a function? 
    std::string bkgname = mapman->getBkgName();
    if(bkgname.compare("") != 0) {
        GLuint tex = resman->getTexture(bkgname);
        glActiveTexture(GL_TEXTURE0);
        glBindBuffer(GL_ARRAY_BUFFER, bkgVerts);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float)*8));
	    glEnableVertexAttribArray(0);
	    glEnableVertexAttribArray(1);
        GLint animloc = glGetUniformLocation(shader->shaderProgram, "animationCoords");
        GLint transloc = glGetUniformLocation(shader->shaderProgram, "transformation");
        GLint loc = glGetUniformLocation(shader->shaderProgram, "myTexture");
	    glBindTexture(GL_TEXTURE_2D, tex);
        glUniformMatrix4fv(transloc, 1, GL_FALSE, (*characterList->begin())->ptransmat->mat);
        glUniform2f(animloc, 1, 1);
	    glUniform1i(loc, 0);
	    glDrawArrays(GL_QUADS, 0, 4);
    }

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
