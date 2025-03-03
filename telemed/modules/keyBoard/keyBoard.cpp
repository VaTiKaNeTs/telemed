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
InlineKeyboardMarkup::Ptr createChooseSpecInlineKeyboard(void)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);

    /* Первая строка */
    vector<InlineKeyboardButton::Ptr> row0;

    InlineKeyboardButton::Ptr specTherapist(new InlineKeyboardButton);
    specTherapist->text = INLINE_KEYBOARD_SPEC_THERAPIST;
    specTherapist->callbackData = INLINE_KEYBOARD_SPEC_THERAPIST;
    row0.push_back(specTherapist);

    InlineKeyboardButton::Ptr specPediatrician(new InlineKeyboardButton);
    specPediatrician->text = INLINE_KEYBOARD_SPEC_PEDIATRICIAN;
    specPediatrician->callbackData = INLINE_KEYBOARD_SPEC_PEDIATRICIAN;
    row0.push_back(specPediatrician);

    InlineKeyboardButton::Ptr specSurgeon(new InlineKeyboardButton);
    specSurgeon->text = INLINE_KEYBOARD_SPEC_SURGEON;
    specSurgeon->callbackData = INLINE_KEYBOARD_SPEC_SURGEON;
    row0.push_back(specSurgeon);

    keyboard->inlineKeyboard.push_back(row0);

    /* Вторая строка */
    vector<InlineKeyboardButton::Ptr> row1;

    InlineKeyboardButton::Ptr specCardiologist(new InlineKeyboardButton);
    specCardiologist->text = INLINE_KEYBOARD_SPEC_CARDIOLOGIST;
    specCardiologist->callbackData = INLINE_KEYBOARD_SPEC_CARDIOLOGIST;
    row1.push_back(specCardiologist);

    InlineKeyboardButton::Ptr specNeurologist(new InlineKeyboardButton);
    specNeurologist->text = INLINE_KEYBOARD_SPEC_NEUROLOGIST;
    specNeurologist->callbackData = INLINE_KEYBOARD_SPEC_NEUROLOGIST;
    row1.push_back(specNeurologist);

    InlineKeyboardButton::Ptr specGastroenterologist(new InlineKeyboardButton);
    specGastroenterologist->text = INLINE_KEYBOARD_SPEC_GASTROENTEROLOGIST;
    specGastroenterologist->callbackData = INLINE_KEYBOARD_SPEC_GASTROENTEROLOGIST;
    row1.push_back(specGastroenterologist);

    keyboard->inlineKeyboard.push_back(row1);

    /* Третья строка */
    vector<InlineKeyboardButton::Ptr> row2;

    InlineKeyboardButton::Ptr specDermatologist(new InlineKeyboardButton);
    specDermatologist->text = INLINE_KEYBOARD_SPEC_DERMATOLOGIST;
    specDermatologist->callbackData = INLINE_KEYBOARD_SPEC_DERMATOLOGIST;
    row2.push_back(specDermatologist);

    InlineKeyboardButton::Ptr specUrologist(new InlineKeyboardButton);
    specUrologist->text = INLINE_KEYBOARD_SPEC_UROLOGIST;
    specUrologist->callbackData = INLINE_KEYBOARD_SPEC_UROLOGIST;
    row2.push_back(specUrologist);

    keyboard->inlineKeyboard.push_back(row2);

    return keyboard;
}

/***********************************************************************************************/
InlineKeyboardMarkup::Ptr createSpecKeyboard(int doctorId)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row0;
    InlineKeyboardButton::Ptr choiсeButton(new InlineKeyboardButton);
    choiсeButton->text = INLINE_KEYBOARD_CHOIСE;
#if 1
    choiсeButton->callbackData = { std::to_string(doctorId) };
#else
    choiсeButton->callbackData = INLINE_KEYBOARD_CHOIСE;
#endif
    row0.push_back(choiсeButton);
    keyboard->inlineKeyboard.push_back(row0);
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
InlineKeyboardMarkup::Ptr createChoiceDateInlineKeyboard(int* days)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row;
    InlineKeyboardButton::Ptr day1(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day2(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day3(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day4(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day5(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day6(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day7(new InlineKeyboardButton);

    day1->text = std::to_string(days[0]);
    day1->callbackData = std::to_string(days[0]);
    row.push_back(day1);

    day2->text = std::to_string(days[1]);
    day2->callbackData = std::to_string(days[1]);
    row.push_back(day2);

    day3->text = std::to_string(days[2]);
    day3->callbackData = std::to_string(days[2]);
    row.push_back(day3);

    day4->text = std::to_string(days[3]);
    day4->callbackData = std::to_string(days[3]);
    row.push_back(day4);

    day5->text = std::to_string(days[4]);
    day5->callbackData = std::to_string(days[4]);
    row.push_back(day5);

    day6->text = std::to_string(days[5]);
    day6->callbackData = std::to_string(days[5]);
    row.push_back(day6);

    day7->text = std::to_string(days[6]);
    day7->callbackData = std::to_string(days[6]);
    row.push_back(day7);

    keyboard->inlineKeyboard.push_back(row);

    return keyboard;
}

/***********************************************************************************************/
InlineKeyboardMarkup::Ptr createChoiceTimeInlineKeyboard(const std::vector<std::string>& timesStr)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row;

    for (const auto& str : timesStr) 
    {
        InlineKeyboardButton::Ptr tmpTime(new InlineKeyboardButton);
        tmpTime->text = str;
        tmpTime->callbackData = str;
        row.push_back(tmpTime);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();
    }

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
