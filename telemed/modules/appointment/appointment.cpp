﻿#include "appointment.h"

#include "../doctors/doctors.h"
#include "../patients/patients.h"
#include "../keyBoard/keyBoard.h"
#include "../users/user.h"
#include "../config.h"

#define SPECS_MAX_CNT 10

static cJSON* aps = NULL;

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

/****************************************************************************************************/
void appointmentInit()
{
	aps = loadDoctor("appointments.json");
	if (aps == NULL)
	{
		aps = cJSON_CreateArray();

		// Сохранение в файл
		if (!saveDoctor("appointments.json", aps))
		{
			fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
		}

		AP_DATE date = { 20, 2, 2025 };
		AP_TIME time = { 18, 30 };
		Appointment* ap = createAp(1, 0, 0, &date, &time);
		addAppointment(ap);
		freeAp(ap);

		date.day = 21;
		time.hour = 19;
		time.min = 0;
		ap = createAp(2, 0, 0, &date, &time);
		addAppointment(ap);
		freeAp(ap);

		date.day = 21;
		time.hour = 19;
		time.min = 30;
		ap = createAp(3, 0, 0, &date, &time);
		addAppointment(ap);
		freeAp(ap);

		aps = loadDoctor("appointments.json");
	}

	// Освобождение памяти
	cJSON_Delete(aps);

#if 1
	

#endif
}

/****************************************************************************************************/
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
		bot.getApi().sendMessage(curChatId, strSpec, NULL, NULL, createSpecKeyboard(doctor->id));
		setUserProcess(curChatId, USER_PROCESS_CHOISE_SPEC);
	}
	
}

/****************************************************************************************************/
void appointmentReg(Bot& bot, long curChatId, int id)
{
	Appointment* ap = findAppointmentId(id);

	PatientData* patient = findPatientChatId(curChatId);

	Doctor* doctor = findDoctorId(ap->doctorId);

	if (ap == NULL || patient == NULL || doctor == NULL)
	{
		bot.getApi().sendMessage(curChatId, u8"К сожалению произошла ошибка, попробуйте позже", NULL, NULL, createStartKeyboard());
		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
		return;
	}

	ap->patientId = patient->id;

	appointmentEdit(ap->id, ap);

	std::string str{
			u8"Вы записаны " + std::to_string(ap->date.day) + "." + std::to_string(ap->date.month) + "." + std::to_string(ap->date.year) +
			u8" в " + std::to_string(ap->time.hour) + ":" + std::to_string(ap->time.min) +
			u8"\n к " + doctor->firstName + " " + doctor->lastName + " " + doctor->middleName +
			u8"\n Специализация " + SPECIALTY_NAMES[doctor->specialty]
	};
	bot.getApi().sendMessage(curChatId, str, NULL, NULL, createStartKeyboard());
	setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
}

/****************************************************************************************************/
void appointmentDelete(Bot& bot, long curChatId, int id)
{
	Appointment* ap = findAppointmentId(id);

	if (ap == NULL)
	{
		bot.getApi().sendMessage(curChatId, u8"К сожалению произошла ошибка, попробуйте позже", NULL, NULL, createStartKeyboard());
		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
		return;
	}

	ap->patientId = 0;

	appointmentEdit(ap->id, ap);

	bot.getApi().sendMessage(curChatId, u8"Запись отменена.", NULL, NULL, createStartKeyboard());
	setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
}

#define MAX_CNT 10

/****************************************************************************************************/
void appointmentShow(Bot& bot, long curChatId)
{
	PatientData* patient = findPatientChatId(curChatId);

	if (patient == NULL)
	{
		return;
	}

	int appointments[MAX_CNT];
	int appointmentsCnt = MAX_CNT;

	findAppointmentPatientId(appointments, &appointmentsCnt, patient->id);

	if (!appointmentsCnt)
	{
		bot.getApi().sendMessage(curChatId, u8"У вас пока нет записей.\nСамое время записаться!", NULL, NULL, createStartKeyboard());
		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
		return;
	}

	bot.getApi().sendMessage(curChatId, u8"Вы записаны:");

	for (UINT32 i = 0; i < appointmentsCnt; i++)
	{
		Appointment* ap = findAppointmentId(appointments[i]);

		if (ap != NULL)
		{
			Doctor* doctor = findDoctorId(ap->doctorId);

			std::string tmp = 
			{ 
				std::to_string(ap->date.day) + "." + std::to_string(ap->date.month) + "." + std::to_string(ap->date.year) +
				u8" в " + std::to_string(ap->time.hour) + ":" + std::to_string(ap->time.min) +
				u8"\n к " + doctor->firstName + " " + doctor->lastName + " " + doctor->middleName +
				u8"\n Специализация " + SPECIALTY_NAMES[doctor->specialty]
			};
			bot.getApi().sendMessage(curChatId, tmp, NULL, NULL, createSessionShowInlineKeyboard(ap->id));
		}
	}
	bot.getApi().sendMessage(curChatId, u8"Это все ваши записи.", NULL, NULL, createSessionsKeyboard());
	setUserProcess(curChatId, USER_PROCESS_SESSION);
}

