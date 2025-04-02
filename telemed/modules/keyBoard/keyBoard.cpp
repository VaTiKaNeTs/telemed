#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <vector>

#include "keyBoard.h"
#include "keyBoardCfg.h"

#include "../modules/general/general.h"

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
ReplyKeyboardMarkup::Ptr createSessionsKeyboard(void)
{
    ReplyKeyboardMarkup::Ptr keyboardWithLayout(new ReplyKeyboardMarkup);
    createKeyboard(
        {
            {KEYBOARD_ACCOUNT_BACK},
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
InlineKeyboardMarkup::Ptr createChooseSpecInlineKeyboard(UINT32 page)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);

    if (page == 0)
    {
        /* Первая строка */
        vector<InlineKeyboardButton::Ptr> row0;

        InlineKeyboardButton::Ptr spec00(new InlineKeyboardButton);
        spec00->text = INLINE_KEYBOARD_SPEC_THERAPIST;
        spec00->callbackData = INLINE_KEYBOARD_SPEC_THERAPIST;
        row0.push_back(spec00);

        InlineKeyboardButton::Ptr spec01(new InlineKeyboardButton);
        spec01->text = INLINE_KEYBOARD_SPEC_PEDIATRICIAN;
        spec01->callbackData = INLINE_KEYBOARD_SPEC_PEDIATRICIAN;
        row0.push_back(spec01);

        InlineKeyboardButton::Ptr spec02(new InlineKeyboardButton);
        spec02->text = INLINE_KEYBOARD_SPEC_SURGEON;
        spec02->callbackData = INLINE_KEYBOARD_SPEC_SURGEON;
        row0.push_back(spec02);

        keyboard->inlineKeyboard.push_back(row0);

        /* Вторая строка */
        vector<InlineKeyboardButton::Ptr> row1;

        InlineKeyboardButton::Ptr spec10(new InlineKeyboardButton);
        spec10->text = INLINE_KEYBOARD_SPEC_CARDIOLOGIST;
        spec10->callbackData = INLINE_KEYBOARD_SPEC_CARDIOLOGIST;
        row1.push_back(spec10);

        InlineKeyboardButton::Ptr spec11(new InlineKeyboardButton);
        spec11->text = INLINE_KEYBOARD_SPEC_NEUROLOGIST;
        spec11->callbackData = INLINE_KEYBOARD_SPEC_NEUROLOGIST;
        row1.push_back(spec11);

        InlineKeyboardButton::Ptr spec12(new InlineKeyboardButton);
        spec12->text = INLINE_KEYBOARD_SPEC_GASTROENTEROLOGIST;
        spec12->callbackData = INLINE_KEYBOARD_SPEC_GASTROENTEROLOGIST;
        row1.push_back(spec12);

        keyboard->inlineKeyboard.push_back(row1);

        /* Третья строка */
        vector<InlineKeyboardButton::Ptr> row2;

        InlineKeyboardButton::Ptr spec20(new InlineKeyboardButton);
        spec20->text = INLINE_KEYBOARD_SPEC_DERMATOLOGIST;
        spec20->callbackData = INLINE_KEYBOARD_SPEC_DERMATOLOGIST;
        row2.push_back(spec20);

        InlineKeyboardButton::Ptr spec21(new InlineKeyboardButton);
        spec21->text = INLINE_KEYBOARD_SPEC_UROLOGIST;
        spec21->callbackData = INLINE_KEYBOARD_SPEC_UROLOGIST;
        row2.push_back(spec21);

        keyboard->inlineKeyboard.push_back(row2);
    }
    else if (page == 1)
    {
        /* Первая строка */
        vector<InlineKeyboardButton::Ptr> row0;

        InlineKeyboardButton::Ptr spec00(new InlineKeyboardButton);
        spec00->text = INLINE_KEYBOARD_SPEC_OPHTHALMOLOGIST;
        spec00->callbackData = INLINE_KEYBOARD_SPEC_OPHTHALMOLOGIST;
        row0.push_back(spec00);

        InlineKeyboardButton::Ptr spec01(new InlineKeyboardButton);
        spec01->text = INLINE_KEYBOARD_SPEC_PHYSIOTHERAPIST;
        spec01->callbackData = INLINE_KEYBOARD_SPEC_PHYSIOTHERAPIST;
        row0.push_back(spec01);

        InlineKeyboardButton::Ptr spec02(new InlineKeyboardButton);
        spec02->text = INLINE_KEYBOARD_SPEC_REHABILITATION_DOCTOR;
        spec02->callbackData = INLINE_KEYBOARD_SPEC_REHABILITATION_DOCTOR;
        row0.push_back(spec02);

        keyboard->inlineKeyboard.push_back(row0);

        /* Вторая строка */
        vector<InlineKeyboardButton::Ptr> row1;

        InlineKeyboardButton::Ptr spec10(new InlineKeyboardButton);
        spec10->text = INLINE_KEYBOARD_SPEC_SPORTS_MEDICINE;
        spec10->callbackData = INLINE_KEYBOARD_SPEC_SPORTS_MEDICINE;
        row1.push_back(spec10);

        InlineKeyboardButton::Ptr spec11(new InlineKeyboardButton);
        spec11->text = INLINE_KEYBOARD_SPEC_GYNECOLOGIST;
        spec11->callbackData = INLINE_KEYBOARD_SPEC_GYNECOLOGIST;
        row1.push_back(spec11);

        InlineKeyboardButton::Ptr spec12(new InlineKeyboardButton);
        spec12->text = INLINE_KEYBOARD_SPEC_PSYCHIATRIST;
        spec12->callbackData = INLINE_KEYBOARD_SPEC_PSYCHIATRIST;
        row1.push_back(spec12);

        keyboard->inlineKeyboard.push_back(row1);

        /* Третья строка */
        vector<InlineKeyboardButton::Ptr> row2;

        InlineKeyboardButton::Ptr spec20(new InlineKeyboardButton);
        spec20->text = INLINE_KEYBOARD_SPEC_DENTIST;
        spec20->callbackData = INLINE_KEYBOARD_SPEC_DENTIST;
        row2.push_back(spec20);

        InlineKeyboardButton::Ptr spec21(new InlineKeyboardButton);
        spec21->text = INLINE_KEYBOARD_SPEC_ALLERGIST;
        spec21->callbackData = INLINE_KEYBOARD_SPEC_ALLERGIST;
        row2.push_back(spec21);

        keyboard->inlineKeyboard.push_back(row2);
    }
    

    /* Четвертая строка */
    vector<InlineKeyboardButton::Ptr> row3;

    InlineKeyboardButton::Ptr left(new InlineKeyboardButton);
    left->text = KEYBOARD_LEFT;
    left->callbackData = KEYBOARD_LEFT;
    row3.push_back(left);

    InlineKeyboardButton::Ptr right(new InlineKeyboardButton);
    right->text = KEYBOARD_RIGHT;
    right->callbackData = KEYBOARD_RIGHT;
    row3.push_back(right);

    keyboard->inlineKeyboard.push_back(row3);

    /* Пятая строка */
    vector<InlineKeyboardButton::Ptr> row4;

    InlineKeyboardButton::Ptr back(new InlineKeyboardButton);
    back->text = KEYBOARD_ACCOUNT_BACK;
    back->callbackData = KEYBOARD_ACCOUNT_BACK;
    row4.push_back(back);

    keyboard->inlineKeyboard.push_back(row4);

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
InlineKeyboardMarkup::Ptr createChoiceDateInlineKeyboard(int day, int doctorId)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row;
    vector<InlineKeyboardButton::Ptr> row1;
    InlineKeyboardButton::Ptr day1(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day2(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day3(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day4(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day5(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day6(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr day7(new InlineKeyboardButton);

    day1->text = std::to_string(dayOfMonth(day, 0));
    day1->callbackData = std::to_string(day) + " " + std::to_string(doctorId);
    row.push_back(day1);
    
    day2->text = std::to_string(dayOfMonth(day + 1, 0));
    day2->callbackData = std::to_string(day + 1) + " " + std::to_string(doctorId);
    row.push_back(day2);

    day3->text = std::to_string(dayOfMonth(day + 2, 0));
    day3->callbackData = std::to_string(day + 2) + " " + std::to_string(doctorId);
    row.push_back(day3);

    day4->text = std::to_string(dayOfMonth(day + 3, 0));
    day4->callbackData = std::to_string(day + 3) + " " + std::to_string(doctorId);
    row.push_back(day4);

    day5->text = std::to_string(dayOfMonth(day + 4, 0));
    day5->callbackData = std::to_string(day + 4) + " " + std::to_string(doctorId);
    row.push_back(day5);

    day6->text = std::to_string(dayOfMonth(day + 5, 0));
    day6->callbackData = std::to_string(day + 5) + " " + std::to_string(doctorId);
    row.push_back(day6);

    day7->text = std::to_string(dayOfMonth(day + 6, 0));
    day7->callbackData = std::to_string(day + 6) + " " + std::to_string(doctorId);
    row.push_back(day7);

    keyboard->inlineKeyboard.push_back(row);

    /******************************************************************/
    InlineKeyboardButton::Ptr left(new InlineKeyboardButton);
    left->text = KEYBOARD_LEFT;
    left->callbackData = KEYBOARD_LEFT;
    row1.push_back(left);

    InlineKeyboardButton::Ptr right(new InlineKeyboardButton);
    right->text = KEYBOARD_RIGHT;
    right->callbackData = KEYBOARD_RIGHT;
    row1.push_back(right);

    keyboard->inlineKeyboard.push_back(row1);

    return keyboard;
}

/***********************************************************************************************/
InlineKeyboardMarkup::Ptr createChoiceTimeInlineKeyboard(const std::vector<std::string>& timesStr)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row;

    for (int i = 0; i < timesStr.size(); i += 2)
    {
        InlineKeyboardButton::Ptr tmpTime(new InlineKeyboardButton);
        tmpTime->callbackData = timesStr[i + 1];
        tmpTime->text = timesStr[i];
        row.push_back(tmpTime);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();
    }

    return keyboard;
}

/***********************************************************************************************/
InlineKeyboardMarkup::Ptr createSessionShowInlineKeyboard(int id)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row;

    InlineKeyboardButton::Ptr btn(new InlineKeyboardButton);
    btn->callbackData = { KEYBOARD_SESSION_CANCEL_CB + std::to_string(id) };
    btn->text = KEYBOARD_SESSION_CANCEL;
    row.push_back(btn);

    keyboard->inlineKeyboard.push_back(row);

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
