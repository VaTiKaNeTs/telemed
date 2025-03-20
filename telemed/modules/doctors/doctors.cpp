#include "doctors.h"

#include <stdio.h>
#include <string.h>
#include <Windows.h>

static cJSON* doctors = NULL;

#define DEFAULT_DOCTOR_CHATID 365545361

/****************************************************************************************************/
void doctorInit(void)
{
    doctors = loadDoctor("doctors.json");
    if (doctors == NULL)
    {
        doctors = cJSON_CreateArray();

        // Сохранение в файл
        if (!saveDoctor("doctors.json", doctors))
        {
            fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
        }
        Doctor* doctor = createDoctor(0, 0, DEFAULT_SPEC, u8"Default", u8"Default", u8"Default", 0, "Default", 0);
        addDoctor(doctor);

        doctor = createDoctor(1, DEFAULT_DOCTOR_CHATID, PEDIATRICIAN, u8"Кирилл", u8"Таровик", u8"Врачевич", 3, "https://clck.ru/3HsfCL", 50);
        addDoctor(doctor);
        doctor = createDoctor(2, DEFAULT_DOCTOR_CHATID, PEDIATRICIAN, u8"Черемисинов", u8"Красносолнышко", u8"Олегович", 10, "https://clck.ru/3HsiiB", 44);
        addDoctor(doctor);
        doctor = createDoctor(3, DEFAULT_DOCTOR_CHATID, SURGEON, u8"Ясна", u8"Мышако", u8"Михайловна", 5, "https://clck.ru/3Hsiz4", 48);
        addDoctor(doctor);
        doctor = createDoctor(4, DEFAULT_DOCTOR_CHATID, THERAPIST, u8"Екатерина", u8"Камарова", u8"Михайловна", 4, "https://clck.ru/3HsjLd", 49);
        addDoctor(doctor);
        doctor = createDoctor(5, DEFAULT_DOCTOR_CHATID, CARDIOLOGIST, u8"Иванов", u8"Александр", u8"Сергеевич", 5, "https://clck.ru/3Hsjbc", 48);
        addDoctor(doctor);
        doctor = createDoctor(6, DEFAULT_DOCTOR_CHATID, THERAPIST, u8"Смирнов", u8"Иван", u8"Петрович", 10, "https://clck.ru/3Hskik", 50),
        addDoctor(doctor);
        doctor = createDoctor(7, DEFAULT_DOCTOR_CHATID, PEDIATRICIAN, u8"Петрова", u8"Анна", u8"Сергеевна", 8, "https://clck.ru/3Hskpb", 45),
        addDoctor(doctor);
        doctor = createDoctor(8, DEFAULT_DOCTOR_CHATID, SURGEON, u8"Фёдоров", u8"Олег", u8"Анатольевич", 12, "https://clck.ru/3HskxM", 45),
        addDoctor(doctor);
        doctor = createDoctor(9, DEFAULT_DOCTOR_CHATID, CARDIOLOGIST, u8"Иванов", u8"Александр", u8"Сергеевич", 5, "https://clck.ru/3Hsm5n", 48),
        addDoctor(doctor);
        doctor = createDoctor(10, DEFAULT_DOCTOR_CHATID, NEUROLOGIST, u8"Захарова", u8"Мария", u8"Викторовна", 9, "https://clck.ru/3HsmBC", 42),
        addDoctor(doctor);
        doctor = createDoctor(11, DEFAULT_DOCTOR_CHATID, GASTROENTEROLOGIST, u8"Кузнецов", u8"Дмитрий", u8"Евгеньевич", 6, "https://clck.ru/3HsmG3", 50),
        addDoctor(doctor);
        doctor = createDoctor(12, DEFAULT_DOCTOR_CHATID, DERMATOLOGIST, u8"Морозова", u8"Екатерина", u8"Николаевна", 7, "https://clck.ru/3HsmMd", 47),
        addDoctor(doctor);
        doctor = createDoctor(13, DEFAULT_DOCTOR_CHATID, UROLOGIST, u8"Соловьёв", u8"Артём", u8"Михайлович", 11, "https://clck.ru/3HsmRM", 43),
        addDoctor(doctor);
        doctor = createDoctor(15, DEFAULT_DOCTOR_CHATID, OPHTHALMOLOGIST, u8"Беляев", u8"Роман", u8"Сергеевич", 10, "https://clck.ru/3Hsjbc", 49),
        addDoctor(doctor);
        doctor = createDoctor(16, DEFAULT_DOCTOR_CHATID, PHYSIOTHERAPIST, u8"Никитина", u8"Татьяна", u8"Андреевна", 6, "https://clck.ru/3Hsjbc", 43),
        addDoctor(doctor);
        doctor = createDoctor(17, DEFAULT_DOCTOR_CHATID, REHABILITATION_DOCTOR, u8"Васильев", u8"Константин", u8"Петрович", 7, "https://clck.ru/3Hsjbc", 44),
        addDoctor(doctor);
        doctor = createDoctor(18, DEFAULT_DOCTOR_CHATID, SPORTS_MEDICINE, u8"Орлова", u8"Надежда", u8"Васильевна", 5, "https://clck.ru/3Hsjbc", 41),
        addDoctor(doctor);
        doctor = createDoctor(19, DEFAULT_DOCTOR_CHATID, GYNECOLOGIST, u8"Фролов", u8"Алексей", u8"Геннадьевич", 14, "https://clck.ru/3Hsjbc", 47),
        addDoctor(doctor);
        doctor = createDoctor(20, DEFAULT_DOCTOR_CHATID, PSYCHIATRIST, u8"Егорова", u8"Юлия", u8"Владимировна", 9, "https://clck.ru/3Hsjbc", 46),
        addDoctor(doctor);
        doctor = createDoctor(21, DEFAULT_DOCTOR_CHATID, DENTIST, u8"Григорьев", u8"Владимир", u8"Степанович", 8, "https://clck.ru/3Hsjbc", 42),
        addDoctor(doctor);
        doctor = createDoctor(22, DEFAULT_DOCTOR_CHATID, ALLERGIST, u8"Тихонов", u8"Станислав", u8"Николаевич", 6, "https://clck.ru/3Hsjbc", 48),
        addDoctor(doctor);


        doctors = loadDoctor("doctors.json");
    }

    // Освобождение памяти
    cJSON_Delete(doctors);
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

        // Сохранение в файл
        if (!saveDoctor("doctors.json", doctors))
        {
            fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
        }

        //freedoctorData(doctor);
    }

    // Освобождение памяти
    cJSON_Delete(doctors);

    return;
}

/****************************************************************************************************/
STATUS addDoctor(Doctor* doctor)
{
    doctors = loadDoctor("doctors.json");

    if (doctor != NULL)
    {
        // Преобразование в JSON и добавление в массив
        cJSON* doctorJson = doctorToJson(doctor);
        if (doctorJson != NULL)
        {
            cJSON_AddItemToArray(doctors, doctorJson);
            /*freedoctorData(doctor);*/
        }
    }

    // Сохранение в файл
    if (!saveDoctor("doctors.json", doctors))
    {
        fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
    }

    // Освобождение памяти
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
        // Удаляем элемент из объекта
        cJSON_DeleteItemFromArray(doctors, id);
        result = KN_OK;
    }

    saveDoctor("doctors.json", doctors);

    // Освобождение памяти
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

    // Освобождение памяти
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

    // Освобождение памяти
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