/****************************************************************************************************/
void appointmentChoiceDateDoctor(Bot& bot, long curChatId, int doctorId)
{
	if (doctorId)
	{
		Doctor *doctor = findDoctorId(doctorId);
		
		std::time_t now = std::time(nullptr);
		std::tm* ltm = std::localtime(&now);

		int day = ltm->tm_mday;
		int month = ltm->tm_mon;
		int year = ltm->tm_year;

		int appointments[MAX_CNT];
		int appointmentsCnt = MAX_CNT;
		findAppointmentDoctorIdAndDate(appointments, &appointmentsCnt, doctor->id, day);

		if (!appointmentsCnt)
		{
			bot.getApi().sendMessage(curChatId, u8"К сожалению записи к этому специалисту сейчас нет", NULL, NULL, createStartKeyboard());
			setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
			return;
		}

		std::vector<std::string> times;

		for (UINT32 i = 0; i < appointmentsCnt; i++)
		{
			Appointment* ap = findAppointmentId(appointments[i]);

			if (ap != NULL)
			{
				std::string tmp = { std::to_string(ap->time.hour) + ":" + std::to_string(ap->time.min)};
				times.push_back(tmp);
				times.push_back(std::to_string(ap->id));
			}
		}

		bot.getApi().sendMessage(curChatId, u8"Выберите подходящее время приема: ", NULL, NULL, createChoiceTimeInlineKeyboard(times));
		setUserProcess(curChatId, USER_PROCESS_CHOISE_TIME);
	}
}

/****************************************************************************************************/
void appointmentChoiceTimeDoctor(Bot& bot, long curChatId, int doctorId, int date)
{
	//if (doctorId && date)
	//{
	//	Doctor* doctor = findDoctorId(doctorId);

	//	int appointments[MAX_CNT];
	//	int appointmentsCnt = MAX_CNT;
	//	findAppointmentDoctorId(appointments, &appointmentsCnt, doctor->id);

	//	if (!appointmentsCnt)
	//	{
	//		bot.getApi().sendMessage(curChatId, u8"К сожалению свободных окошек на эту дату нет", NULL, NULL, createStartKeyboard());
	//		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
	//		return;
	//	}

	//	//AP_TIME times[MAX_CNT];
	//	std::vector<std::string> times;

	//	for (UINT32 i = 0; i < appointmentsCnt; i++)
	//	{
	//		Appointment* ap = findAppointmentId(appointments[i]);

	//		if (ap != NULL)
	//		{
	//			std::string tmp = { std::to_string(ap->time.hour) + ":" + std::to_string(ap->time.min) };
	//			times.push_back(tmp);
	//		}
	//	}

	//	bot.getApi().sendMessage(curChatId, u8"Выберите подходящее время приема: ", NULL, NULL, createChoiceTimeInlineKeyboard(times));
	//	setUserProcess(curChatId, USER_PROCESS_CHOISE_TIME);
	//}
}

/****************************************************************************************************/
void appointmentEdit(int id, Appointment* ap)
{
	aps = loadAp("appointments.json");

	int len = cJSON_GetArraySize(aps);
	if (id < 0 || id >= len)
	{
		return;
	}
	cJSON* newItem = apToJson(ap);

	if (newItem != NULL)
	{
		cJSON_ReplaceItemInArray(aps, id, newItem);

		// Сохранение в файл
		if (!saveAp("appointments.json", aps))
		{
			fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
		}
	}

	// Освобождение памяти
	cJSON_Delete(aps);

	return;
}

/****************************************************************************************************/
void appointmentChooseTime(long doctorId)
{
	
}

/****************************************************************************************************/
Appointment* findAppointmentId(int id)
{
	Appointment* ap = (Appointment*)malloc(sizeof(Appointment));

	aps = loadAp("appointments.json");

	if (aps == NULL || cJSON_GetArraySize(aps) == 0)
	{
		return NULL;
	}

	for (int i = 0; i < cJSON_GetArraySize(aps); i++)
	{
		cJSON* apJson = cJSON_GetArrayItem(aps, i);
		if (apJson != NULL)
		{
			cJSON* jsonDoctorId = cJSON_GetObjectItem(apJson, "id");
			if (jsonDoctorId != NULL && jsonDoctorId->valuedouble == id)
			{
				ap = jsonToAp(apJson);
			}
		}
	}

	// Освобождение памяти
	cJSON_Delete(aps);

	return ap;
}

