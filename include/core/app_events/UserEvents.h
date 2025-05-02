//
// Created by belyashik2k on 4/30/25.
//

#ifndef USEREVENTS_H
#define USEREVENTS_H
#include "IEvent.h"

class OnUserLoggedIn : public IEvent {
public:
    int userId;
    explicit OnUserLoggedIn(const int userId) : userId(userId) {}
};

#endif //USEREVENTS_H
