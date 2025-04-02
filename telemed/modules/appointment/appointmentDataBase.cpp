#include "appointmentDataBase.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "../../libs/cJSON/cJSON.h"
#include <sstream>
#include <string>
#include <iostream>

/****************************************************************************************************/
void createAp(Appointment* ap, int id, int doctorId, int patientId, int dayOfYear, int year, int minOfDay)
{
    if (ap == NULL) return;

    ap->id = id;
    ap->doctorId = doctorId;
    ap->patientId = patientId;
    ap->dayOfYear = dayOfYear;
    ap->year = year;
    ap->minOfDay = minOfDay;
}

/****************************************************************************************************/
void freeAp(Appointment* ap)
{
    if (ap != NULL)
    {
        free(ap);
    }
}

/****************************************************************************************************/
cJSON* apToJson(Appointment* ap)
{
    if (ap == NULL) return NULL;

    cJSON* json = cJSON_CreateObject();
    if (json == NULL) return NULL;

    cJSON_AddNumberToObject(json, "id", ap->id);
    cJSON_AddNumberToObject(json, "doctorId", ap->doctorId);
    cJSON_AddNumberToObject(json, "patientId", ap->patientId);
    cJSON_AddNumberToObject(json, "dayOfYear", ap->dayOfYear);
    cJSON_AddNumberToObject(json, "year", ap->year);
    cJSON_AddNumberToObject(json, "minOfDay", ap->minOfDay);

    return json;
}

/****************************************************************************************************/
void jsonToAp(cJSON* json, Appointment *ap)
{
    if (json == NULL) return;

    createAp(ap,
        (int)cJSON_GetObjectItem(json, "id")->valueint,
        (int)cJSON_GetObjectItem(json, "doctorId")->valueint,
        (int)cJSON_GetObjectItem(json, "patientId")->valueint,
        (int)cJSON_GetObjectItem(json, "dayOfYear")->valueint,
        (int)cJSON_GetObjectItem(json, "year")->valueint,
        (int)cJSON_GetObjectItem(json, "minOfDay")->valueint
    );
}

/****************************************************************************************************/
int saveAp(const char* filename, cJSON* ap)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) return 0;

    char* jsonStr = cJSON_Print(ap);
    if (jsonStr == NULL) {
        fclose(file);
        return 0;
    }

    fprintf(file, "%s", jsonStr);
    free(jsonStr);
    fclose(file);
    return 1;
}

/****************************************************************************************************/
cJSON* loadAp(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    cJSON* json = cJSON_Parse(buffer);
    free(buffer);
    return json;
}