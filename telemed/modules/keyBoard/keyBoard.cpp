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
ReplyKeyboardRemove::Ptr createFeedbackKeyboard(void)
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
