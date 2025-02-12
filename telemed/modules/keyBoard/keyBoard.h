#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include "../../knTypes.h"

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

/* Клавиатура для стартового меню */
ReplyKeyboardMarkup::Ptr createStartKeyboard(void);

/* Клавиатура для меню личного кабинета */
ReplyKeyboardMarkup::Ptr createAccountKeyboard(void);


ReplyKeyboardRemove::Ptr deleteKeyboard(void);

/* Клавиатура приглашение зарегистрироваться */
InlineKeyboardMarkup::Ptr createRegInlineKeyboard(void);

/* Клавиатура изменение данных пользователя */
InlineKeyboardMarkup::Ptr createAccEditInlineKeyboard(void);

#endif __KEYBOARD_H_