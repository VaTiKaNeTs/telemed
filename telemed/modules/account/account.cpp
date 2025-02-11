#include "account.h"

#include "../../config.h"
#include "../keyBoard/keyBoard.h"

#define ACCOUNT_INFO_NAME_LEN 20
#define ACCOUNT_INFO_SURNAME_LEN 20
#define ACCOUNT_INFO_PATRONYMIC_LEN 20

/****************************************************************************************************/
typedef enum
{
	NONE = 0,
	MALE,
	FEMALE,

	SEX_CNT
} SEX;

/****************************************************************************************************/
typedef struct
{
	std::string name;

	std::string surname;

	std::string patronymic;

	UINT32 age;

	UINT32 sex;

} ACCOUNT_INFO;

/****************************************************************************************************/
ACCOUNT_INFO info[MAX_CNT_USERS_CHAT_ID];

/****************************************************************************************************/
void account(Bot& bot, INT32 curChatId)
{
	info->name = { u8"Кирилл" };
	info->surname = { u8"Таровик" };
	info->patronymic = { u8"Михайлович" };
	info->sex = MALE;
	info->age = 23;

	std::string strSex = { (info->sex == MALE) ? ( u8"Мужской" ) : (u8"Женский") };
	std::string strAge = { 0 };

	std::string str{u8"Ваши данные:"
					u8"\nИмя: " + info->name + 
					u8"\nФамилия " + info->surname + 
					u8"\nОтчество " + info->patronymic +
					u8"\n\nПол " + strSex +
					u8"\n\nВозраст " +  strAge};

	bot.getApi().sendMessage(curChatId, str, NULL, NULL, createAccountKeyboard());
}