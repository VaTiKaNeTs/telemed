
#include "botCmd.h"

#include "../../config.h"
#include "../keyBoard/keyBoard.h"
#include "../keyBoard/keyBoardCfg.h"
#include "../account/account.h"
#include "../users/user.h"
#include "../patients/patients.h"
#include "../doctors/doctors.h"
#include "../appointment/appointment.h"

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

static char str[1024];

/****************************************************************************************************/
void botCmdInit(Bot& bot)
{
    // Команды ***********************************************************
    vector<BotCommand::Ptr> commands;
    BotCommand::Ptr cmdArray(new BotCommand);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = CMD_START;
    cmdArray->description = u8"Старт";
    commands.push_back(cmdArray);

    bot.getApi().setMyCommands(commands);

    vector<BotCommand::Ptr> vectCmd;
    vectCmd = bot.getApi().getMyCommands();

    for (std::vector<BotCommand::Ptr>::iterator it = vectCmd.begin(); it != vectCmd.end(); ++it) 
    {
        printf("cmd: %s -> %s\r\n", (*it)->command.c_str(), (*it)->command.c_str());
    }
}

/****************************************************************************************************/
void botCmdStart(Bot& bot)
{
    bot.getEvents().onCommand(CMD_START, [&bot](Message::Ptr message)
    {
        
        long curChatId = 0;
        printf("User wrote %s\n", message->text.c_str());
        curChatId = message->chat->id;
        saveChatId(curChatId);

        PatientData *patient;
        if (patient = findPatientChatId(curChatId))
        { /* Пациент зарегистрирован */
            snprintf(str, sizeof(str), u8"👨‍⚕️Здравствуйте, %s, я \"ТелеМедБот\". Чем могу помочь?", patient->firstName);
            std::string readyStr(str);
            bot.getApi().sendMessage(curChatId, readyStr, NULL, NULL, createStartKeyboard());
            setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
        }
        else
        { /* Пациент не зарегистрирован */
            snprintf(str, sizeof(str), u8"👨‍⚕️Здравствуйте, я \"ТелеМедБот\". Давайте зарегистрируемся!");
            std::string readyStr(str);
            bot.getApi().sendMessage(curChatId, readyStr, NULL, NULL, createRegInlineKeyboard());
            setUserProcess(curChatId, USER_PROCESS_ACCOUNT_EDIT);
        }
    });
}

/****************************************************************************************************/
void BotCmdAny(Bot& bot)
{
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message)
        {
            long curChatId = 0;
            /* Проверка что пользователь зарегистрирован */
            if (findUser(message->chat->id) != -1)
            {
                curChatId = message->chat->id;
            }
            else
            {
                return;
            }

            printf("User wrote %s\n", message->text.c_str());
            if (StringTools::startsWith(message->text, "/start"))
            {
                return;
            }

            switch (getUserProcess(curChatId))
            {
            case USER_PROCESS_MAIN_MENU:
            {
                /* Проверяем, что пришла команда Личный кабинет */
                if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT))
                {
                    account(bot, curChatId);
                    setUserProcess(curChatId, USER_PROCESS_ACCOUNT);
                }
                else if (StringTools::startsWith(message->text, KEYBOARD_MAKE_AN_APPOINTMENT))
                {
                    bot.getApi().sendMessage(curChatId, u8"Выберите специалиста", NULL, NULL, createChooseSpecInlineKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_CHOOSE_SPECIALIT);
                }
                break;
            }
            case USER_PROCESS_ACCOUNT:
            {
                /* Проверяем, что пришла команда выйти из личного кабинета */
                if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT_BACK))
                {
                    bot.getApi().sendMessage(curChatId, u8"Назад", NULL, NULL, createStartKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
                }
                else if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT_EDIT))
                {
                    bot.getApi().sendMessage(curChatId, u8"Какую информацию, вы хотите изменить?", NULL, NULL, createAccEditInlineKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_ACCOUNT_EDIT);
                }
                break;
            }
            case USER_PROCESS_GET_FIRSTNAME_REG:
            {
                PatientData* patient = createPatientData(getPatientsCnt(), curChatId, message->text.c_str(), "NULL", "NULL", 0, "NULL");
                addPatient(patient);
                snprintf(str, sizeof(str), u8"%s, спасибо за регистрацию!", patient->firstName);
                std::string readyStr(str);
                bot.getApi().sendMessage(curChatId, readyStr);
                bot.getApi().sendMessage(curChatId, u8"Полную информацию о себе вы можете заполнить в личном кабинете.", NULL, NULL, createStartKeyboard());
                setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
                break;
            }
            case USER_PROCESS_GET_FIRSTNAME:
            {
                PatientData* patient = findPatientChatId(curChatId);
                patient->firstName = _strdup(message->text.c_str());
                patientEdit(patient->id, patient);
                account(bot, curChatId);
                bot.getApi().sendMessage(curChatId, u8"Какую информацию, вы хотите изменить?", NULL, NULL, createAccEditInlineKeyboard());
                setUserProcess(curChatId, USER_PROCESS_ACCOUNT_EDIT);
                break;
            }
            case USER_PROCESS_GET_LASTNAME:
            {
                PatientData* patient = findPatientChatId(curChatId);
                patient->lastName = _strdup(message->text.c_str());
                patientEdit(patient->id, patient);
                account(bot, curChatId);
                bot.getApi().sendMessage(curChatId, u8"Какую информацию, вы хотите изменить?", NULL, NULL, createAccEditInlineKeyboard());
                setUserProcess(curChatId, USER_PROCESS_ACCOUNT_EDIT);
                break;
            }
            case USER_PROCESS_GET_MIDDLENAME:
            {
                PatientData* patient = findPatientChatId(curChatId);
                patient->middleName = _strdup(message->text.c_str());
                patientEdit(patient->id, patient);
                account(bot, curChatId);
                bot.getApi().sendMessage(curChatId, u8"Какую информацию, вы хотите изменить?", NULL, NULL, createAccEditInlineKeyboard());
                setUserProcess(curChatId, USER_PROCESS_ACCOUNT_EDIT);
                break;
            }
            case USER_PROCESS_GET_AGE:
            {
                PatientData* patient = findPatientChatId(curChatId);
                patient->age = stoi(message->text);
                patientEdit(patient->id, patient);
                account(bot, curChatId);
                bot.getApi().sendMessage(curChatId, u8"Какую информацию, вы хотите изменить?", NULL, NULL, createAccEditInlineKeyboard());
                setUserProcess(curChatId, USER_PROCESS_ACCOUNT_EDIT);
                break;
            }
            case USER_PROCESS_GET_SEX:
            {
                PatientData* patient = findPatientChatId(curChatId);
                if (u8"М" == message->text)
                {
                    patient->gender = _strdup(u8"Мужской");
                }
                else if (u8"Ж" == message->text)
                {
                    patient->gender = _strdup(u8"Женский");
                }
                else
                {
                    bot.getApi().sendMessage(curChatId, u8"Введите М или Ж");
                    break;
                }
                patientEdit(patient->id, patient);
                account(bot, curChatId);
                bot.getApi().sendMessage(curChatId, u8"Какую информацию, вы хотите изменить?", NULL, NULL, createAccEditInlineKeyboard());
                setUserProcess(curChatId, USER_PROCESS_ACCOUNT_EDIT);
                break;
            }
            case USER_PROCESS_ACCOUNT_EDIT:
            {
                if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT_BACK))
                {
                    account(bot, curChatId);
                    setUserProcess(curChatId, USER_PROCESS_ACCOUNT);
                }
                break;
            }
            }
        });
}