/****************************************************************************************************/
void findAppointmentPatientId(int* dst, int* size, int patientId)
{
	int slider = 0;

	if (NULL == dst || NULL == size || !size[0])
	{
		return;
	}
	memset(dst, -1, size[0] * sizeof(int));

	aps = loadAp("appointments.json");

	if (aps == NULL || cJSON_GetArraySize(aps) == 0)
	{
		return;
	}

	for (int i = 0; i < cJSON_GetArraySize(aps) && slider < size[0]; i++)
	{
		cJSON* apJson = cJSON_GetArrayItem(aps, i);
		if (apJson != NULL)
		{
			cJSON* apPatientId = cJSON_GetObjectItem(apJson, "patientId");
			if (apPatientId != NULL && (int)apPatientId->valueint == patientId)
			{
				cJSON* apId = cJSON_GetObjectItem(apJson, "id");
				dst[slider++] = apId->valueint;
			}
		}
	}

	*size = slider;

	return;
}

/****************************************************************************************************/
void findAppointmentDoctorId(int *dst, int* size, int doctorId)
{
	int slider = 0;

	if (NULL == dst || NULL == size || !size[0])
	{
		return;
	}
	memset(dst, -1, size[0] * sizeof(int));

	aps = loadAp("appointments.json");

	if (aps == NULL || cJSON_GetArraySize(aps) == 0)
	{
		return;
	}

	for (int i = 0; i < cJSON_GetArraySize(aps) && slider < size[0]; i++)
	{
		cJSON* apJson = cJSON_GetArrayItem(aps, i);
		if (apJson != NULL)
		{
			cJSON* apDoctorId = cJSON_GetObjectItem(apJson, "doctorId");
			if (apDoctorId != NULL && (int)apDoctorId->valuedouble == doctorId)
			{
				cJSON* apId = cJSON_GetObjectItem(apJson, "id");
				dst[slider++] = apId->valuedouble;
			}
		}
	}

	*size = slider;

	return;
}

/****************************************************************************************************/
void findAppointmentDoctorIdAndDate(int* dst, int* size, int doctorId, int date)
{
	int slider = 0;

	if (NULL == dst || NULL == size || !size[0])
	{
		return;
	}
	memset(dst, -1, size[0] * sizeof(int));

	aps = loadDoctor("appointments.json");

	if (aps == NULL || cJSON_GetArraySize(aps) == 0)
	{
		return;
	}

	for (int i = 0; i < cJSON_GetArraySize(aps) && slider < size[0]; i++)
	{
		cJSON* apJson = cJSON_GetArrayItem(aps, i);
		if (apJson != NULL)
		{
			cJSON* apDoctorId = cJSON_GetObjectItem(apJson, "doctorId");
			if (apDoctorId != NULL && (int)apDoctorId->valuedouble == doctorId)
			{
				cJSON* apDate = cJSON_GetObjectItem(apJson, "date");
				cJSON* apPatientId = cJSON_GetObjectItem(apJson, "patientId");
				char strDate[12] = { 0 };
				sprintf(strDate, "%d.3.2025", date);
				/* Проверка что даты совпадают, и никто еще не записан */
				if (!strcmp(apDate->valuestring, strDate) && !apPatientId->valueint)
				{
					cJSON* apId = cJSON_GetObjectItem(apJson, "id");
					dst[slider++] = apId->valuedouble;
				}
			}
		}
	}

	*size = slider;

	return;
}

//std::string strSpec{
//			u8"Специализация: " + info.specialty + "\n" +
//			info.lastName + " " + info.firstName + " " + info.middleName +
//			u8"\nСтаж " + info.experience + u8" лет\n"
//			u8"⭐️" + info.rating
//};

/****************************************************************************************************/
STATUS addAppointment(Appointment* ap)
{
	aps = loadDoctor("appointments.json");

	if (ap != NULL)
	{
		// Преобразование в JSON и добавление в массив
		cJSON* apJson = apToJson(ap);
		if (apJson != NULL)
		{
			cJSON_AddItemToArray(aps, apJson);
			/*freedoctorData(doctor);*/
		}
	}

	// Сохранение в файл
	if (!saveDoctor("appointments.json", aps))
	{
		fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
	}

	// Освобождение памяти
	cJSON_Delete(aps);

	return KN_OK;
}
