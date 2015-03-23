#include "Script.h"

Script::Script(asIScriptEngine* engine, std::string& file) {
    m_name = file;
    m_engine = engine;
    asIScriptModule* mod = m_engine->GetModule("MyFirstMod");
    m_func = mod->GetFunctionByName(file.c_str());
    if(m_func == 0) {
        std::cout << "Error, m_func is null!\n";
    }
}

Script::~Script(){
}

asIScriptFunction* Script::getFunc() {
    return m_func;
}

void Script::execute(Entity* e) {
    asIScriptContext* ctx = m_engine->CreateContext();
    ctx->Prepare(m_func);
    ctx->SetArgObject(0,&*e);
    int r = ctx->Execute();
    checkASError(r, ctx);

    ctx->Release();
}

void Script::execute(Entity* e, Entity* p) {
    asIScriptContext* ctx = m_engine->CreateContext();
    ctx->Prepare(m_func);
    ctx->SetArgObject(0,&*e);
    ctx->SetArgObject(1,p);
    int r = ctx->Execute();
    checkASError(r, ctx);

    ctx->Release();

}


void checkASError(int r, asIScriptContext* ctx) {
    if( r != asEXECUTION_FINISHED) {
        if( r == asEXECUTION_EXCEPTION) {
            std::cout << "Error, an exception occured:\n";
            std::cout << ctx->GetExceptionString() << "\n";
        }
        if( r == asEXECUTION_UNINITIALIZED) {
            std::cout << "Error, execution uninitialized.\n";
        }
        if( r == asEXECUTION_ERROR) {
            std::cout << "Error, context needs to be reinitialized!\n";
        }
        if( r == asERROR) {
            std::cout << "it was a normal error!\n";
        }
    }
}
