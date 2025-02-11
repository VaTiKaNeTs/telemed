#include "user.h"

#include "../../config.h"

#include <stdio.h>

long usersChatId[MAX_CNT_USERS_CHAT_ID] = { 0 };
PROCESS_FLAGS flagCurUserProcess[MAX_CNT_USERS_CHAT_ID] = { 0 };

/* счетчик юзеров */
int usersRegCnt = 0;

/****************************************************************************************************/
INT32 findUser(long chatId)
{
    for (UINT32 i = 0; i < MAX_CNT_USERS_CHAT_ID; i++)
    {
        if (usersChatId[i] == chatId)
        {
            return i;
        }
    }
    return -1;
}

/****************************************************************************************************/
void deleteUser(long chatId)
{
    for (UINT32 i = 0; i < MAX_CNT_USERS_CHAT_ID; i++)
    {
        if (usersChatId[i] == chatId)
        {
            usersChatId[i] = 0;
        }
    }
}

/****************************************************************************************************/
void setUserProcess(long chatId, PROCESS_FLAGS flag)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        flagCurUserProcess[user] = flag;
    }
}

/****************************************************************************************************/
PROCESS_FLAGS getUserProcess(long chatId)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        return flagCurUserProcess[user];
    }
    else
    {
        return FLAG_NONE;
    }
   
}

/****************************************************************************************************/
void saveChatId(long chatId)
{
    UINT8 flagUserReg = 0;
    /* Проверяем что такого id у нас не зарестрировано */
    for (UINT32 i = 0; i < MAX_CNT_USERS_CHAT_ID; i++)
    {
        if (usersChatId[i] == chatId)
        {
            flagUserReg = 1;
            break;
        }
    }

    /* Если пользователь не зарегестрирован, регистриуем его */
    if (!flagUserReg)
    {
        usersChatId[usersRegCnt++] = chatId;
        printf("Registrated new users with chatid: %d", chatId);
    }
}
