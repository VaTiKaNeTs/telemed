#ifndef GROUP_DB_H_
#define GROUP_DB_H_

#include <stdio.h>
#include <string.h>
#include <cstdint>
#include "../libs/cJSON/cJSON.h"

/****************************************************************************************************/
typedef struct {
    std::int64_t chatId;                /**< јйди чата */

    long doctorId;

    std::int64_t doctorChatId;

    long patientId;

    std::int64_t patientChatId;

} Group;

/****************************************************************************************************/
void createGroup(Group* group, std::int64_t chatId, long doctorId, std::int64_t doctorChatId,
    long patientId, std::int64_t patientChatId);

/****************************************************************************************************/
cJSON* groupToJson(Group* group);

/****************************************************************************************************/
void jsonToGroup(cJSON* json, Group* group);

/****************************************************************************************************/
int saveGroup(const char* filename, cJSON* group);

/****************************************************************************************************/
cJSON* loadGroup(const char* filename);

#endif /* GROUP_DB_H_ */