#ifndef GROUP_DB_H_
#define GROUP_DB_H_

#include <stdio.h>
#include <string.h>
#include "../libs/cJSON/cJSON.h"

/****************************************************************************************************/
typedef struct {
    int id;                     /**< ”никальный идентификатор группы */

    long chatId;                /**< јйди чата */

    long doctorId;

    long doctorChatId;

    long patientId;

    long patientChatId;


} Group;

/****************************************************************************************************/
Group* createGroup(int id, long chatId, long doctorId, long doctorChatId, 
    long patientId, long patientChatId);

/****************************************************************************************************/
cJSON* groupToJson(Group* group);

/****************************************************************************************************/
Group* jsonToGroup(cJSON* json);

/****************************************************************************************************/
int saveGroup(const char* filename, cJSON* group);

/****************************************************************************************************/
cJSON* loadGroup(const char* filename);

#endif /* GROUP_DB_H_ */