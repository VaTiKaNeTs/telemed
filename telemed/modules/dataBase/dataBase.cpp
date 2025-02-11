#include "dataBase.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "../../libs/cJSON/cJSON.h"

/****************************************************************************************************/
// Функция для создания нового пациента
PatientData* createPatientData(int id, long chatId, const char* firstName, const char* lastName,
    const char* middleName, int age, const char* gender) {
    PatientData* patient = (PatientData*)malloc(sizeof(PatientData));
    if (patient == NULL) return NULL;

    patient->firstName = _strdup(firstName);
    patient->lastName = _strdup(lastName);
    patient->middleName = _strdup(middleName);
    patient->gender = _strdup(gender);
    patient->id = id;
    patient->age = age;
    patient->chatId = chatId;

    return patient;
}

/****************************************************************************************************/
// Функция для освобождения памяти пациента
void freePatientData(PatientData* patient)
{
    if (patient != NULL) 
    {
        free(patient->firstName);
        free(patient->lastName);
        free(patient->middleName);
        free(patient->gender);
        free(patient);
    }
}

/****************************************************************************************************/
// Функция для создания JSON объекта пациента
cJSON* patientToJson(PatientData* patient)
{
    if (patient == NULL) return NULL;

    cJSON* json = cJSON_CreateObject();
    if (json == NULL) return NULL;

    cJSON_AddNumberToObject(json, "id", patient->id);
    cJSON_AddNumberToObject(json, "chatId", patient->chatId);
    cJSON_AddStringToObject(json, "firstName", patient->firstName);
    cJSON_AddStringToObject(json, "lastName", patient->lastName);
    cJSON_AddStringToObject(json, "middleName", patient->middleName);
    cJSON_AddNumberToObject(json, "age", patient->age);
    cJSON_AddStringToObject(json, "gender", patient->gender);

    return json;
}

/****************************************************************************************************/
// Функция для создания пациента из JSON
PatientData* jsonToPatient(cJSON* json)
{
    if (json == NULL) return NULL;

    PatientData* patient = createPatientData(
        (int)cJSON_GetObjectItem(json, "id")->valueint,
        (int)cJSON_GetObjectItem(json, "chatId")->valuedouble,
        cJSON_GetObjectItem(json, "firstName")->valuestring,
        cJSON_GetObjectItem(json, "lastName")->valuestring,
        cJSON_GetObjectItem(json, "middleName")->valuestring,
        (int)cJSON_GetObjectItem(json, "age")->valuedouble,
        cJSON_GetObjectItem(json, "gender")->valuestring
    );

    return patient;
}

/****************************************************************************************************/
// Функция для сохранения базы данных в файл
int savePatientDatabase(const char* filename, cJSON* patients)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) return 0;

    char* jsonStr = cJSON_Print(patients);
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
// Функция для загрузки базы данных из файла
cJSON* loadPatientDatabase(const char* filename) 
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