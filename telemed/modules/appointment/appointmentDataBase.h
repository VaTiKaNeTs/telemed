#ifndef APPOINTMENT_DB_H_
#define APPOINTMENT_DB_H_

#include <stdio.h>
#include <string.h>
#include "../libs/cJSON/cJSON.h"

/****************************************************************************************************/
typedef struct 
{
    int id;

    int doctorId;

    int patientId;

    int dayOfYear;

    int year;

    int minOfDay;

} Appointment;

/****************************************************************************************************/
void createAp(Appointment* ap, int id, int doctorId, int patientId, int dayOfYear, int year, int minOfDay);

/****************************************************************************************************/
void freeAp(Appointment* ap);

/****************************************************************************************************/
cJSON* apToJson(Appointment* ap);

/****************************************************************************************************/
void jsonToAp(cJSON* json, Appointment* ap);

/****************************************************************************************************/
int saveAp(const char* filename, cJSON* ap);

/****************************************************************************************************/
cJSON* loadAp(const char* filename);

#endif // APPOINTMENT_DB_H_
