#ifndef __BOTCMD_H_
#define __BOTCMD_H_

#include "../../knTypes.h"

#include <tgbot/tgbot.h>
using namespace std;
using namespace TgBot;

/***********************************************
 Инициализация начальных команд бота.
***********************************************/
void botCmdInit(Bot& bot);

void botCmdStart(Bot& bot);

void BotCmdAny(Bot& bot);

#endif __BOTCMD_H_