#include "patients.h"

static cJSON* patients = NULL;

/****************************************************************************************************/
void patientInit(void)
{
    patients = loadPatientDatabase("patients.json");
    if (patients == NULL)
    {
        patients = cJSON_CreateArray();

        // ���������� � ����
        if (!savePatientDatabase("patients.json", patients))
        {
            fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
        }

        PatientData* patient = createPatientData(0, 0, u8"Default", u8"Default", u8"Default", 0, u8"�������");
        addPatient(patient);

        patients = loadPatientDatabase("patients.json");
    }

    // ������������ ������
    cJSON_Delete(patients);
}

/****************************************************************************************************/
void patientEdit(int id, PatientData* patient)
{
    patients = loadPatientDatabase("patients.json");

    int len = cJSON_GetArraySize(patients);
    if (id < 0 || id >= len)
    {
        return;
    }
    cJSON* newItem = patientToJson(patient);

    if (newItem != NULL)
    {
        //cJSON_AddItemToArray(patients, item);
        cJSON_ReplaceItemInArray(patients, id, newItem);

        // ���������� � ����
        if (!savePatientDatabase("patients.json", patients))
        {
            fprintf(stderr, "������: �� ������� ��������� ���� ������\n");
        }

        //freePatientData(patient);
    }

    // ������������ ������
    cJSON_Delete(patients);

    return;
}

/****************************************************************************************************/
STATUS addPatient(PatientData* patient)
{
    patients = loadPatientDatabase("patients.json");

    if (patient != NULL)
    {
        // �������������� � JSON � ���������� � ������
        cJSON* patientJson = patientToJson(patient);
        if (patientJson != NULL)
        {
            cJSON_AddItemToArray(patients, patientJson);
            /*freePatientData(patient);*/
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


/****************************************************************************************************/
STATUS removePatient(long id)
{
    STATUS result = KN_ERROR;

    patients = loadPatientDatabase("patients.json");

    int len = cJSON_GetArraySize(patients);
    if (id < 0 || id >= len)
    {
        return KN_ERROR;
    }    

    cJSON* item = cJSON_GetArrayItem(patients, id);
    if (item != NULL)
    {
        // ������� ������� �� �������
        cJSON_DeleteItemFromArray(patients, id);
        result = KN_OK;
    }

    savePatientDatabase("patients.json", patients);

    // ������������ ������
    cJSON_Delete(patients);

    return result;
}

/****************************************************************************************************/
STATUS cleanAllPatients(void)
{
    patients = loadPatientDatabase("patients.json");

    int len = 0;
    while (len = cJSON_GetArraySize(patients))
    {
        for (int i = 0; i < len; i++)
        {
            cJSON_DeleteItemFromArray(patients, i);
        }
    }    

    savePatientDatabase("patients.json", patients);

    // ������������ ������
    cJSON_Delete(patients);

    return KN_OK;
}

/****************************************************************************************************/
void findPatientId(PatientData *patient, int id)
{
    patients = loadPatientDatabase("patients.json");

    if (patients == NULL || cJSON_GetArraySize(patients) == 0)
    {
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(patients); i++)
    {
        cJSON* patientJson = cJSON_GetArrayItem(patients, i);
        if (patientJson != NULL)
        {
            cJSON* patientId = cJSON_GetObjectItem(patientJson, "id");
            if (patientId != NULL && patientId->valuedouble == id)
            {
                PatientData*tmpPatient = jsonToPatient(patientJson);
                memcpy(patient, tmpPatient, sizeof(PatientData));
                break;
            }
        }
    }

    // ������������ ������
    cJSON_Delete(patients);

    return;
}


#if 1
/****************************************************************************************************/
PatientData* findPatientChatId(std::int64_t chatId)
{
    PatientData* patient = NULL;

    patients = loadPatientDatabase("patients.json");

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
                patient = jsonToPatient(patientJson);
            }
        }
    }

    // ������������ ������
    cJSON_Delete(patients);

    return patient;
}

#endif

/****************************************************************************************************/
int getPatientsCnt(void)
{
    patients = loadPatientDatabase("patients.json");

    int size = cJSON_GetArraySize(patients);

    // ������������ ������
    cJSON_Delete(patients);

    return size;
}