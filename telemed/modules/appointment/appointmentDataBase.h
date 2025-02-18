#ifndef APPOINTMENT_DB_H_
#define APPOINTMENT_DB_H_

#include <stdio.h>
#include <string.h>
#include "../libs/cJSON/cJSON.h"

/****************************************************************************************************/
typedef struct
{
    int day;

    int month;

    int year;

} AP_DATE;

/****************************************************************************************************/
typedef struct
{
    int hour;

    int min;

} AP_TIME;

/****************************************************************************************************/
typedef struct {
    int id;

    int doctorId;

    int patientId;

    AP_DATE date;

    AP_TIME time;

} Appointment;

/****************************************************************************************************/
Appointment* createAp(int id, int doctorId, int patientId, AP_DATE* date,
    AP_TIME* time);

/****************************************************************************************************/
void freeAp(Appointment* ap);

/****************************************************************************************************/
cJSON* apToJson(Appointment* ap);

/****************************************************************************************************/
Appointment* jsonToAp(cJSON* json);

/****************************************************************************************************/
int saveAp(const char* filename, cJSON* ap);

/****************************************************************************************************/
cJSON* loadAp(const char* filename);

#endif // APPOINTMENT_DB_H_
