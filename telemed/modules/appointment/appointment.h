#pragma once

#include "../../knTypes.h"
#include <tgbot/tgbot.h>

#include "../doctors/doctorDataBase.h"

using namespace std;
using namespace TgBot;

void appointment(Bot& bot, long curChatId, SPECIALITY spec);

