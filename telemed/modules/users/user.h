#pragma once

#include "../../knTypes.h"

typedef enum
{
	FLAG_NONE = 0,
	FLAG_REG_TABLE,
	FLAG_FEEDBACK,

	FLAG_PROCESS_CNT,
} PROCESS_FLAGS;

/* Поиск юзера */
INT32 findUser(long chatId);

/* Удаление юзера */
void deleteUser(long chatId);

/* Установить флаг процесса для пользователя */
void setUserProcess(long chatId, PROCESS_FLAGS flag);

/* Получить флаг процесса пользователя */
PROCESS_FLAGS getUserProcess(long chatId);

/* Сохраняем chatId пользователя */
void saveChatId(long chatId);
