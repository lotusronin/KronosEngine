#ifndef GAMEEVENT_H
#define GAMEEVENT_H

enum GameEvent_t { ATTACK, HIT, JUMP, TALK, ITEMGET, MONEYGET, DEATH, HEAL, LEVELSTART, LEVELEND, CHECKPOINT};


class GameEvent {
    public:
        GameEvent(void* origin, GameEvent_t type, void(*callback)(void*));
        ~GameEvent();
        GameEvent_t getType();
        template<typename T>
        T* getOrigin();
        void process();
    private:
        void* m_origin;
        GameEvent_t m_type;
        void (*m_callback)(void*);
};


#endif //GAMEEVENT_H
