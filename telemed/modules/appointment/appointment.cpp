#include "appointment.h"

#include "../doctors/doctors.h"
#include "../keyBoard/keyBoard.h"
#include "../users/user.h"

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
void appointmentChoiceDateDoctor(Bot& bot, long curChatId, int doctorId)
{
	if (doctorId)
	{
		Doctor *doctor = findDoctorId(doctorId);
		
		int appointments[10];
		int appointmentsCnt = 10;
		findAppointmentDoctorId(appointments, &appointmentsCnt, doctor->id);

		if (!appointmentsCnt)
		{
			bot.getApi().sendMessage(curChatId, u8"К сожалению записи к этому специалисту сейчас нет", NULL, NULL, createStartKeyboard());
			setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
			return;
		}
		
		bot.getApi().sendMessage(curChatId, "Доступные даты на запись: ", NULL, NULL, createChoiceDateInlineKeyboard(appointments, appointmentsCnt));

	}
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
void findAppointmentDoctorId(int *dst, int* size, int doctorId)
{
	int slider = 0;

	if (NULL == dst || NULL == size || !size[0])
	{
		return;
	}
	memset(dst, -1, size[0]);

	aps = loadDoctor("doctors.json");

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
				dst[slider++] = i;
			}
		}
	}

	*size = slider;

	return;
}

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
