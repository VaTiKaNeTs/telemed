#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include "../../knTypes.h"

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

/* Клавиатура для стартового меню */
ReplyKeyboardMarkup::Ptr createStartKeyboard(void);

/* Клавиатура для меню записей */
ReplyKeyboardMarkup::Ptr createSessionsKeyboard(void);

/* Клавиатура для меню личного кабинета */
ReplyKeyboardMarkup::Ptr createAccountKeyboard(void);

ReplyKeyboardRemove::Ptr deleteKeyboard(void);

/* Клавиатура для действия с записью */
InlineKeyboardMarkup::Ptr createSessionShowInlineKeyboard(int id);

/* Клавиатура приглашение зарегистрироваться */
InlineKeyboardMarkup::Ptr createRegInlineKeyboard(void);

/* Клавиатура выбора даты. */
/* принимает массив дней которые надо вывести 7 шт */
InlineKeyboardMarkup::Ptr createChoiceDateInlineKeyboard(int day, int doctorId);

/* Клавиатруа выбора времени */
InlineKeyboardMarkup::Ptr createChoiceTimeInlineKeyboard(const std::vector<std::string>& timesStr);

/* Клавиатура выбрать врача */
InlineKeyboardMarkup::Ptr createSpecKeyboard(int doctorId);

/* Клавиатура изменение данных пользователя */
InlineKeyboardMarkup::Ptr createAccEditInlineKeyboard(void);

/* Клавиатура выбора специалиста */
InlineKeyboardMarkup::Ptr createChooseSpecInlineKeyboard(UINT32 page);

#endif __KEYBOARD_H_