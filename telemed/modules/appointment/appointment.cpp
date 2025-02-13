#include "appointment.h"

#include "../doctors/doctors.h"
#include "../keyBoard/keyBoard.h"
#include "../users/user.h"

#define SPECS_MAX_CNT 10

/****************************************************************************************************/
typedef struct
{
	std::string specialty;

	std::string firstName;

	std::string lastName;

	std::string middleName;

	std::string experience;

	std::string rating;

} DOCTOR_INFO;

void appointment(Bot& bot, long curChatId, SPECIALITY spec)
{
	int specs[SPECS_MAX_CNT];
	int specsCnt = SPECS_MAX_CNT;
	findDoctorSpec(specs, &specsCnt, spec);

	if (!specsCnt)
	{
		bot.getApi().sendMessage(curChatId, u8"К сожалению таких специалистов сейчас нет", NULL, NULL, createStartKeyboard());
		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
		return;
	}

	std::string str1{ u8"У нас есть " + std::to_string(specsCnt) + u8" подходящих специалиста(ов). \nВыберите подходящего врача:" };
	bot.getApi().sendMessage(curChatId, str1, NULL, NULL, deleteKeyboard());

	while (--specsCnt >= 0)
	{		

		Doctor* doctor = findDoctorId(specs[specsCnt]);

		DOCTOR_INFO info;
		info.specialty = SPECIALTY_NAMES[spec];
		info.firstName = { doctor->firstName };
		info.lastName = { doctor->lastName };
		info.middleName = { doctor->middleName };
		info.experience = { std::to_string(doctor->experience) };
		info.rating = { std::to_string(doctor->rating / 10) + "." + std::to_string(doctor->rating % 10) };

#if 1
		std::string strSpec{
			u8"Специализация: " + info.specialty + "\n" +
			info.lastName + " " + info.firstName + " " + info.middleName +
			u8"\nСтаж " + info.experience + u8" лет\n"
			u8"⭐️" + info.rating
		};
#endif
		bot.getApi().sendMessage(curChatId, strSpec, NULL, NULL, createSpecKeyboard());
		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
	}
	
}
