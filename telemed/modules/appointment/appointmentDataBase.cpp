#include "appointmentDataBase.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "../../libs/cJSON/cJSON.h"
#include <sstream>
#include <string>
#include <iostream>

/****************************************************************************************************/
Appointment* createAp(int id, int doctorId, int patientId, AP_DATE* date,
    AP_TIME* time)
{
    Appointment* ap = (Appointment*)malloc(sizeof(Appointment));
    if (ap == NULL) return NULL;

    ap->id = id;
    ap->doctorId = doctorId;
    ap->patientId = patientId;
    memcpy(&ap->date, date, sizeof(AP_DATE));
    memcpy(&ap->time, time, sizeof(AP_TIME));

    return ap;
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
    std::string dateStr = { std::to_string(ap->date.day) + "." + std::to_string(ap->date.month) + "." + std::to_string(ap->date.year)};
    std::string timeStr = { std::to_string(ap->time.hour) + ":" + std::to_string(ap->time.min) };
    cJSON_AddStringToObject(json, "date", dateStr.c_str());
    cJSON_AddStringToObject(json, "time", timeStr.c_str());

    return json;
}

/****************************************************************************************************/
Appointment* jsonToAp(cJSON* json)
{
    if (json == NULL) return NULL;

    std::string dateStr = cJSON_GetObjectItem(json, "date")->valuestring;
    std::string timeStr = cJSON_GetObjectItem(json, "time")->valuestring;

    /* Парсим строку с датой */
    AP_DATE date;
    std::stringstream ss(dateStr);
    char dot1, dot2;  // Для точек разделителей
    ss >> date.day >> dot1 >> date.month >> dot2 >> date.year;

    /* Парсим строку времени */
    AP_TIME time;
    std::stringstream ss1(timeStr);
    ss1 >> time.hour >> dot1 >> time.min;

    Appointment* ap = createAp(
        (int)cJSON_GetObjectItem(json, "id")->valueint,
        (int)cJSON_GetObjectItem(json, "doctorId")->valueint,
        (int)cJSON_GetObjectItem(json, "patientId")->valueint,
        &date,
        (AP_TIME*)cJSON_GetObjectItem(json, "time")->valuestring
    );



    return ap;
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