#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "GameEvent.h"
#include <vector>

class EventManager {
    private:
        std::vector<GameEvent*> events;
    public:
        EventManager();
        ~EventManager();
        void addEvent(GameEvent* event);
        void processEvents();
};

#endif //EVENTMANAGER_H
