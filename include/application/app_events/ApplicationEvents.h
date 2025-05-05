//
// Created by belyashik2k on 5/2/25.
//

#ifndef APPLICATIONEVENTS_H
#define APPLICATIONEVENTS_H

#include <interfaces/IEvent.h>

class OnApplicationStartup: public IEvent {};
class OnApplicationShutdown : public IEvent {};

#endif //APPLICATIONEVENTS_H
