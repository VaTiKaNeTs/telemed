#include "doctorDataBase.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "../../libs/cJSON/cJSON.h"

/****************************************************************************************************/
// Функция для создания нового доктора
Doctor* createDoctor(int id, int64_t chatId, SPECIALITY specialty, const char* firstName, const char* lastName,
    const char* middleName, float experience, const char* photo_path, float rating)
{
    Doctor* doctor = (Doctor*)malloc(sizeof(Doctor));
    if (doctor == NULL) return NULL;

    doctor->firstName = _strdup(firstName);
    doctor->lastName = _strdup(lastName);
    doctor->middleName = _strdup(middleName);
    doctor->photo_path = _strdup(photo_path);
    doctor->id = id;
    doctor->chatId = chatId;
    doctor->specialty = specialty;
    doctor->experience = experience;
    doctor->rating = rating;

    return doctor;
}

/****************************************************************************************************/
// Функция для освобождения памяти пациента
void freeDoctor(Doctor* doctor)
{
    if (doctor != NULL)
    {
        free(doctor->firstName);
        free(doctor->lastName);
        free(doctor->middleName);
        free(doctor);
    }
}

/****************************************************************************************************/
// Функция для создания JSON объекта пациента
cJSON* doctorToJson(Doctor* doctor)
{
    if (doctor == NULL) return NULL;

    cJSON* json = cJSON_CreateObject();
    if (json == NULL) return NULL;

    cJSON_AddNumberToObject(json, "id", doctor->id);
    cJSON_AddNumberToObject(json, "chatId", doctor->chatId);
    cJSON_AddNumberToObject(json, "specialty", doctor->specialty);
    cJSON_AddStringToObject(json, "firstName", doctor->firstName);
    cJSON_AddStringToObject(json, "lastName", doctor->lastName);
    cJSON_AddStringToObject(json, "middleName", doctor->middleName);
    cJSON_AddStringToObject(json, "photo_path", doctor->photo_path);
    cJSON_AddNumberToObject(json, "experience", doctor->experience);
    cJSON_AddNumberToObject(json, "rating", doctor->rating);

    return json;
}

/****************************************************************************************************/
// Функция для создания пациента из JSON
Doctor* jsonToDoctor(cJSON* json)
{
    if (json == NULL) return NULL;

    Doctor* doctor = createDoctor(
        (int)cJSON_GetObjectItem(json, "id")->valueint,
        (int)cJSON_GetObjectItem(json, "chatId")->valueint,
        (SPECIALITY)cJSON_GetObjectItem(json, "specialty")->valueint,
        cJSON_GetObjectItem(json, "firstName")->valuestring,
        cJSON_GetObjectItem(json, "lastName")->valuestring,
        cJSON_GetObjectItem(json, "middleName")->valuestring,
        (float)cJSON_GetObjectItem(json, "experience")->valuedouble,
        cJSON_GetObjectItem(json, "photo_path")->valuestring,
        (float)cJSON_GetObjectItem(json, "rating")->valuedouble
    );

    return doctor;
}

/****************************************************************************************************/
// Функция для сохранения базы данных в файл
int saveDoctor(const char* filename, cJSON* doctors)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) return 0;

    char* jsonStr = cJSON_Print(doctors);
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
cJSON* loadDoctor(const char* filename)
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