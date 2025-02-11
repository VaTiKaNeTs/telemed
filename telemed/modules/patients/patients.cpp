#include "patients.h"

static cJSON* patients = NULL;

/****************************************************************************************************/
STATUS savePatient(PatientData* patient)
{
    if (patient != NULL)
    {
        // �������������� � JSON � ���������� � ������
        cJSON* patientJson = patientToJson(patient);
        if (patientJson != NULL)
        {
            cJSON_AddItemToArray(patients, patientJson);
            freePatientData(patient);
        }
    }

    // ���������� � ����
    if (!savePatientDatabase("patients.json", patients))
    {
        fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
    }

    // ������������ ������
    cJSON_Delete(patients);

    return KN_OK;
}

/****************************************************************************************************/
PatientData* findPatientChatId(long chatId)
{
    if (patients == NULL || cJSON_GetArraySize(patients) == 0) 
    {
        return NULL;
    }

    for (int i = 0; i < cJSON_GetArraySize(patients); i++) 
    {
        cJSON* patientJson = cJSON_GetArrayItem(patients, i);
        if (patientJson != NULL) 
        {
            cJSON* patientId = cJSON_GetObjectItem(patientJson, "chatid");
            if (patientId != NULL && patientId->valuedouble == chatId) 
            {
                return jsonToPatient(patientJson);
            }
        }
    }

    return NULL;
}