/****************************************************************************************************/
void botCmdCallback(Bot& bot)
{
    InlineKeyboardMarkup::Ptr keyboard = createRegInlineKeyboard();

    bot.getEvents().onCallbackQuery([&bot, &keyboard](CallbackQuery::Ptr query) 
        {
            long curChatId = query->message->chat->id;
            if (KN_ERROR != findUser(curChatId))
            {

                /* Приглашение ввести имя */
                if (StringTools::startsWith(query->data, INLINE_KEYBOARD_REGISTRATION)) {
                    bot.getApi().sendMessage(curChatId, u8"Введите ваше имя:", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_GET_FIRSTNAME_REG);
                }

                /* Выбор специалиста для записи */
                else if (USER_PROCESS_CHOISE_SPEC == getUserProcess(curChatId))
                {
                    
                }

                /* Изменение личных данных */
                else if (StringTools::startsWith(query->data, INLINE_KEYBOARD_ACCOUNT_EDIT_FIRSTNAME)) {
                    bot.getApi().sendMessage(curChatId, u8"Введите ваше имя:", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_GET_FIRSTNAME);
                }
                else if (StringTools::startsWith(query->data, INLINE_KEYBOARD_ACCOUNT_EDIT_LASTNAME)) {
                    bot.getApi().sendMessage(curChatId, u8"Введите вашу фамилию:", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_GET_LASTNAME);
                }
                else if (StringTools::startsWith(query->data, INLINE_KEYBOARD_ACCOUNT_EDIT_MIDDLENAME)) {
                    bot.getApi().sendMessage(curChatId, u8"Введите ваше отчество:", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_GET_MIDDLENAME);
                }
                else if (StringTools::startsWith(query->data, INLINE_KEYBOARD_ACCOUNT_EDIT_AGE)) {
                    bot.getApi().sendMessage(curChatId, u8"Введите ваш возраст:", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_GET_AGE);
                }
                else if (StringTools::startsWith(query->data, INLINE_KEYBOARD_ACCOUNT_EDIT_GENDER)) {
                    bot.getApi().sendMessage(curChatId, u8"Введите ваш пол (М или Ж):", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_GET_SEX);
                }

                /* Выбор специалиста */
                else if (StringTools::startsWith(query->data, INLINE_KEYBOARD_SPEC_THERAPIST)) {
                    //bot.getApi().sendMessage(query->message->chat->id, u8"Выберите врача:", NULL, NULL, deleteKeyboard());
                    appointment(bot, curChatId, THERAPIST);
                    //setUserProcess(query->message->chat->id, USER_PROCESS_GET_SEX);
                }
                else if (StringTools::startsWith(query->data, INLINE_KEYBOARD_SPEC_PEDIATRICIAN)) {
                    appointment(bot, curChatId, PEDIATRICIAN);
                    //setUserProcess(query->message->chat->id, USER_PROCESS_GET_SEX);
                }
                else if (StringTools::startsWith(query->data, INLINE_KEYBOARD_SPEC_SURGEON)) {
                    appointment(bot, curChatId, SURGEON);
                    //setUserProcess(query->message->chat->id, USER_PROCESS_GET_SEX);
                }

                /* Выбор времени специалиста */
            }
        });
}