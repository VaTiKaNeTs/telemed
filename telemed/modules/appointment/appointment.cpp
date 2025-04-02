#include "appointment.h"

#include "../doctors/doctors.h"
#include "../patients/patients.h"
#include "../keyBoard/keyBoard.h"
#include "../users/user.h"
#include "../general/general.h"
#include "../config.h"

#include <string.h>

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
static std::string formatTime(int totalMinutes)
{
	int hours = totalMinutes / 60;
	int minutes = totalMinutes % 60;

	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << hours << ":"
		<< std::setw(2) << std::setfill('0') << minutes;
	return ss.str();
}

/****************************************************************************************************/
std::string formatDate(int dayOfYear, int year, bool isLeapYear) 
{
	int month = monthOfYear(dayOfYear, isLeapYear);
	int day = dayOfMonth(dayOfYear, isLeapYear);
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << day << "."
		<< std::setw(2) << std::setfill('0') << month << "."
		<< year;
	return oss.str();
}

/****************************************************************************************************/
void appointmentUpdate(void)
{
	aps = loadDoctor("appointments.json");
}

/****************************************************************************************************/
void appointmentInit(void)
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

#define TODAY getCurrentDayOfYear()
		Appointment ap = { 0 };
		int id = 1;
#if 0
		createAp(&ap, 0, 1, 0, TODAY, 2025, minOfDay(18, 30));
		addAppointment(&ap);
		
		createAp(&ap, 1, 1, 0, TODAY, 2025, minOfDay(19, 0));
		addAppointment(&ap);

		createAp(&ap, 2, 1, 0, TODAY, 2025, minOfDay(19, 30));
		addAppointment(&ap);
#else 
		// Для каждого врача от 1 до 22
		for (int doctorId = 1; doctorId <= 22; doctorId++) 
		{
			// Вычисляем базовое время для данного врача:
			// Базовый час: от 8 до 15 часов
			int baseHour = 8 + (doctorId % 8);
			// Базовая минута: 0 для чётных doctorId, 30 для нечётных
			int baseMinute = (doctorId % 2 == 0) ? 0 : 30;

			// Создаем первую встречу для врача: базовое время
			createAp(&ap, id++, doctorId, 0, TODAY, 2025, minOfDay(baseHour, baseMinute));
			addAppointment(&ap);

			// Создаем вторую встречу: через 30 минут от базового времени
			int minute2 = baseMinute + 30;
			int hour2 = baseHour;
			if (minute2 >= 60) {
				minute2 -= 60;
				hour2++;
			}
			createAp(&ap, id++, doctorId, 0, TODAY, 2025, minOfDay(hour2, minute2));
			addAppointment(&ap);

			// Создаем третью встречу: через 60 минут от базового времени
			int minute3 = baseMinute + 60;
			int hour3 = baseHour;
			if (minute3 >= 60) {
				minute3 -= 60;
				hour3++;
			}
			createAp(&ap, id++, doctorId, 0, TODAY, 2025, minOfDay(hour3, minute3));
			addAppointment(&ap);
		}
#endif
		aps = loadDoctor("appointments.json");
	}
}

/****************************************************************************************************/
void appointment(Bot& bot, int64_t curChatId, SPECIALITY spec)
{
	int specs[SPECS_MAX_CNT];
	int specsCnt = SPECS_MAX_CNT;
	findDoctorSpec(specs, &specsCnt, spec);

	setUserDay(curChatId, getCurrentDayOfYear());

	if (!specsCnt)
	{
		bot.getApi().sendMessage(curChatId, u8"К сожалению таких специалистов сейчас нет", NULL, NULL, createStartKeyboard());
		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
		return;
	}

	std::string str1{ u8"У нас есть " + std::to_string(specsCnt) + u8" подходящих специалиста(ов). \nВыберите подходящего врача:" };
	bot.getApi().sendMessage(curChatId, str1, NULL, NULL, createSessionsKeyboard());
	setUserSpec(curChatId, spec);

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

		bot.getApi().sendPhoto(curChatId, doctor->photo_path, strSpec, NULL, createSpecKeyboard(doctor->id));
#endif
		//bot.getApi().sendMessage(curChatId, strSpec, NULL, NULL, createSpecKeyboard(doctor->id));
		setUserProcess(curChatId, USER_PROCESS_CHOISE_SPEC);
		setUserDoctorId(curChatId, doctor->id);
	}
	
}

