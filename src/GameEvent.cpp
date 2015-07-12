#include "GameEvent.h"

GameEvent::GameEvent(void* origin, GameEvent_t type, void(*callback)(void*)) : m_origin(origin), m_type(type), m_callback(callback)
{}

GameEvent::~GameEvent() 
{}

GameEvent_t GameEvent::getType() {
    return m_type;
}

template<typename T>
T* GameEvent::getOrigin() {
    return (T*)m_origin;
}

void GameEvent::process() {
    m_callback(m_origin);
}
