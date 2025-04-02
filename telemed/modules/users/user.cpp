#include "user.h"


#include "../../config.h"

#include <stdio.h>

std::int64_t usersChatId[MAX_CNT_USERS_CHAT_ID] = { 0 };
USER_PROCESS flagCurUserProcess[MAX_CNT_USERS_CHAT_ID] = { USER_PROCESS_NONE };
SPECIALITY userCurSpec[MAX_CNT_USERS_CHAT_ID] = { DEFAULT_SPEC };
int userCurDoctorId[MAX_CNT_USERS_CHAT_ID] = { 0 };
int userCurDay[MAX_CNT_USERS_CHAT_ID] = { 0 };


/* счетчик юзеров */
int usersRegCnt = 0;

/****************************************************************************************************/
INT32 findUser(std::int64_t chatId)
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
void deleteUser(std::int64_t chatId)
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
void setUserProcess(std::int64_t chatId, USER_PROCESS flag)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        flagCurUserProcess[user] = flag;
    }
}

/****************************************************************************************************/
USER_PROCESS getUserProcess(std::int64_t chatId)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        return flagCurUserProcess[user];
    }
    else
    {
        return USER_PROCESS_NONE;
    }
   
}

/****************************************************************************************************/
void setUserSpec(std::int64_t chatId, SPECIALITY spec)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        userCurSpec[user] = spec;
    }
}

/****************************************************************************************************/
SPECIALITY getUserSpec(std::int64_t chatId)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        return userCurSpec[user];
    }
    else
    {
        return DEFAULT_SPEC;
    }
}


/****************************************************************************************************/
void setUserDoctorId(std::int64_t chatId, int doctorId)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        userCurDoctorId[user] = doctorId;
    }
}

/****************************************************************************************************/
int getUserDoctorId(std::int64_t chatId)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        return userCurDoctorId[user];
    }
    else
    {
        return 0;
    }
}

/****************************************************************************************************/
void setUserDay(std::int64_t chatId, int day)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        userCurDay[user] = day;
    }
}

/****************************************************************************************************/
int getUserDay(std::int64_t chatId)
{
    INT32 user = -1;
    user = findUser(chatId);
    if (user != -1)
    {
        return userCurDay[user];
    }
    else
    {
        return 0;
    }
}

/****************************************************************************************************/
void saveChatId(std::int64_t chatId)
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
