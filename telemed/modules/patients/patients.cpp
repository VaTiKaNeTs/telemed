#include "patients.h"

static cJSON* patients = NULL;

/****************************************************************************************************/
void patientInit(void)
{
    patients = loadPatientDatabase("patients.json");
    if (patients == NULL)
    {
        patients = cJSON_CreateArray();
    }
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
            freePatientData(patient);
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
STATUS removePatient(long id)
{
    STATUS result = KN_ERROR;

    patients = loadPatientDatabase("patients.json");

    int len = cJSON_GetArraySize(patients);
    // Ищем пациента по ID
    for (int i = 0; i < len; i++) 
    {
        cJSON* item = cJSON_GetArrayItem(patients, i);
        if (item != NULL) 
        {
            cJSON* id_item = cJSON_GetObjectItem(item, "id");
            if (id_item != NULL && id_item->type == cJSON_Number && id_item->valueint == id) 
            {
                // Удаляем найденного пациента
                cJSON_DeleteItemFromArray(patients, i);
                result = KN_OK;
            }
        }
    }

    // Освобождение памяти
    cJSON_Delete(patients);

    return result;
}


#if 0
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
    //cJSON_Delete(patients);

    return patient;
}
#endif