#include "group.h"

#include "../modules/appointment/appointment.h"
#include "../modules/patients/patients.h"
#include "../modules/doctors/doctors.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include <iostream>
#include <ctime>

static cJSON* groups = NULL;

#define GROUP_MAX_BUF 20


/****************************************************************************************************/
void group(Bot& bot)
{
    static std::tm prevTime = { 0 };

    /* получаем время текущее */
    std::time_t now = std::time(nullptr);

    // Преобразуем в локальное время
    std::tm* localTime = std::localtime(&now);

    if (localTime->tm_min == prevTime.tm_min)
    {
        return;
    }

    prevTime.tm_min = localTime->tm_min;

    printf("proverka group\n");

    // Ищем подходящие встречи.
    int buf[GROUP_MAX_BUF] = { 0 };
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;
    int hour = localTime->tm_hour;
    int min = localTime->tm_min;
    int size = findAppointment(buf, GROUP_MAX_BUF, ANY, ANY, ANY, localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900, 
        localTime->tm_hour, localTime->tm_min);

    /* проверяем не пора ли добавить в группу врача и пациента */
    while (size)
    {
        if (buf[--size] != 0)
        {
            Appointment ap = { 0 }; 
            findAppointmentId(&ap, buf[size]);

            Group group = { 0 };
            findFreeGroup(&group);

            if (ap.id != 0 && group.chatId != 0)
            {
                PatientData patient = { 0 };
                findPatientId(&patient, ap.patientId);

                if (patient.chatId != 0)
                {
                    group.patientId = patient.id;
                    group.patientChatId = patient.chatId;
                }

                Doctor* doctor = findDoctorId(ap.doctorId);
                if (doctor->chatId != 0)
                {
                    group.doctorId = doctor->id;
                    group.doctorChatId = doctor->chatId;
                }
                
                bot.getApi().getChatAdministrators(group.chatId);
                /*std::string inviteLink = */ bot.getApi().exportChatInviteLink(group.chatId);
                //bot.getApi().sendMessage(group.doctorChatId, "Приглашение в группу: " + inviteLink);
                //bot.getApi().sendMessage(group.patientChatId, "Приглашение в группу: " + inviteLink);
            }
        }
    }
}

/****************************************************************************************************/
void startGroup(Appointment* ap)
{
    
}

/****************************************************************************************************/
static UINT32 findIndex(long chatId)
{
    UINT32 i = 0;

    //groups = loadGroup("groups.json");

    if (groups == NULL || cJSON_GetArraySize(groups) == 0)
    {
        return 0;
    }

    for (i = 0; i < cJSON_GetArraySize(groups); i++)
    {
        cJSON* groupJson = cJSON_GetArrayItem(groups, i);
        if (groupJson != NULL)
        {
            cJSON* groupId = cJSON_GetObjectItem(groupJson, "chatId");
            if (groupId != NULL && groupId->valuedouble == chatId)
            {
                break;
            }
        }
    }

    // Освобождение памяти
    //cJSON_Delete(groups);

    return i;
}

/****************************************************************************************************/
void groupUpdate(void)
{
    groups = loadGroup("groups.json");
}

/****************************************************************************************************/
void groupInit(void)
{
    groups = loadGroup("groups.json");
    if (groups == NULL)
    {
        groups = cJSON_CreateArray();

        // Сохранение в файл
        if (!saveGroup("groups.json", groups))
        {
            fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
        }
        Group* group = createGroup(0, 0, 0, 0, 0);
        addGroup(group);

        groups = loadGroup("groups.json");
    }
}

/****************************************************************************************************/
void groupEdit(int chatId, Group* group)
{

    int len = cJSON_GetArraySize(groups);
    if (chatId == 0)
    {
        return;
    }
    cJSON* newItem = groupToJson(group);

    if (newItem != NULL)
    {
        UINT32 id = findIndex(chatId);
        cJSON_ReplaceItemInArray(groups, id, newItem);

        // Сохранение в файл
        if (!saveGroup("groups.json", groups))
        {
            fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
        }
    }

    return;
}

