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

/* Клавиатура для меню обратной связи */
ReplyKeyboardRemove::Ptr createFeedbackKeyboard(void);

#endif __KEYBOARD_H_