#pragma once

#include "../../knTypes.h"
#include <tgbot/tgbot.h>

#include "../doctors/doctorDataBase.h"
#include "appointmentDataBase.h"

using namespace std;
using namespace TgBot;

void appointmentInit();

void appointment(Bot& bot, long curChatId, SPECIALITY spec);

STATUS addAppointment(Appointment* ap);

