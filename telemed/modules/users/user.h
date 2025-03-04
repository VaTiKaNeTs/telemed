#pragma once

#include "../../knTypes.h"

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

	USER_PROCESS_CHOOSE_SPECIALIT,
	USER_PROCESS_CHOISE_SPEC,
	USER_PROCESS_CHOISE_DATE,
	USER_PROCESS_CHOISE_TIME,

	USER_PROCESS_CNT
} USER_PROCESS;

/* ����� ����� */
INT32 findUser(long chatId);

/* �������� ����� */
void deleteUser(long chatId);

/* ���������� ���� �������� ��� ������������ */
void setUserProcess(long chatId, USER_PROCESS flag);

/* �������� ���� �������� ������������ */
USER_PROCESS getUserProcess(long chatId);

/* ��������� chatId ������������ */
void saveChatId(long chatId);
