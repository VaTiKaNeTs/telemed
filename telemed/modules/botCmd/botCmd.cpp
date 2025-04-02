
#include "botCmd.h"

#include "../../config.h"
#include "../keyBoard/keyBoard.h"
#include "../keyBoard/keyBoardCfg.h"
#include "../account/account.h"
#include "../users/user.h"
#include "../patients/patients.h"
#include "../doctors/doctors.h"
#include "../appointment/appointment.h"
#include "../group/group.h"
#include "../general/general.h"

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

static char str[1024];

static bool rootMode = TRUE; /* позже исправить на FALSE */

#define pageChSpMin 0
#define pageChSpMax 1
static int pageChooseSpecialist = pageChSpMin; /* Страница выбора специалиста */

/****************************************************************************************************/
bool startsWith(const std::string& str, const std::string& prefix) 
{
    return str.compare(0, prefix.size(), prefix) == 0;
}

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
        
        int64_t curChatId = 0;
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
            snprintf(str, sizeof(str), u8"👨‍⚕️Здравствуйте, я \"ТелеМедБот\". Мы не знакомы, давайте зарегистрируемся!");
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
            int64_t curChatId = 0;
            /* Проверка что пользователь зарегистрирован */
            if (findUser(message->chat->id) != -1)
            {
                curChatId = message->chat->id;
            }
            else
            {
                if (rootMode)
                {
                    // Добавление бота в группу
                    if (!message->newChatMembers.empty()) 
                    {
                        // Получаем данные о боте
                        auto botUser = bot.getApi().getMe();
                        // Проходим по всем новым участникам
                        for (auto newMember : message->newChatMembers) 
                        {
                            // Если бот был добавлен в чат
                            if (newMember->id == botUser->id) 
                            {
                                // Функция для сохранения идентификатора группы
                                Group group = { message->chat->id, 0, 0, 0, 0 };
                                addGroup(&group);
                                // Можно отправить уведомление о сохранении группы
                                bot.getApi().sendMessage(message->chat->id, u8"Группа успешно сохранена!");
                                break;
                            }
                        }
                    }
                    else if (message->leftChatMember) 
                    {
                        // Получаем данные о самом боте
                        auto me = bot.getApi().getMe();
                        // Если покинул чат именно бот
                        if (message->leftChatMember->id == me->id) 
                        {
                            // Здесь удаляем идентификатор группы из вашей базы данных
                            Group group = { 0 };
                            findGroupChatId(&group, message->chat->id);
                            if (KN_ERROR == removeGroup(group.chatId))
                            {
                                printf("error of remove group\n");
                            }
                            // Логируем событие или выполняем другие необходимые действия
                            std::cout << "Бот был удален из группы с chatId: " << message->chat->id << std::endl;

                            // Прерываем дальнейшую обработку этого сообщения
                            return;
                        }
                    }
                }
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
                    pageChooseSpecialist = 0;
                    bot.getApi().sendMessage(curChatId, u8"Выберите специалиста", NULL, NULL, createChooseSpecInlineKeyboard(pageChooseSpecialist));
                    bot.getApi().sendMessage(curChatId, u8"Используйте кнопки ↩️ ⬅️ ➡️ для навигации", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_CHOOSE_SPECIALIT_0);
                }
                else if (StringTools::startsWith(message->text, KEYBOARD_SESSIONS))
                {
                    appointmentShow(bot, curChatId);
                }
                else if (StringTools::startsWith(message->text, KEYBOARD_ROOT_ACCESS))
                {
                    rootMode = !rootMode;
                    bot.getApi().sendMessage(curChatId, u8"Вход в режим админа");
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
            case USER_PROCESS_SESSION:
            {
                if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT_BACK))
                {
                    bot.getApi().sendMessage(curChatId, u8"Главное меню", NULL, NULL, createStartKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
                }
                break;
            }
            case USER_PROCESS_CHOISE_SPEC:
            {
                if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT_BACK))
                {
                    bot.getApi().sendMessage(curChatId, u8"Выберите специалиста", NULL, NULL, createChooseSpecInlineKeyboard(pageChooseSpecialist));
                    bot.getApi().sendMessage(curChatId, u8"Используйте кнопки ↩️ ⬅️ ➡️ для навигации", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, (USER_PROCESS)(USER_PROCESS_CHOOSE_SPECIALIT_0 + pageChooseSpecialist));
                }
                break;
            }
            case USER_PROCESS_CHOISE_DATE:
            {
                if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT_BACK))
                {
                    appointment(bot, curChatId, getUserSpec(curChatId));
                }
                break;
            }
            case USER_PROCESS_CHOISE_TIME:
            {
                if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT_BACK))
                {
                    appointmentChoiceDateDoctor(bot, curChatId, getUserDoctorId(curChatId));
                    //bot.getApi().sendMessage(curChatId, u8"Выберите специалиста", NULL, NULL, createChooseSpecInlineKeyboard(pageChooseSpecialist));
                    //bot.getApi().sendMessage(curChatId, u8"Используйте кнопки ↩️ ⬅️ ➡️ для навигации", NULL, NULL, deleteKeyboard());
                    //setUserProcess(curChatId, (USER_PROCESS)(USER_PROCESS_CHOOSE_SPECIALIT_0 + pageChooseSpecialist));
                }
                break;
            }
            default:
            {
                
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
            std::int64_t curChatId = query->message->chat->id;
            if (KN_ERROR != findUser(curChatId))
            {

                /* Приглашение ввести имя */
                if (StringTools::startsWith(query->data, INLINE_KEYBOARD_REGISTRATION)) {
                    bot.getApi().sendMessage(curChatId, u8"Введите ваше имя:", NULL, NULL, deleteKeyboard());
                    setUserProcess(curChatId, USER_PROCESS_GET_FIRSTNAME_REG);
                }

                /* Выбор даты для записи */
                else if (USER_PROCESS_CHOISE_DATE == getUserProcess(curChatId))
                {
                    if (StringTools::startsWith(query->data, KEYBOARD_LEFT))
                    {
                        if (getUserDay(curChatId) - 7 < getCurrentDayOfYear())
                        {
                            setUserDay(curChatId, getCurrentDayOfYear());
                        }
                        else
                        {
                            setUserDay(curChatId, getUserDay(curChatId) - 7);
                        }
                        appointmentChoiceDateDoctor(bot, curChatId, getUserDoctorId(curChatId));
                    }
                    else if (StringTools::startsWith(query->data, KEYBOARD_RIGHT))
                    {
                        setUserDay(curChatId, getUserDay(curChatId) + 7);
                        appointmentChoiceDateDoctor(bot, curChatId, getUserDoctorId(curChatId));
                    }
                    else
                    {
                        appointmentChoiceTimeDoctor(bot, curChatId, query->data.c_str());
                    }
                }

                else if (USER_PROCESS_CHOISE_SPEC == getUserProcess(curChatId))
                {

                    appointmentChoiceDateDoctor(bot, curChatId, std::stoi(query->data));
                }

                /* Выбор специалиста для записи */
                else if (USER_PROCESS_CHOOSE_SPECIALIT_0 == getUserProcess(curChatId) ||
                         USER_PROCESS_CHOOSE_SPECIALIT_1 == getUserProcess(curChatId))
                {
                    if (StringTools::startsWith(query->data, KEYBOARD_ACCOUNT_BACK))
                    {
                        bot.getApi().sendMessage(curChatId, u8"Главное меню", NULL, NULL, createStartKeyboard());
                        setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
                    }
                    else if (StringTools::startsWith(query->data, KEYBOARD_LEFT))
                    {
                        if (USER_PROCESS_CHOOSE_SPECIALIT_0 == getUserProcess(curChatId))
                        {
                            setUserProcess(curChatId, USER_PROCESS_CHOOSE_SPECIALIT_1);
                            pageChooseSpecialist = 1;
                        }
                        else
                        {
                            setUserProcess(curChatId, USER_PROCESS_CHOOSE_SPECIALIT_0);
                            pageChooseSpecialist = 0;
                        }
                        bot.getApi().sendMessage(curChatId, u8"Выберите специалиста", NULL, NULL, createChooseSpecInlineKeyboard(pageChooseSpecialist));
                    }
                    else if (StringTools::startsWith(query->data, KEYBOARD_RIGHT))
                    {
                        if (USER_PROCESS_CHOOSE_SPECIALIT_0 == getUserProcess(curChatId))
                        {
                            setUserProcess(curChatId, USER_PROCESS_CHOOSE_SPECIALIT_1);
                            pageChooseSpecialist = 1;
                        }
                        else
                        {
                            setUserProcess(curChatId, USER_PROCESS_CHOOSE_SPECIALIT_0);
                            pageChooseSpecialist = 0;
                        }
                        bot.getApi().sendMessage(curChatId, u8"Выберите специалиста", NULL, NULL, createChooseSpecInlineKeyboard(pageChooseSpecialist));
                    }
                    else
                    {
                        /* Выбор специалиста */
                        for (UINT32 i = DEFAULT_SPEC + 1; i < OTHER; i++)
                        {
                            if (StringTools::startsWith(query->data, SPECIALTY_NAMES[i]))
                            {
                                appointment(bot, curChatId, (SPECIALITY)i);
                            }
                        }
                    }
                }

                /* Выбор времени на запись */
                else if (USER_PROCESS_CHOISE_TIME == getUserProcess(curChatId))
                {
                    appointmentReg(bot, curChatId, std::stoi(query->data));
                }

                /* Отмена записи */
                else if (USER_PROCESS_SESSION == getUserProcess(curChatId))
                {
                    std::string prefix = KEYBOARD_SESSION_CANCEL_CB;
                    appointmentDelete(bot, curChatId, std::stoi(query->data.substr(prefix.size())));
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
                else if (StringTools::startsWith(query->data, KEYBOARD_SESSION_CANCEL_CB))
                {
                    /* Если вызывается команда на отмену записи из другого меню. */
                    std::string prefix = KEYBOARD_SESSION_CANCEL_CB;
                    appointmentDelete(bot, curChatId, std::stoi(query->data.substr(prefix.size())));
                }
                
                else
                {
                    
                }

                /* Выбор времени специалиста */
            }
        });
}

/****************************************************************************************************/
void BotGroup(Bot& bot)
{
    //bot.getEvents().chatUpdate
}