#pragma once

#include "../../knTypes.h"

typedef enum
{
	FLAG_NONE = 0,
	FLAG_REG_TABLE,
	FLAG_FEEDBACK,

	FLAG_PROCESS_CNT,
} PROCESS_FLAGS;

/* ����� ����� */
INT32 findUser(long chatId);

/* �������� ����� */
void deleteUser(long chatId);

/* ���������� ���� �������� ��� ������������ */
void setUserProcess(long chatId, PROCESS_FLAGS flag);

/* �������� ���� �������� ������������ */
PROCESS_FLAGS getUserProcess(long chatId);

/* ��������� chatId ������������ */
void saveChatId(long chatId);
