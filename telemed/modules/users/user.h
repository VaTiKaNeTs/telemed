#pragma once

#include "../../knTypes.h"
#include "../doctors/doctorDataBase.h"

typedef enum
{
	USER_PROCESS_NONE = 0,
	USER_PROCESS_MAIN_MENU,
	USER_PROCESS_SESSION,
	USER_PROCESS_ACCOUNT,
	USER_PROCESS_ACCOUNT_EDIT,
	USER_PROCESS_GET_FIRSTNAME_REG,
	USER_PROCESS_GET_FIRSTNAME,
	USER_PROCESS_GET_LASTNAME,
	USER_PROCESS_GET_MIDDLENAME,
	USER_PROCESS_GET_AGE,
	USER_PROCESS_GET_SEX,

	USER_PROCESS_CHOOSE_SPECIALIT_0,
	USER_PROCESS_CHOOSE_SPECIALIT_1,
	USER_PROCESS_CHOISE_SPEC,
	USER_PROCESS_CHOISE_DATE,
	USER_PROCESS_CHOISE_TIME,

	USER_PROCESS_CNT
} USER_PROCESS;

/* ����� ����� */
INT32 findUser(std::int64_t chatId);

/* �������� ����� */
void deleteUser(std::int64_t chatId);

/* ���������� ���� �������� ��� ������������ */
void setUserProcess(std::int64_t chatId, USER_PROCESS flag);

/* �������� ���� �������� ������������ */
USER_PROCESS getUserProcess(std::int64_t chatId);

/* ���������� ���� ����������� ��� �������� */
void setUserSpec(std::int64_t chatId, SPECIALITY spec);

/* ���������� ���� ������� */
void setUserDoctorId(std::int64_t chatId, int doctorId);

/* �������� ���� ������� */
int getUserDoctorId(std::int64_t chatId);

/* ���������� ���� ������ ����������� */
void setUserDay(std::int64_t chatId, int day);

/* �������� ���� ������ ����������� */
int getUserDay(std::int64_t chatId);

/* �������� ���� ����������� ��� ������ */
SPECIALITY getUserSpec(std::int64_t chatId);

/* ��������� chatId ������������ */
void saveChatId(std::int64_t chatId);