/****************************************************************************************************/
void appointmentReg(Bot& bot, int64_t curChatId, int id)
{
	Appointment ap = { 0 };
	findAppointmentId(&ap, id);

	PatientData* patient = findPatientChatId(curChatId);

	Doctor* doctor = findDoctorId(ap.doctorId);

	if (&ap == NULL || patient == NULL || doctor == NULL)
	{
		bot.getApi().sendMessage(curChatId, u8"К сожалению произошла ошибка, попробуйте позже", NULL, NULL, createStartKeyboard());
		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
		return;
	}

	ap.patientId = patient->id;

	appointmentEdit(ap.id, &ap);

	std::string str{
			u8"Вы записаны " + formatDate(ap.dayOfYear, ap.year + 1900, 0) +
			u8" в " + formatTime(ap.minOfDay) +
			u8"\n к " + doctor->firstName + " " + doctor->lastName + " " + doctor->middleName +
			u8"\n Специализация " + SPECIALTY_NAMES[doctor->specialty]
	};
	bot.getApi().sendMessage(curChatId, str, NULL, NULL, createStartKeyboard());
	setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
}

/****************************************************************************************************/
void appointmentDelete(Bot& bot, int64_t curChatId, int id)
{
	Appointment ap = { 0 }; 
	findAppointmentId(&ap, id);

	if (&ap == NULL)
	{
		bot.getApi().sendMessage(curChatId, u8"К сожалению произошла ошибка, попробуйте позже", NULL, NULL, createStartKeyboard());
		setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
		return;
	}

	ap.patientId = 0;

	appointmentEdit(ap.id, &ap);

	bot.getApi().sendMessage(curChatId, u8"Запись отменена.", NULL, NULL, createStartKeyboard());
	setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
}

#define MAX_CNT 50

/****************************************************************************************************/
void appointmentShow(Bot& bot, int64_t curChatId)
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
		Appointment ap = { 0 }; 
		findAppointmentId(&ap, appointments[i]);

		if (&ap != NULL)
		{
			Doctor* doctor = findDoctorId(ap.doctorId);
			std::string tmp =
			formatDate(ap.dayOfYear, ap.year + 1900, 0) + u8" в " + formatTime(ap.minOfDay) + 
			u8"\n к " + doctor->firstName + " " + doctor->lastName + " " + doctor->middleName +
			u8"\n Специализация: " + SPECIALTY_NAMES[doctor->specialty];
			bot.getApi().sendMessage(curChatId, tmp, NULL, NULL, createSessionShowInlineKeyboard(ap.id));
		}
	}
	bot.getApi().sendMessage(curChatId, u8"Это все ваши записи.", NULL, NULL, createSessionsKeyboard());
	setUserProcess(curChatId, USER_PROCESS_SESSION);
}

/****************************************************************************************************/
void appointmentChoiceDateDoctor(Bot& bot, int64_t curChatId, int doctorId)
{
	if (doctorId)
	{
		Doctor* doctor = findDoctorId(doctorId);

		std::time_t now = std::time(nullptr);
		std::tm* ltm = std::localtime(&now);

		int day = getUserDay(curChatId);
		if (day == 0)
		{
			day = dayOfYear(ltm->tm_mday, ltm->tm_mon + 1, 0);
		}

		DOCTOR_INFO info;
		info.specialty = SPECIALTY_NAMES[doctor->specialty];
		info.firstName = { doctor->firstName };
		info.lastName = { doctor->lastName };
		info.middleName = { doctor->middleName };
		info.experience = { std::to_string(doctor->experience) };
		info.rating = { std::to_string(doctor->rating / 10) + "." + std::to_string(doctor->rating % 10) };

		std::string strSpec{
			u8"Специализация: " + info.specialty + "\n" +
			info.lastName + " " + info.firstName + " " + info.middleName +
			u8"\nСтаж " + info.experience + u8" лет\n"
			u8"⭐️" + info.rating + u8"\nВыберите дату:"
		};

		bot.getApi().sendPhoto(curChatId, doctor->photo_path, strSpec, NULL, createChoiceDateInlineKeyboard(day, doctorId));
		setUserProcess(curChatId, USER_PROCESS_CHOISE_DATE);
		setUserDay(curChatId, day);
	}
}

