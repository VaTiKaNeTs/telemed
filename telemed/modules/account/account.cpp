#include "account.h"

#include "../../config.h"
#include "../keyBoard/keyBoard.h"
#include "../patients/patients.h"

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

	std::string sex;

} ACCOUNT_INFO;

/****************************************************************************************************/
ACCOUNT_INFO info[MAX_CNT_USERS_CHAT_ID];

/****************************************************************************************************/
void createAccount(Bot& bot, INT32 curChatId)
{
	PatientData* patient = createPatientData(
		0,
		curChatId,
		NULL,
		NULL,
		NULL,
		0,
		NULL);

	addPatient(patient);
	bot.getApi().sendMessage(curChatId, "Введите ваше имя:");
}

/****************************************************************************************************/
void account(Bot& bot, INT32 curChatId)
{
	PatientData* patient = findPatientChatId(curChatId);

#if 1
	info->name = { patient->firstName };
	info->surname = { patient->lastName };
	info->patronymic = { patient->middleName };
	info->sex = { patient->gender };
	info->age = patient->age;

	std::string strAge = { 0 };

	std::string str{u8"Ваши данные:"
					u8"\nИмя: " + info->name + 
					u8"\nФамилия " + info->surname + 
					u8"\nОтчество " + info->patronymic +
					u8"\n\nПол " + info->sex +
					u8"\n\nВозраст " + std::to_string(info->age)};
#endif


	bot.getApi().sendMessage(curChatId, str, NULL, NULL, createAccountKeyboard());
}