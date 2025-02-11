
#include "botCmd.h"

#include "../../config.h"
#include "../keyBoard/keyBoard.h"
#include "../keyBoard/keyBoardCfg.h"
#include "../account/account.h"
#include "../users/user.h"

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

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

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = CMD_MAKE_AN_APPOINTMENT;
    cmdArray->description = u8"Запись";
    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = CMD_PERSONAL_ACCOUNT;
    cmdArray->description = u8"Личный кабиент";
    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = CMD_CURRENT_SESSIONS;
    cmdArray->description = u8"Текущие записи";
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
        bot.getApi().sendMessage(curChatId, u8"👨‍⚕️Привет, я ''ТелеМедБот'.Чем могу помочь?", NULL, NULL, createStartKeyboard());
        saveChatId(curChatId);
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

            /* Проверяем, что пришла команда Личный кабинет */
            if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT))
            {
                account(bot, curChatId);
            }
            /* Проверяем, что пришла команда Личный кабинет */
            else if (StringTools::startsWith(message->text, KEYBOARD_ACCOUNT_BACK))
            {
                bot.getApi().sendMessage(curChatId, u8"Назад", NULL, NULL, createStartKeyboard());
                //bot.getApi().editMessageReplyMarkup(curChatId, NULL, NULL, createStartKeyboard());
            }
        });
}