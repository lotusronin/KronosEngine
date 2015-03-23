#ifndef SCRIPT
#define SCRIPT
#include <angelscript.h>
#include <string>
#include "Entity.h"

class Script {
    public:
        Script(asIScriptEngine* engine, std::string& file);
        ~Script();
        asIScriptFunction* getFunc();
        void execute(Entity* e);
        void execute(Entity* e, Entity* p);
    private:
        asIScriptFunction* m_func;
        asIScriptEngine* m_engine;
        std::string m_name;
};

void checkASError(int r, asIScriptContext* ctx);

#endif //SCRIPT
