#include "group.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>

static cJSON* groups = NULL;

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
        Group* group = createGroup(0, 0, 0, 0, 0, 0);
        addGroup(group);

        //group = createGroup(1, PEDIATRICIAN, u8"������", u8"�������", u8"����������", 3, "pathtttt", 44);
        //addGroup(group);
        //group = createGroup(2, PEDIATRICIAN, u8"��������", u8"��������������", u8"��������", 10, "pathtttt", 50);
        //addGroup(group);
        //group = createGroup(3, SURGEON, u8"����", u8"������", u8"����������", 5, "pathtttt", 48);
        //addGroup(group);

        groups = loadGroup("groups.json");
    }

    // ������������ ������
    cJSON_Delete(groups);
}

/****************************************************************************************************/
void groupEdit(int id, Group* group)
{
    groups = loadGroup("groups.json");

    int len = cJSON_GetArraySize(groups);
    if (id < 0 || id >= len)
    {
        return;
    }
    cJSON* newItem = groupToJson(group);

    if (newItem != NULL)
    {
        //cJSON_AddItemToArray(groups, item);
        cJSON_ReplaceItemInArray(groups, id, newItem);

        // ���������� � ����
        if (!saveGroup("groups.json", groups))
        {
            fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
        }

        //freedoctorData(group);
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
            /*freedoctorData(group);*/
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
STATUS removeGroup(long id)
{
    STATUS result = KN_ERROR;

    groups = loadGroup("groups.json");

    int len = cJSON_GetArraySize(groups);
    if (id < 0 || id >= len)
    {
        return KN_ERROR;
    }

    cJSON* item = cJSON_GetArrayItem(groups, id);
    if (item != NULL)
    {
        // ������� ������� �� �������
        cJSON_DeleteItemFromArray(groups, id);
        result = KN_OK;
    }

    saveGroup("groups.json", groups);

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