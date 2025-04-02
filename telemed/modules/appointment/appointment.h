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

void appointment(Bot& bot, int64_t curChatId, SPECIALITY spec);

void appointmentReg(Bot& bot, int64_t curChatId, int id);

void appointmentDelete(Bot& bot, int64_t curChatId, int id);

void appointmentShow(Bot& bot, int64_t curChatId);

STATUS addAppointment(Appointment* ap);

void appointmentEdit(int id, Appointment* ap);

void appointmentChoiceDateDoctor(Bot& bot, int64_t curChatId, int doctorId);

void appointmentChoiceTimeDoctor(Bot& bot, std::int64_t curChatId, const char* str);

void findAppointmentPatientId(int* dst, int* size, int patientId);

void findAppointmentDoctorId(int* dst, int* size, int doctorId);

void findAppointmentDoctorIdAndDate(int* dst, int* size, int doctorId, int dayOfYear, int year);

void findAppointmentDateAndTime();

int findAppointment(int* dst, int size, int id, int doctorId, int patientId, int day, int year, int minute);

//STATUS appointmentCreateByDoctor(std::int64_t c);
