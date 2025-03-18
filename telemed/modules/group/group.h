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

STATUS removeGroup(long id);

STATUS cleanAllGroups(void);

void findGroupId(Group* group, int id);

void findFreeGroup(Group *group);

void findGroupChatId(Group* group, long chatId);

UINT32 groupGetCnt(void);

#endif __GROUP_H_