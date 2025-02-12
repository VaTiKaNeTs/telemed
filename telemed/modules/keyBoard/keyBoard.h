#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include "../../knTypes.h"

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

/* ���������� ��� ���������� ���� */
ReplyKeyboardMarkup::Ptr createStartKeyboard(void);

/* ���������� ��� ���� ������� �������� */
ReplyKeyboardMarkup::Ptr createAccountKeyboard(void);


ReplyKeyboardRemove::Ptr deleteKeyboard(void);

/* ���������� ����������� ������������������ */
InlineKeyboardMarkup::Ptr createRegInlineKeyboard(void);

/* ���������� ��������� ������ ������������ */
InlineKeyboardMarkup::Ptr createAccEditInlineKeyboard(void);

#endif __KEYBOARD_H_