typedef struct 
{
	int dayOfYear;
	int doctorId;

} APPOINTMENT_DATE_DATA;

static void parseAppointment(const char* input, APPOINTMENT_DATE_DATA* dateData)
{
	sscanf(input, "%d %d", &dateData->dayOfYear, &dateData->doctorId);
}

// Функция сравнения для qsort
static int compareAppointments(const void* a, const void* b) 
{
	const Appointment* appA = (const Appointment*)a;
	const Appointment* appB = (const Appointment*)b;
	return appA->minOfDay - appB->minOfDay;
}

// Функция сортировки массива структур Appointment
static Appointment* sortAppointments(Appointment* appointments, size_t count) 
{
	qsort(appointments, count, sizeof(Appointment), compareAppointments);
	return appointments;
}

/****************************************************************************************************/
void appointmentChoiceTimeDoctor(Bot& bot, int64_t curChatId, const char* str)
{
	if (str != NULL)
	{
		APPOINTMENT_DATE_DATA dateData = { 0 };
		parseAppointment(str, &dateData);

		Doctor *doctor = findDoctorId(dateData.doctorId);
		
		std::time_t now = std::time(nullptr);
		std::tm* ltm = std::localtime(&now);

		//int day = dayOfMonth(dateData.dayOfYear, 0);
		//int month = monthOfYear(dateData.dayOfYear, 0);
		int year = ltm->tm_year + 1900;

		int appointments[MAX_CNT];
		int appointmentsCnt = MAX_CNT;		

		findAppointmentDoctorIdAndDate(appointments, &appointmentsCnt, doctor->id, dateData.dayOfYear, year);

		if (!appointmentsCnt || appointmentsCnt > MAX_CNT)
		{
			bot.getApi().sendMessage(curChatId, u8"К сожалению свободных приемов в этот день нет");
			appointmentChoiceDateDoctor(bot, curChatId, doctor->id);
			
			//setUserProcess(curChatId, USER_PROCESS_MAIN_MENU);
			return;
		}

		/* Находим все приемы и сортируем их */
		Appointment ap[MAX_CNT] = { 0 };
		for (UINT32 i = 0; i < appointmentsCnt; i++)
		{
			findAppointmentId(&ap[i], appointments[i]);	
		}
		sortAppointments(ap, appointmentsCnt);


		/* формируем строку времен */
		std::vector<std::string> times;
		for (UINT32 i = 0; i < appointmentsCnt; i++)
		{
			if (&ap != NULL)
			{
				std::string tmp = formatTime(ap[i].minOfDay);
				times.push_back(tmp);
				times.push_back(std::to_string(ap[i].id));
			}
		}

		DOCTOR_INFO info;
		info.specialty = SPECIALTY_NAMES[doctor->specialty];
		info.firstName = { doctor->firstName };
		info.lastName = { doctor->lastName };
		info.middleName = { doctor->middleName };
		info.experience = { std::to_string(doctor->experience) };
		info.rating = { std::to_string(doctor->rating / 10) + "." + std::to_string(doctor->rating % 10) };

		std::string strSpec{
			u8"Специализация: " + info.specialty + "\n" +
			info.lastName + " " + info.firstName + " " + info.middleName +
			u8"\nСтаж " + info.experience + u8" лет\n"
			u8"⭐️" + info.rating + u8"\nВыберите подходящее время приема:"
		};

		bot.getApi().sendPhoto(curChatId, doctor->photo_path, strSpec, NULL, createChoiceTimeInlineKeyboard(times));
		setUserProcess(curChatId, USER_PROCESS_CHOISE_TIME);
	}
}

