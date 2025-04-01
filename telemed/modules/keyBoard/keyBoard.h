#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include "../../knTypes.h"

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

/* ���������� ��� ���������� ���� */
ReplyKeyboardMarkup::Ptr createStartKeyboard(void);

/* ���������� ��� ���� ������� */
ReplyKeyboardMarkup::Ptr createSessionsKeyboard(void);

/* ���������� ��� ���� ������� �������� */
ReplyKeyboardMarkup::Ptr createAccountKeyboard(void);

ReplyKeyboardRemove::Ptr deleteKeyboard(void);

/* ���������� ��� �������� � ������� */
InlineKeyboardMarkup::Ptr createSessionShowInlineKeyboard(int id);

/* ���������� ����������� ������������������ */
InlineKeyboardMarkup::Ptr createRegInlineKeyboard(void);

/* ���������� ������ ����. */
/* ��������� ������ ���� ������� ���� ������� 7 �� */
InlineKeyboardMarkup::Ptr createChoiceDateInlineKeyboard(int day, int doctorId);

/* ���������� ������ ������� */
InlineKeyboardMarkup::Ptr createChoiceTimeInlineKeyboard(const std::vector<std::string>& timesStr);

/* ���������� ������� ����� */
InlineKeyboardMarkup::Ptr createSpecKeyboard(int doctorId);

/* ���������� ��������� ������ ������������ */
InlineKeyboardMarkup::Ptr createAccEditInlineKeyboard(void);

/* ���������� ������ ����������� */
InlineKeyboardMarkup::Ptr createChooseSpecInlineKeyboard(UINT32 page);

#endif __KEYBOARD_H_