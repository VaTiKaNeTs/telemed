
#include "botCmd.h"

#include "../../config.h"
#include "../../modules/keyBoard/keyBoard.h"

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
    /* Айди чата которое выполняется в даный момент */
    static long curChatId = 0;

    bot.getEvents().onCommand(CMD_START, [&bot](Message::Ptr message)
    {
        printf("User wrote %s\n", message->text.c_str());
        curChatId = message->chat->id;
        bot.getApi().sendMessage(curChatId, u8"👨‍⚕️Привет, я ''ТелеМедБот'.Чем могу помочь?", NULL, NULL, createStartKeyboard());
        //saveChatId(curChatId);
    });
}