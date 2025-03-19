#include "groupDataBase.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "../../libs/cJSON/cJSON.h"

/****************************************************************************************************/
void createGroup(Group* group, std::int64_t chatId, long doctorId, std::int64_t doctorChatId,
    long patientId, std::int64_t patientChatId)
{
    if (group == NULL) return;

    group->chatId = chatId;
    group->doctorId = doctorId;
    group->doctorChatId = doctorChatId;
    group->patientId = patientId;
    group->patientChatId = patientChatId;

    return;
}

/****************************************************************************************************/
cJSON* groupToJson(Group* group)
{
    if (group == NULL) return NULL;

    cJSON* json = cJSON_CreateObject();
    if (json == NULL) return NULL;

    cJSON_AddNumberToObject(json, "chatId", group->chatId);
    cJSON_AddNumberToObject(json, "doctorId", group->doctorId);
    cJSON_AddNumberToObject(json, "doctorChatId", group->doctorChatId);
    cJSON_AddNumberToObject(json, "patientId", group->patientId);
    cJSON_AddNumberToObject(json, "patientChatId", group->patientChatId);

    return json;
}

/****************************************************************************************************/
void jsonToGroup(cJSON* json, Group* group)
{
    if (json == NULL) return;

     createGroup(group,
        (std::int64_t)cJSON_GetObjectItem(json, "chatId")->valuedouble,
        (long)cJSON_GetObjectItem(json, "doctorId")->valueint,
        (std::int64_t)cJSON_GetObjectItem(json, "doctorChatId")->valuedouble,
        (long)cJSON_GetObjectItem(json, "patientId")->valueint,
        (std::int64_t)cJSON_GetObjectItem(json, "patientChatId")->valuedouble
    );

    return;
}

/****************************************************************************************************/
int saveGroup(const char* filename, cJSON* groups)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) return 0;

    char* jsonStr = cJSON_Print(groups);
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
cJSON* loadGroup(const char* filename)
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