/****************************************************************************************************/
void appointmentEdit(int id, Appointment* ap)
{
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

	return;
}

/****************************************************************************************************/
void findAppointmentId(Appointment* ap, int id)
{
	if (aps == NULL || cJSON_GetArraySize(aps) == 0)
	{
		return;
	}

	for (int i = 0; i < cJSON_GetArraySize(aps); i++)
	{
		cJSON* apJson = cJSON_GetArrayItem(aps, i);
		if (apJson != NULL)
		{
			cJSON* jsonDoctorId = cJSON_GetObjectItem(apJson, "id");
			if (jsonDoctorId != NULL && jsonDoctorId->valuedouble == id)
			{
				jsonToAp(apJson, ap);
			}
		}
	}

	return;
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
void findAppointmentDoctorIdAndDate(int* dst, int* size, int doctorId, int dayOfYear, int year)
{
	int slider = 0;

	if (NULL == dst || NULL == size || !size[0])
	{
		return;
	}
	memset(dst, -1, size[0] * sizeof(int));

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
				cJSON* apDay = cJSON_GetObjectItem(apJson, "dayOfYear");
				//cJSON* apMonth = cJSON_GetObjectItem(apJson, "month");
				cJSON* apYear = cJSON_GetObjectItem(apJson, "year");
				cJSON* apPatientId = cJSON_GetObjectItem(apJson, "patientId");
				//char strDate[12] = { 0 };
				//sprintf(strDate, "%d.3.2025", date);
				/* Проверка что даты совпадают, и никто еще не записан */
				if (apDay->valueint == dayOfYear && apYear->valueint == year && !apPatientId->valueint)
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

/****************************************************************************************************/
STATUS addAppointment(Appointment* ap)
{
	if (ap != NULL)
	{
		// Преобразование в JSON и добавление в массив
		cJSON* apJson = apToJson(ap);
		if (apJson != NULL)
		{
			cJSON_AddItemToArray(aps, apJson);
		}
	}

	// Сохранение в файл
	if (!saveDoctor("appointments.json", aps))
	{
		fprintf(stderr, "Ошибка: не удалось сохранить базу данных\n");
	}

	return KN_OK;
}

/****************************************************************************************************/
int findAppointment(int* dst, int size, int id, int doctorId, int patientId, int day, int year, int minute) 
{
	cJSON* appointment;
	int count = cJSON_GetArraySize(aps);
	int cntMatch = 0;
	for (int i = 0; i < count; i++) 
	{
		cJSON* appointment = cJSON_GetArrayItem(aps, i);

		int appId = cJSON_GetObjectItem(appointment, "id")->valueint;
		int appDoctorId = cJSON_GetObjectItem(appointment, "doctorId")->valueint;
		int appPatientId = cJSON_GetObjectItem(appointment, "patientId")->valueint;
		int appDay = cJSON_GetObjectItem(appointment, "dayOfYear")->valueint;
		//int appMonth = cJSON_GetObjectItem(appointment, "month")->valueint;
		int appYear = cJSON_GetObjectItem(appointment, "year")->valueint;
		//int appHour = cJSON_GetObjectItem(appointment, "hour")->valueint;
		int appMin = cJSON_GetObjectItem(appointment, "minOfDay")->valueint;

		int match = 1;
		if (id != 0xFFFFFFFF && appId != id) match = 0;
		if (doctorId != 0xFFFFFFFF && appDoctorId != doctorId) match = 0;
		if (patientId != 0xFFFFFFFF && appPatientId != patientId) match = 0;
		if (day != 0xFFFFFFFF && appDay != day) match = 0;
		//if (month != 0xFFFFFFFF && appMonth != month) match = 0;
		if (year != 0xFFFFFFFF && appYear != year) match = 0;
		//if (hour != 0xFFFFFFFF && appHour != hour) match = 0;
		if (minute != 0xFFFFFFFF && appMin != minute) match = 0;

		if (match) 
		{
			if (cntMatch < size)
			{
				dst[cntMatch] = appId;
			}
			cntMatch++;
		}
	}

	return cntMatch;
}

