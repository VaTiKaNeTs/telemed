#ifndef DOCTOR_DB_H_
#define DOCTOR_DB_H_


#include "../libs/cJSON/cJSON.h"
#include <stdio.h>
#include <string.h>

#include "../modules/keyBoard/keyBoardCfg.h"

// ������������ ��������� ��������������
typedef enum
{
    DEFAULT_SPEC,                 // ������
    THERAPIST,                    // ��������
    PEDIATRICIAN,                 // �������
    SURGEON,                      // ������
    CARDIOLOGIST,                 // ���������
    NEUROLOGIST,                  // ��������
    GASTROENTEROLOGIST,           // ���������������
    DERMATOLOGIST,                // ����������
    UROLOGIST,                    // ������
    OPHTHALMOLOGIST,              // �����������
    PHYSIOTHERAPIST,              // �������������
    REHABILITATION_DOCTOR,        // ������������
    SPORTS_MEDICINE,              // ����������-����
    GYNECOLOGIST,                 // ���������
    PSYCHIATRIST,                 // ��������
    DENTIST,                      // ���������� ����� ��������
    ALLERGIST,                    // ����������

    OTHER                        // ������
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
    u8"������"
};
#endif

#define PHOTO_PATH_MAX 40

/***************************************************************************//**
 * @struct PatientData
 * @brief ��������� ��� �������� ������ ��������
 *
 * ��� ��������� �������� ��� ����������� ������ � ��������:
 * - ������ ������ (���, �������, ��������)
 * - �������
 * - ���
 *******************************************************************************/
typedef struct 
{
    int id;                     /**< ���������� ������������� ����� */

    long chatId;

    SPECIALITY specialty;       /**< ����������� ������������� */

    char* firstName;             /**< ��� ����� */

    char* lastName;             /**< ������� ����� */

    char* middleName;           /**< �������� ����� */

    int experience;             /**< ���� ������ � ����� */

    char* photo_path;           /**< ���� � ���������� */

    int rating;                 /**< ������� ����� (�� 0 �� 5) */

} Doctor;

/***************************************************************************//**
 * @brief ������� ����� ��������� Doctor
 * @return ��������� �� ��������� ��������� PatientData ��� NULL � ������ ������
 *******************************************************************************/
Doctor* createDoctor(int id, long chatId, SPECIALITY specialty, const char* firstName, const char* lastName,
    const char* middleName, float experience, const char* photo_path, float rating);

/***************************************************************************//**
 * @brief ����������� ������, ���������� ��� Doctor
 *
 * @param patient ��������� �� ��������� PatientData ��� ������������
 *******************************************************************************/
void freeDoctor(Doctor* doctor);

/***************************************************************************//**
 * @brief ����������� ��������� Doctor � JSON ������
 *
 * @param patient ��������� �� ��������� Doctor ��� ��������������
 *
 * @return ��������� �� ��������� JSON ������ ��� NULL � ������ ������
 *******************************************************************************/
cJSON* doctorToJson(Doctor* doctor);

/***************************************************************************//**
 * @brief ������� ��������� Doctor �� JSON �������
 *
 * @param json ��������� �� JSON ������ ��� ��������������
 *
 * @return ��������� �� ��������� ��������� PatientData ��� NULL � ������ ������
 *******************************************************************************/
Doctor* jsonToDoctor(cJSON* json);

/***************************************************************************//**
 * @brief ��������� ���� ������ Doctors � JSON ����
 *
 * @param filename ��� ����� ��� ����������
 * @param patients ��������� �� JSON ������ � ������� ���������
 *
 * @return 1 ��� �������� ����������, 0 � ������ ������
 *******************************************************************************/
int saveDoctor(const char* filename, cJSON* doctor);

/***************************************************************************//**
 * @brief ��������� ���� ������ ��������� �� JSON �����
 *
 * @param filename ��� ����� ��� ��������
 *
 * @return ��������� �� ����������� JSON ������ ��� NULL � ������ ������
 *******************************************************************************/
cJSON* loadDoctor(const char* filename);

#endif // DOCTOR_DB_H_