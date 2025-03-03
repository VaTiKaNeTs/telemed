#pragma once

#include "../../knTypes.h"
#include <tgbot/tgbot.h>

#include "../doctors/doctorDataBase.h"
#include "appointmentDataBase.h"

using namespace std;
using namespace TgBot;

void appointmentInit();

Appointment* findAppointmentId(int id);

void appointment(Bot& bot, long curChatId, SPECIALITY spec);

STATUS addAppointment(Appointment* ap);

void appointmentChoiceDateDoctor(Bot& bot, long curChatId, int doctorId);

void findAppointmentDoctorId(int* dst, int* size, int doctorId);

void findAppointmentDoctorIdAndDate(int* dst, int* size, int doctorId, int date);

