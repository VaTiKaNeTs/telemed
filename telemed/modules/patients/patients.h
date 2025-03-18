#include "../../knTypes.h"
#include "../dataBase/dataBase.h"

void patientInit(void);

void patientEdit(int id, PatientData* patient);

STATUS addPatient(PatientData* patient);

STATUS removePatient(long id);

STATUS cleanAllPatients(void);

void findPatientId(PatientData* patient, int id);

PatientData* findPatientChatId(long chatId);

int getPatientsCnt(void);