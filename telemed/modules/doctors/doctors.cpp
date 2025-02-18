#include "doctors.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>

static cJSON* doctors = NULL;

/****************************************************************************************************/
void doctorInit(void)
{
    doctors = loadDoctor("doctors.json");
    if (doctors == NULL)
    {
        doctors = cJSON_CreateArray();

        // ���������� � ����
        if (!saveDoctor("doctors.json", doctors))
        {
            fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
        }
        Doctor* doctor = createDoctor(0, DEFAULT_SPEC, u8"Default", u8"Default", u8"Default", 0, "Default", 0);
        addDoctor(doctor);

        doctor = createDoctor(1, PEDIATRICIAN, u8"������", u8"�������", u8"����������", 3, "pathtttt", 44);
        addDoctor(doctor);
        doctor = createDoctor(2, PEDIATRICIAN, u8"��������", u8"��������������", u8"��������", 10, "pathtttt", 50);
        addDoctor(doctor);
        doctor = createDoctor(3, SURGEON, u8"����", u8"������", u8"����������", 5, "pathtttt", 48);
        addDoctor(doctor);

        doctors = loadDoctor("doctors.json");
    }

    // ������������ ������
    cJSON_Delete(doctors);

#if 0
    
    Doctor* doctor = createDoctor(1, PEDIATRICIAN, u8"������", u8"�������", u8"����������", 3, "pathtttt", 44);
    addDoctor(doctor);
    doctor = createDoctor(2, PEDIATRICIAN, u8"��������", u8"��������������", u8"��������", 10, "pathtttt", 50);
    addDoctor(doctor);
    doctor = createDoctor(3, SURGEON, u8"����", u8"������", u8"����������", 5, "pathtttt", 48);
    addDoctor(doctor);
#endif
}

/****************************************************************************************************/
void doctorEdit(int id, Doctor* doctor)
{
    doctors = loadDoctor("doctors.json");

    int len = cJSON_GetArraySize(doctors);
    if (id < 0 || id >= len)
    {
        return;
    }
    cJSON* newItem = doctorToJson(doctor);

    if (newItem != NULL)
    {
        //cJSON_AddItemToArray(doctors, item);
        cJSON_ReplaceItemInArray(doctors, id, newItem);

        // ���������� � ����
        if (!saveDoctor("doctors.json", doctors))
        {
            fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
        }

        //freedoctorData(doctor);
    }

    // ������������ ������
    cJSON_Delete(doctors);

    return;
}

/****************************************************************************************************/
STATUS addDoctor(Doctor* doctor)
{
    doctors = loadDoctor("doctors.json");

    if (doctor != NULL)
    {
        // �������������� � JSON � ���������� � ������
        cJSON* doctorJson = doctorToJson(doctor);
        if (doctorJson != NULL)
        {
            cJSON_AddItemToArray(doctors, doctorJson);
            /*freedoctorData(doctor);*/
        }
    }

    // ���������� � ����
    if (!saveDoctor("doctors.json", doctors))
    {
        fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
    }

    // ������������ ������
    cJSON_Delete(doctors);

    return KN_OK;
}

/****************************************************************************************************/


/****************************************************************************************************/
STATUS removeDoctor(long id)
{
    STATUS result = KN_ERROR;

    doctors = loadDoctor("doctors.json");

    int len = cJSON_GetArraySize(doctors);
    if (id < 0 || id >= len)
    {
        return KN_ERROR;
    }

    cJSON* item = cJSON_GetArrayItem(doctors, id);
    if (item != NULL)
    {
        // ������� ������� �� �������
        cJSON_DeleteItemFromArray(doctors, id);
        result = KN_OK;
    }

    saveDoctor("doctors.json", doctors);

    // ������������ ������
    cJSON_Delete(doctors);

    return result;
}

/****************************************************************************************************/
STATUS cleanAllDoctors(void)
{
    doctors = loadDoctor("doctors.json");

    int len = 0;
    while (len = cJSON_GetArraySize(doctors))
    {
        for (int i = 0; i < len; i++)
        {
            cJSON_DeleteItemFromArray(doctors, i);
        }
    }

    saveDoctor("doctors.json", doctors);

    // ������������ ������
    cJSON_Delete(doctors);

    return KN_OK;
}

#if 1
/****************************************************************************************************/
Doctor* findDoctorId(int id)
{
    Doctor* doctor = (Doctor*)malloc(sizeof(Doctor));

    doctors = loadDoctor("doctors.json");

    if (doctors == NULL || cJSON_GetArraySize(doctors) == 0)
    {
        return NULL;
    }

    for (int i = 0; i < cJSON_GetArraySize(doctors); i++)
    {
        cJSON* doctorJson = cJSON_GetArrayItem(doctors, i);
        if (doctorJson != NULL)
        {
            cJSON* doctorId = cJSON_GetObjectItem(doctorJson, "id");
            if (doctorId != NULL && doctorId->valuedouble == id)
            {
                doctor = jsonToDoctor(doctorJson);
            }
        }
    }

    // ������������ ������
    cJSON_Delete(doctors);

    return doctor;
}
#endif

/****************************************************************************************************/
void findDoctorSpec(int* dst, int* size, SPECIALITY spec)
{
    int slider = 0;

    if (NULL == dst || NULL == size || !size[0])
    {
        return;
    }
    memset(dst, -1, size[0]);

    doctors = loadDoctor("doctors.json");

    if (doctors == NULL || cJSON_GetArraySize(doctors) == 0)
    {
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(doctors) && slider < size[0]; i++)
    {
        cJSON* doctorJson = cJSON_GetArrayItem(doctors, i);
        if (doctorJson != NULL)
        {
            cJSON* doctorSpec = cJSON_GetObjectItem(doctorJson, "specialty");
            if (doctorSpec != NULL && (int)doctorSpec->valuedouble == spec)
            {
                dst[slider++] = i;
            }
        }
    }

    *size = slider;

    return;
}