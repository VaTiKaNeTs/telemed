#ifndef DOCTOR_DB_H_
#define DOCTOR_DB_H_

#include <stdio.h>
#include <string.h>
#include "../libs/cJSON/cJSON.h"

// ������������ ��������� ��������������
typedef enum
{
    THERAPIST,                    // ��������
    PEDIATRICIAN,                 // �������
    SURGEON,                      // ������
    CARDIOLOGIST,                 // ���������
    NEUROLOGIST,                  // ��������
    GASTROENTEROLOGIST,           // ���������������
    DERMATOLOGIST,                // ����������
    UROLOGIST,                    // ������
    ONCOLOGIST,                   // �������
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
    u8"��������",
    u8"�������",
    u8"������",
    u8"���������",
#if 0
    u8"��������",
    u8"���������������",
    u8"����������",
    u8"������",
    u8"�������",
    u8"�����������",
    u8"�������������",
    u8"������������",
    u8"����������-����",
    u8"���������",
    u8"��������",
    u8"���������� ����� ��������",
    u8"����������",
#endif
    u8"������"
};
#endif

/***************************************************************************//**
 * @struct PatientData
 * @brief ��������� ��� �������� ������ ��������
 *
 * ��� ��������� �������� ��� ����������� ������ � ��������:
 * - ������ ������ (���, �������, ��������)
 * - �������
 * - ���
 *******************************************************************************/
typedef struct {
    int id;                     /**< ���������� ������������� ����� */

    SPECIALITY specialty;       /**< ����������� ������������� */

    char* firstName;             /**< ��� ����� */

    char* lastName;             /**< ������� ����� */

    char* middleName;           /**< �������� ����� */

    int experience;             /**< ���� ������ � ����� */

    char* photo_path;           /**< ���� � ���������� */

    int rating;                 /**< ������� ����� (�� 0 �� 5) */

} Doctor;

/***************************************************************************//**
 * @brief ������� ����� ��������� PatientData
 *
 * @param firstName ��� ��������
 * @param lastName ������� ��������
 * @param middleName �������� ��������
 * @param age ������� ��������
 * @param gender ��� ��������
 *
 * @return ��������� �� ��������� ��������� PatientData ��� NULL � ������ ������
 *******************************************************************************/
Doctor* createDoctor(int id, SPECIALITY specialty, const char* firstName, const char* lastName,
    const char* middleName, float experience, const char* photo_path, float rating);

/***************************************************************************//**
 * @brief ����������� ������, ���������� ��� PatientData
 *
 * @param patient ��������� �� ��������� PatientData ��� ������������
 *******************************************************************************/
void freeDoctor(Doctor* doctor);

/***************************************************************************//**
 * @brief ����������� ��������� PatientData � JSON ������
 *
 * @param patient ��������� �� ��������� PatientData ��� ��������������
 *
 * @return ��������� �� ��������� JSON ������ ��� NULL � ������ ������
 *******************************************************************************/
cJSON* doctorToJson(Doctor* doctor);

/***************************************************************************//**
 * @brief ������� ��������� PatientData �� JSON �������
 *
 * @param json ��������� �� JSON ������ ��� ��������������
 *
 * @return ��������� �� ��������� ��������� PatientData ��� NULL � ������ ������
 *******************************************************************************/
Doctor* jsonToDoctor(cJSON* json);

/***************************************************************************//**
 * @brief ��������� ���� ������ ��������� � JSON ����
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