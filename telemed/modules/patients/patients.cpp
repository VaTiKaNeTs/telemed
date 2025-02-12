#include "patients.h"

static cJSON* patients = NULL;

/****************************************************************************************************/
void patientInit(void)
{
    patients = loadPatientDatabase("patients.json");
    if (patients == NULL)
    {
        patients = cJSON_CreateArray();

        // Сохранение в файл
        if (!savePatientDatabase("patients.json", patients))
        {
            fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
        }
    }

    // Освобождение памяти
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

    //cJSON* item = cJSON_GetArrayItem(patients, id);
    //PatientData* dstPatient = jsonToPatient(item);
    //memcpy(dstPatient, patient, sizeof(PatientData));
    cJSON* newItem = patientToJson(patient);

    if (newItem != NULL)
    {
        //cJSON_AddItemToArray(patients, item);
        cJSON_ReplaceItemInArray(patients, id, newItem);

        // Сохранение в файл
        if (!savePatientDatabase("patients.json", patients))
        {
            fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
        }

        //freePatientData(patient);
    }

    // Освобождение памяти
    cJSON_Delete(patients);

    return;
}

/****************************************************************************************************/
STATUS addPatient(PatientData* patient)
{
    patients = loadPatientDatabase("patients.json");

    if (patient != NULL)
    {
        // Преобразование в JSON и добавление в массив
        cJSON* patientJson = patientToJson(patient);
        if (patientJson != NULL)
        {
            cJSON_AddItemToArray(patients, patientJson);
            /*freePatientData(patient);*/
        }
    }

    // Сохранение в файл
    if (!savePatientDatabase("patients.json", patients))
    {
        fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
    }

    // Освобождение памяти
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
        // Удаляем элемент из объекта
        cJSON_DeleteItemFromArray(patients, id);
        result = KN_OK;
    }

    savePatientDatabase("patients.json", patients);

    // Освобождение памяти
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

    // Освобождение памяти
    cJSON_Delete(patients);

    return KN_OK;
}

#if 1
/****************************************************************************************************/
PatientData* findPatientChatId(long chatId)
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

    // Освобождение памяти
    cJSON_Delete(patients);

    return patient;
}
#endif