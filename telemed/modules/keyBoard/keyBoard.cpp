#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <vector>

#include "keyBoard.h"
#include "keyBoardCfg.h"

using namespace std;
using namespace TgBot;
/***********************************************************************************************/
void createOneColumnKeyboard(const vector<string>& buttonStrings, ReplyKeyboardMarkup::Ptr& kb);
void createKeyboard(const vector<vector<string>>& buttonLayout, ReplyKeyboardMarkup::Ptr& kb);
void removeKeyboard(ReplyKeyboardRemove::Ptr& kb);

/***********************************************************************************************/
ReplyKeyboardMarkup::Ptr createStartKeyboard(void)
{
    ReplyKeyboardMarkup::Ptr keyboardWithLayout(new ReplyKeyboardMarkup);
    createKeyboard(
        {
            {KEYBOARD_ACCOUNT, KEYBOARD_MAKE_AN_APPOINTMENT, KEYBOARD_SESSIONS},
        }, keyboardWithLayout);
    keyboardWithLayout->resizeKeyboard = TRUE;

    return keyboardWithLayout;
}

/***********************************************************************************************/
ReplyKeyboardMarkup::Ptr createAccountKeyboard(void)
{
    ReplyKeyboardMarkup::Ptr keyboardWithLayout(new ReplyKeyboardMarkup);
    createKeyboard(
        {
            {KEYBOARD_ACCOUNT_EDIT, KEYBOARD_ACCOUNT_BACK},
        }, keyboardWithLayout);

    return keyboardWithLayout;
}

/***********************************************************************************************/
InlineKeyboardMarkup::Ptr createAccEditInlineKeyboard(void)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    
    /* Первая строка */
    vector<InlineKeyboardButton::Ptr> row0;

    InlineKeyboardButton::Ptr firstName(new InlineKeyboardButton);
    firstName->text = INLINE_KEYBOARD_ACCOUNT_EDIT_FIRSTNAME;
    firstName->callbackData = INLINE_KEYBOARD_ACCOUNT_EDIT_FIRSTNAME;
    row0.push_back(firstName);

    InlineKeyboardButton::Ptr lastName(new InlineKeyboardButton);
    lastName->text = INLINE_KEYBOARD_ACCOUNT_EDIT_LASTNAME;
    lastName->callbackData = INLINE_KEYBOARD_ACCOUNT_EDIT_LASTNAME;
    row0.push_back(lastName);

    InlineKeyboardButton::Ptr middleName(new InlineKeyboardButton);
    middleName->text = INLINE_KEYBOARD_ACCOUNT_EDIT_MIDDLENAME;
    middleName->callbackData = INLINE_KEYBOARD_ACCOUNT_EDIT_MIDDLENAME;
    row0.push_back(middleName);

    keyboard->inlineKeyboard.push_back(row0);
    
    /* Вторая строка */
    vector<InlineKeyboardButton::Ptr> row1;

    InlineKeyboardButton::Ptr gender(new InlineKeyboardButton);
    gender->text = INLINE_KEYBOARD_ACCOUNT_EDIT_GENDER;
    gender->callbackData = INLINE_KEYBOARD_ACCOUNT_EDIT_GENDER;
    row1.push_back(gender);

    InlineKeyboardButton::Ptr age(new InlineKeyboardButton);
    age->text = INLINE_KEYBOARD_ACCOUNT_EDIT_AGE;
    age->callbackData = INLINE_KEYBOARD_ACCOUNT_EDIT_AGE;
    row1.push_back(age);

    keyboard->inlineKeyboard.push_back(row1);

    return keyboard;
}

/***********************************************************************************************/
InlineKeyboardMarkup::Ptr createRegInlineKeyboard(void)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row0;
    InlineKeyboardButton::Ptr checkButton(new InlineKeyboardButton);
    checkButton->text = INLINE_KEYBOARD_REGISTRATION;
    checkButton->callbackData = INLINE_KEYBOARD_REGISTRATION;
    row0.push_back(checkButton);
    keyboard->inlineKeyboard.push_back(row0);
    return keyboard;
}

/***********************************************************************************************/
ReplyKeyboardRemove::Ptr deleteKeyboard(void)
{
    ReplyKeyboardRemove::Ptr keyboardWithLayout(new ReplyKeyboardRemove);
    removeKeyboard(keyboardWithLayout);

    return keyboardWithLayout;
}

/***********************************************************************************************/
void createOneColumnKeyboard(const vector<string>& buttonStrings, ReplyKeyboardMarkup::Ptr& kb)
{
    for (size_t i = 0; i < buttonStrings.size(); ++i) 
    {
        vector<KeyboardButton::Ptr> row;
        KeyboardButton::Ptr button(new KeyboardButton);
        button->text = buttonStrings[i];
        row.push_back(button);
        kb->selective = true;
        kb->keyboard.push_back(row);
        kb->resizeKeyboard = true;
    }
}

/***********************************************************************************************/
void createKeyboard(const vector<vector<string>>& buttonLayout, ReplyKeyboardMarkup::Ptr& kb)
{
    for (size_t i = 0; i < buttonLayout.size(); ++i)
    {
        vector<KeyboardButton::Ptr> row;
        for (size_t j = 0; j < buttonLayout[i].size(); ++j)
        {
            KeyboardButton::Ptr button(new KeyboardButton);
            button->text = buttonLayout[i][j];
            row.push_back(button);
        }
        kb->selective = true;
        kb->keyboard.push_back(row);
        kb->resizeKeyboard = true;
    }
}

/***********************************************************************************************/
/* Удаление клавиатуры */
void removeKeyboard(ReplyKeyboardRemove::Ptr& kb)
{
    kb->selective = true;
}
