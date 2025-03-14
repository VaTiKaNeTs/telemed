#include "group.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>

static cJSON* groups = NULL;

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

    // ������������ ������
    //cJSON_Delete(groups);

    return i;
}

/****************************************************************************************************/
void groupInit(void)
{
    groups = loadGroup("groups.json");
    if (groups == NULL)
    {
        groups = cJSON_CreateArray();

        // ���������� � ����
        if (!saveGroup("groups.json", groups))
        {
            fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
        }
        Group* group = createGroup(0, 0, 0, 0, 0);
        addGroup(group);

        groups = loadGroup("groups.json");
    }

    // ������������ ������
    cJSON_Delete(groups);
}

/****************************************************************************************************/
void groupEdit(int chatId, Group* group)
{
    groups = loadGroup("groups.json");

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

        // ���������� � ����
        if (!saveGroup("groups.json", groups))
        {
            fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
        }
    }

    // ������������ ������
    cJSON_Delete(groups);

    return;
}

/****************************************************************************************************/
STATUS addGroup(Group* group)
{
    groups = loadGroup("groups.json");

    if (group != NULL)
    {
        // �������������� � JSON � ���������� � ������
        cJSON* doctorJson = groupToJson(group);
        if (doctorJson != NULL)
        {
            cJSON_AddItemToArray(groups, doctorJson);
        }
    }

    // ���������� � ����
    if (!saveGroup("groups.json", groups))
    {
        fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
    }

    // ������������ ������
    cJSON_Delete(groups);

    return KN_OK;
}

/****************************************************************************************************/
STATUS removeGroup(long chatId)
{
    STATUS result = KN_ERROR;

    groups = loadGroup("groups.json");

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
            // ������� ������� �� �������
            cJSON_DeleteItemFromArray(groups, id);
            result = KN_OK;
        }

        saveGroup("groups.json", groups);
    }
    
    // ������������ ������
    cJSON_Delete(groups);

    return result;
}

/****************************************************************************************************/
STATUS cleanAllGroups(void)
{
    groups = loadGroup("groups.json");

    int len = 0;
    while (len = cJSON_GetArraySize(groups))
    {
        for (int i = 0; i < len; i++)
        {
            cJSON_DeleteItemFromArray(groups, i);
        }
    }

    saveGroup("groups.json", groups);

    // ������������ ������
    cJSON_Delete(groups);

    return KN_OK;
}

/****************************************************************************************************/
#if 0
Group* findGroupId(int id)
{
    Group* group = (Group*)malloc(sizeof(Group));

    groups = loadGroup("groups.json");

    if (groups == NULL || cJSON_GetArraySize(groups) == 0)
    {
        return NULL;
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

    // ������������ ������
    cJSON_Delete(groups);

    return group;
}
#endif

/****************************************************************************************************/
void findGroupChatId(Group *group, long chatId)
{
    if (group == NULL)
    {
        return;
    }

    groups = loadGroup("groups.json");

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

    // ������������ ������
    cJSON_Delete(groups);

    return;
}

/****************************************************************************************************/
UINT32 groupGetCnt(void)
{
    groups = loadGroup("groups.json");

    if (groups == NULL)
    {
        return 0;
    }
    else
    {
        return cJSON_GetArraySize(groups);
    }

    // ������������ ������
    cJSON_Delete(groups);
}