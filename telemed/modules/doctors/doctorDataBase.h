#ifndef DOCTOR_DB_H_
#define DOCTOR_DB_H_


#include "../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <string.h>

#include "../modules/keyBoard/keyBoardCfg.h"

// Перечисление возможных специальностей
typedef enum
{
    DEFAULT_SPEC,                 // Дефолт
    THERAPIST,                    // Терапевт
    PEDIATRICIAN,                 // Педиатр
    SURGEON,                      // Хирург
    CARDIOLOGIST,                 // Кардиолог
    NEUROLOGIST,                  // Невролог
    GASTROENTEROLOGIST,           // Гастроэнтеролог
    DERMATOLOGIST,                // Дерматолог
    UROLOGIST,                    // Уролог
    OPHTHALMOLOGIST,              // Офтальмолог
    PHYSIOTHERAPIST,              // Физиотерапевт
    REHABILITATION_DOCTOR,        // Реабилитолог
    SPORTS_MEDICINE,              // Спортивный-врач
    GYNECOLOGIST,                 // Гинеколог
    PSYCHIATRIST,                 // Психиатр
    DENTIST,                      // Стоматолог общей практики
    ALLERGIST,                    // Аллерголог

    OTHER                        // Прочее
} SPECIALITY;

#if 1
const char* const SPECIALTY_NAMES[] =
{
    u8"Default",
    INLINE_KEYBOARD_SPEC_THERAPIST,
    INLINE_KEYBOARD_SPEC_PEDIATRICIAN,
    INLINE_KEYBOARD_SPEC_SURGEON,
    INLINE_KEYBOARD_SPEC_CARDIOLOGIST,
    INLINE_KEYBOARD_SPEC_NEUROLOGIST,
    INLINE_KEYBOARD_SPEC_GASTROENTEROLOGIST,
    INLINE_KEYBOARD_SPEC_DERMATOLOGIST,
    INLINE_KEYBOARD_SPEC_UROLOGIST,
    INLINE_KEYBOARD_SPEC_OPHTHALMOLOGIST,
    INLINE_KEYBOARD_SPEC_PHYSIOTHERAPIST,
    INLINE_KEYBOARD_SPEC_REHABILITATION_DOCTOR,
    INLINE_KEYBOARD_SPEC_SPORTS_MEDICINE,
    INLINE_KEYBOARD_SPEC_GYNECOLOGIST,
    INLINE_KEYBOARD_SPEC_PSYCHIATRIST,
    INLINE_KEYBOARD_SPEC_DENTIST,
    INLINE_KEYBOARD_SPEC_ALLERGIST,
    u8"Прочее"
};
#endif

#define PHOTO_PATH_MAX 40

/***************************************************************************//**
 * @struct PatientData
 * @brief Структура для хранения данных пациента
 *
 * Эта структура содержит все необходимые данные о пациенте:
 * - личные данные (имя, фамилия, отчество)
 * - возраст
 * - пол
 *******************************************************************************/
typedef struct 
{
    int id;                     /**< Уникальный идентификатор врача */

    long chatId;

    SPECIALITY specialty;       /**< Медицинская специализация */

    char* firstName;             /**< Имя врача */

    char* lastName;             /**< Фамилия врача */

    char* middleName;           /**< Отчество врача */

    int experience;             /**< Стаж работы в годах */

    char* photo_path;           /**< Путь к фотографии */

    int rating;                 /**< Рейтинг врача (от 0 до 5) */

} Doctor;

/***************************************************************************//**
 * @brief Создает новый экземпляр Doctor
 * @return Указатель на созданную структуру PatientData или NULL в случае ошибки
 *******************************************************************************/
Doctor* createDoctor(int id, long chatId, SPECIALITY specialty, const char* firstName, const char* lastName,
    const char* middleName, float experience, const char* photo_path, float rating);

/***************************************************************************//**
 * @brief Освобождает память, выделенную для Doctor
 *
 * @param patient Указатель на структуру PatientData для освобождения
 *******************************************************************************/
void freeDoctor(Doctor* doctor);

/***************************************************************************//**
 * @brief Преобразует структуру Doctor в JSON объект
 *
 * @param patient Указатель на структуру Doctor для преобразования
 *
 * @return Указатель на созданный JSON объект или NULL в случае ошибки
 *******************************************************************************/
cJSON* doctorToJson(Doctor* doctor);

/***************************************************************************//**
 * @brief Создает структуру Doctor из JSON объекта
 *
 * @param json Указатель на JSON объект для преобразования
 *
 * @return Указатель на созданную структуру PatientData или NULL в случае ошибки
 *******************************************************************************/
Doctor* jsonToDoctor(cJSON* json);

/***************************************************************************//**
 * @brief Сохраняет базу данных Doctors в JSON файл
 *
 * @param filename Имя файла для сохранения
 * @param patients Указатель на JSON массив с данными пациентов
 *
 * @return 1 при успешном сохранении, 0 в случае ошибки
 *******************************************************************************/
int saveDoctor(const char* filename, cJSON* doctor);

/***************************************************************************//**
 * @brief Загружает базу данных пациентов из JSON файла
 *
 * @param filename Имя файла для загрузки
 *
 * @return Указатель на загруженный JSON объект или NULL в случае ошибки
 *******************************************************************************/
cJSON* loadDoctor(const char* filename);

#endif // DOCTOR_DB_H_