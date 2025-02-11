// telemed.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <locale.h>

#include <iostream>
#include <tgbot/tgbot.h>

#include "knTypes.h"

#include "config.h"
#include "modules/botCmd/botCmd.h"

#include "Windows.h"

#include <stdio.h>
#include <string.h>
#include "libs/cJSON/cJSON.h"
#include "modules/dataBase/dataBase.h"



using namespace std;
using namespace TgBot;

/****************************************************************************************************/
#define BOT_API_TOKEN "8191200173:AAFQbZZ5mKIWIba4WowIXvJ0ymjMmjewEm4"

/****************************************************************************************************/
void tgLoop(Bot& bot);

/****************************************************************************************************/

// Функция для создания тестового JSON объекта
cJSON* create_test_json() {
    // Создаем корневой объект
    cJSON* root = cJSON_CreateObject();

    // Добавляем простые значения
    cJSON_AddStringToObject(root, "имя", "Тестовый объект");
    cJSON_AddNumberToObject(root, "число", 42);
    cJSON_AddTrueToObject(root, "флаг");  // добавляем true значение

    // Создаем вложенный объект
    cJSON* address = cJSON_CreateObject();
    cJSON_AddStringToObject(address, "город", "Москва");
    cJSON_AddStringToObject(address, "улица", "Ленина");
    cJSON_AddNumberToObject(address, "дом", 123);
    cJSON_AddItemToObject(root, "адрес", address);

    // Создаем массив
    cJSON* colors = cJSON_CreateArray();
    cJSON_AddItemToArray(colors, cJSON_CreateString("красный"));
    cJSON_AddItemToArray(colors, cJSON_CreateString("зеленый"));
    cJSON_AddItemToArray(colors, cJSON_CreateString("синий"));
    cJSON_AddItemToObject(root, "цвета", colors);

    return root;
}

// Функция для чтения JSON данных
void read_json_data(cJSON* json) {
    // Проверяем корневой JSON
    if (json == NULL) {
        fprintf(stderr, "Ошибка: корневой JSON объект не найден\n");
        return;
    }

    // Чтение простых значений
    printf("Простые значения:\n");

    // Имя
    cJSON* name = cJSON_GetObjectItem(json, "имя");
    if (name != NULL && name->type == cJSON_String) {
        printf("- Имя: %s\n", name->valuestring);
    }
    else {
        printf("- Имя: не найдено или неверный тип\n");
    }

    // Число
    cJSON* number = cJSON_GetObjectItem(json, "число");
    if (number != NULL && number->type == cJSON_Number) {
        printf("- Число: %d\n", (int)number->valuedouble);
    }
    else {
        printf("- Число: не найдено или неверный тип\n");
    }

    // Флаг
    cJSON* flag = cJSON_GetObjectItem(json, "флаг");
    if (flag != NULL && flag->type == cJSON_True || flag->type == cJSON_False) {
        printf("- Флаг: %s\n", flag->type == cJSON_True ? "да" : "нет");
    }
    else {
        printf("- Флаг: не найден или неверный тип\n");
    }

    // Остальной код остается без изменений...
}

// Функция для парсинга JSON строки
void parse_json_string(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (json != NULL) {
        read_json_data(json);
        cJSON_Delete(json);  // Освобождаем память
    }
    else {
        fprintf(stderr, "Ошибка парсинга JSON!\n");
    }
}


/****************************************************************************************************/
int main()
{
    Bot bot(BOT_API_TOKEN);

    botCmdInit(bot);


    setlocale(LC_ALL, "Russian");

#if 0
    // Создаем тестовый JSON объект
    cJSON* json = create_test_json();

    // Преобразуем его в строку
    char* json_str = cJSON_Print(json);
    printf("Созданный JSON:\n%s\n\n", json_str);

    // Освобождаем память от строки
    free(json_str);

    // Тестируем парсинг строки
    const char* test_str = "{\"имя\":\"Новый объект\",\"число\":123,\"флаг\":false}";
    printf("Тестирование парсинга JSON строки:\n");
    parse_json_string(test_str);

    // Освобождаем память от корневого объекта
    cJSON_Delete(json);
#endif



#if 1

    // Создание массива для хранения пациентов
    /*cJSON* patients = cJSON_CreateArray();*/
    cJSON* patients = loadPatientDatabase("patients.json");
    if (patients == NULL) {
        fprintf(stderr, "Ошибка: не удалось создать массив пациентов\n");
        return 1;
    }

    // Добавление нового пациента
    //PatientData* patient = createPatientData(
    //    0,
    //    123456789,
    //    "Иван",
    //    "Петров",
    //    "Сергеевич",
    //    30,
    //    "мужской"
    //);
    PatientData* patient = createPatientData(
        1,
        99999999,
        "Кирилл",
        "Таровик",
        "Михайлович",
        23,
        "мужской"
    );

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
#endif

#if 0
    // Пример 2: Поиск пациента по фамилии
    cJSON* patients = loadPatientDatabase("patients.json");
    if (patients != NULL) 
    {
        int size = cJSON_GetArraySize(patients);
        for (int i = 0; i < size; i++) 
        {
            cJSON* patientJson = cJSON_GetArrayItem(patients, i);
            cJSON* lastName = cJSON_GetObjectItem(patientJson, "lastName");
            if (lastName != NULL && strcmp(lastName->valuestring, "Петров") == 0) 
            {
                PatientData* patient = jsonToPatient(patientJson);
                if (patient != NULL) 
                {
                    printf("Найден пациент:\n");
                    printf("- Имя: %s\n", patient->firstName);
                    printf("- Фамилия: %s\n", patient->lastName);
                    printf("- Отчество: %s\n", patient->middleName);
                    printf("- Возраст: %d\n", patient->age);
                    printf("- Пол: %s\n", patient->gender);
                    freePatientData(patient);
                    break;
                }
            }
        }
        cJSON_Delete(patients);
    }
#endif






    botCmdStart(bot);
    BotCmdAny(bot);

    tgLoop(bot);

    return 0;
}

/****************************************************************************************************/
void tgLoop(Bot& bot)
{
    signal(SIGINT, [](int s)
        {
            printf("SIGINT got\n");
            exit(0);
        });

    try
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (exception& e)
    {
        printf("error: %s\n", e.what());
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