/****************************************************************************************************/
STATUS addGroup(Group* group)
{

    if (group != NULL)
    {
        // Преобразование в JSON и добавление в массив
        cJSON* doctorJson = groupToJson(group);
        if (doctorJson != NULL)
        {
            cJSON_AddItemToArray(groups, doctorJson);
        }
    }

    // Сохранение в файл
    if (!saveGroup("groups.json", groups))
    {
        fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
    }

    return KN_OK;
}

/****************************************************************************************************/
STATUS removeGroup(long chatId)
{
    STATUS result = KN_ERROR;

    int len = cJSON_GetArraySize(groups);
    if (chatId == 0)
    {
        return KN_ERROR;
    }

    UINT32 id = findIndex(chatId);

    if (id)
    {
        cJSON* item = cJSON_GetArrayItem(groups, id);
        if (item != NULL)
        {
            // Удаляем элемент из объекта
            cJSON_DeleteItemFromArray(groups, id);
            result = KN_OK;
        }

        saveGroup("groups.json", groups);
    }

    return result;
}

/****************************************************************************************************/
STATUS cleanAllGroups(void)
{

    int len = 0;
    while (len = cJSON_GetArraySize(groups))
    {
        for (int i = 0; i < len; i++)
        {
            cJSON_DeleteItemFromArray(groups, i);
        }
    }

    saveGroup("groups.json", groups);

    return KN_OK;
}

/****************************************************************************************************/
#if 1
void findGroupId(Group* group, int id)
{

    if (groups == NULL || cJSON_GetArraySize(groups) == 0)
    {
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(groups); i++)
    {
        cJSON* doctorJson = cJSON_GetArrayItem(groups, i);
        if (doctorJson != NULL)
        {
            cJSON* doctorId = cJSON_GetObjectItem(doctorJson, "id");
            if (doctorId != NULL && doctorId->valuedouble == id)
            {
                group = jsonToGroup(doctorJson);
            }
        }
    }

    return;
}
#endif

/****************************************************************************************************/
void findGroupChatId(Group *group, long chatId)
{
    if (group == NULL)
    {
        return;
    }

    if (groups == NULL || cJSON_GetArraySize(groups) == 0)
    {
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(groups); i++)
    {
        cJSON* groupJson = cJSON_GetArrayItem(groups, i);
        if (groupJson != NULL)
        {
            cJSON* groupId = cJSON_GetObjectItem(groupJson, "chatId");
            if (groupId != NULL && groupId->valuedouble == chatId)
            {
                Group *tmpGroup = jsonToGroup(groupJson);
                memcpy(group, tmpGroup, sizeof(Group));
                break;
            }
        }
    }

    return;
}

/****************************************************************************************************/
void findFreeGroup(Group* group)
{
    if (groups == NULL || cJSON_GetArraySize(groups) == 0)
    {
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(groups); i++)
    {
        cJSON* groupJson = cJSON_GetArrayItem(groups, i);
        if (groupJson != NULL)
        {
            cJSON* groupChatId = cJSON_GetObjectItem(groupJson, "chatId");
            cJSON* groupDoctorId = cJSON_GetObjectItem(groupJson, "doctorId");
            cJSON* groupPatientId = cJSON_GetObjectItem(groupJson, "patientId");
            if (groupChatId != NULL && groupChatId->valuedouble != 0 &&
                groupDoctorId != NULL && groupDoctorId->valuedouble == 0 &&
                groupPatientId != NULL && groupPatientId->valuedouble == 0)
            {
                Group* tmpGroup = jsonToGroup(groupJson);
                memcpy(group, tmpGroup, sizeof(Group));
                break;
            }
        }
    }
}

/****************************************************************************************************/
UINT32 groupGetCnt(void)
{
    if (groups == NULL)
    {
        return 0;
    }
    else
    {
        return cJSON_GetArraySize(groups);
    }
}