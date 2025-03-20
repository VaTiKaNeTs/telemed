#pragma once

#include "../../knTypes.h"
#include <tgbot/tgbot.h>

#include "../doctors/doctorDataBase.h"
#include "appointmentDataBase.h"

#define ANY 0xFFFFFFFF

using namespace std;
using namespace TgBot;

void appointmentUpdate(void);

void appointmentInit(void);

void findAppointmentId(Appointment* ap, int id);

void appointment(Bot& bot, long curChatId, SPECIALITY spec);

void appointmentReg(Bot& bot, long curChatId, int id);

void appointmentDelete(Bot& bot, long curChatId, int id);

void appointmentShow(Bot& bot, long curChatId);

STATUS addAppointment(Appointment* ap);

void appointmentEdit(int id, Appointment* ap);

void appointmentChoiceDateDoctor(Bot& bot, long curChatId, int doctorId);

void findAppointmentPatientId(int* dst, int* size, int patientId);

void findAppointmentDoctorId(int* dst, int* size, int doctorId);

void findAppointmentDoctorIdAndDate(int* dst, int* size, int doctorId, int day, int month, int year);

void findAppointmentDateAndTime();

int findAppointment(int* dst, int size, int id, int doctorId, int patientId, int day, int month, int year, int hour, int min);

//STATUS appointmentCreateByDoctor(std::int64_t c);
