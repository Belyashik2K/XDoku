//
// Created by belyashik2k on 4/29/25.
//

#ifndef BUTTONS_H
#define BUTTONS_H
#include "IEvent.h"

class OnSignUpButtonClicked : public IEvent {};
class OnSignInButtonClicked : public IEvent {};
class OnLeaderboardButtonClicked : public IEvent {};
class OnMainMenuButtonClicked : public IEvent {};
class OnPlayButtonClicked : public IEvent {};
class OnProfileButtonClicked : public IEvent {};

#endif //BUTTONS_H
