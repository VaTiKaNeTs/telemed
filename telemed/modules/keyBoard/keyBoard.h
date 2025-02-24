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

/* ���������� ������ ����. */
/* ��������� ������ ���� ������� ���� ������� 7 �� */
InlineKeyboardMarkup::Ptr createChoiceDateInlineKeyboard(int* days);

/* ���������� ������� ����� */
InlineKeyboardMarkup::Ptr createSpecKeyboard(int doctorId);

/* ���������� ��������� ������ ������������ */
InlineKeyboardMarkup::Ptr createAccEditInlineKeyboard(void);

/* ���������� ������ ����������� */
InlineKeyboardMarkup::Ptr createChooseSpecInlineKeyboard(void);

#endif __KEYBOARD_H_