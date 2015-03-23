#ifndef SCRIPTMANAGER
#define SCRIPTMANAGER

#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <string>
#include <iostream>
#include <vector>
#include "Script.h"
#include "Entity.h"
#include "Character.h"

class ScriptManager {
    public:
        ScriptManager();
        ~ScriptManager();
        void execute();
        void registerTypes(asIScriptEngine* engine);
        Script* loadScript(std::string &filename);
    private:
        std::vector<Script*> m_scripts;
        asIScriptEngine* engine;
        CScriptBuilder builder;
};

void print(std::string &msg);

void MsgCallbk(const asSMessageInfo* msg, void* param); 

#endif //SCRIPTMANAGER
