

#ifndef DOCTORS_DB_H
#define DOCTORS_DB_H

#include "../../knTypes.h"
#include "doctorDataBase.h"

void doctorInit(void);

void doctorEdit(int id, Doctor* doctor);

STATUS addDoctor(Doctor* doctor);

STATUS removeDoctor(long id);

STATUS cleanAllDoctors(void);

Doctor* findDoctorId(int id);

void findDoctorSpec(int* dst, int* size, SPECIALITY spec);

#endif DOCTORS_DB_H