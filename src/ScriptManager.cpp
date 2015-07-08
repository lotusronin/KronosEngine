#include "ScriptManager.h"
#include <assert.h>

#define NOTE(x) std::cout << "Registered " << #x << std::endl;

ScriptManager::ScriptManager() {
    engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
    int r = engine->SetMessageCallback(asFUNCTION(MsgCallbk), 0, asCALL_CDECL);
    assert(r >= 0);

    registerTypes(engine);

    r = builder.StartNewModule(engine, "MyFirstMod");
    if (r < 0) {
        std::cout << "error, couldn't build module!\n";
    }
}


ScriptManager::~ScriptManager() {
    for(auto it : m_scripts) {
        delete it;
    }
    engine->ShutDownAndRelease();
}

void ScriptManager::execute() {
    int r = builder.AddSectionFromFile("scripts/test.as");
    if(r < 0) {
        std::cout << "Errors in script, please fix!\n";
    }

    r = builder.BuildModule();
    if(r < 0) {
        std::cout << "Error building module!\n";
    }
    
    asIScriptModule* mod = engine->GetModule("MyFirstMod");
    asIScriptFunction* func = mod->GetFunctionByDecl("void main()");
    if(!func)
    {
        std::cout << "Error function needs a 'void main()'\n";
    }
    
    asIScriptContext* ctx = engine->CreateContext();
    ctx->Prepare(func);
    r = ctx->Execute();
    checkASError(r, ctx);
    ctx->Release();
}

Script* ScriptManager::loadScript(std::string &filename) {
    std::string f = "scripts/"+filename+".as";
    int r = builder.AddSectionFromFile(f.c_str());
    r = builder.BuildModule();
    m_scripts.push_back(new Script(engine, filename));
    return m_scripts.back();
}

void ScriptManager::registerTypes(asIScriptEngine* engine) { 
    RegisterStdString(engine);
    int r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
    assert(r >= 0);
    
    //Register Entities And other classes
    r = engine->RegisterObjectType("Entity", 0, asOBJ_REF | asOBJ_NOCOUNT);
    assert( r >= 0);
    r = engine->RegisterObjectMethod("Entity", "string getTexName()", asMETHOD(Entity, getTexName), asCALL_THISCALL);
    assert(r >= 0);
    r = engine->RegisterObjectType("PhysicsSquare", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
    r = engine->RegisterObjectMethod("PhysicsSquare", "void setVeloc(float vx, float vy)", asMETHOD(PhysicsSquare, setVeloc), asCALL_THISCALL);
    assert(r >= 0);
    r = engine->RegisterObjectMethod("PhysicsSquare", "float getVelx()", asMETHOD(PhysicsSquare, getVelx), asCALL_THISCALL);
    assert(r >= 0);
    r = engine->RegisterObjectMethod("PhysicsSquare", "float getVely()", asMETHOD(PhysicsSquare, getVely), asCALL_THISCALL);
    assert(r >= 0);
    r = engine->RegisterObjectType("Character", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
    r = engine->RegisterObjectMethod("Character", "PhysicsSquare& getObj()", asMETHOD(Character, getObj), asCALL_THISCALL);
    assert(r >= 0);
    r = engine->RegisterObjectMethod("Character", "float getCenterX()", asMETHOD(Character, getCenterX), asCALL_THISCALL);
    assert(r >= 0);
    r = engine->RegisterObjectMethod("Character", "float getCenterY()", asMETHOD(Character, getCenterY), asCALL_THISCALL);
    assert(r >= 0);

    NOTE(Entity)
    NOTE(getTexName)
    NOTE(PhysicsSquare)
    NOTE(setVeloc)
    NOTE(getVelx)
    NOTE(getVely)
    NOTE(Character)
    NOTE(getObj)
    NOTE(getCenterX)
    NOTE(getCenterY)


}

void print(std::string &msg) {
    std::cout << msg << "\n";
}

void MsgCallbk(const asSMessageInfo* msg, void* param) {
    const char* type = "ERR";
    if( msg->type == asMSGTYPE_WARNING) {
        type = "WARN";
    } else if (msg->type == asMSGTYPE_INFORMATION) {
        type = "INFO";
    }
    std::cout << msg->section << " (" << msg->row << "," << msg->col << ") :" << type << " : " << msg->message << "\n";
}

