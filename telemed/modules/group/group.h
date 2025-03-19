#ifndef __GROUP_H_
#define __GROUP_H_

#include "../../knTypes.h"

#include <tgbot/tgbot.h>

#include "groupDataBase.h"

using namespace TgBot;

void group(Bot& bot);


void groupUpdate(void);

void groupInit(void);

void groupEdit(int chatId, Group* group);

STATUS addGroup(Group* group);

STATUS removeGroup(std::int64_t chatId);

STATUS cleanAllGroups(void);

void findFreeGroup(Group *group);

void findGroupChatId(Group* group, std::int64_t chatId);

UINT32 groupGetCnt(void);

#endif __GROUP_H_