#include "../../knTypes.h"
#include "../dataBase/dataBase.h"

void patientInit(void);

STATUS addPatient(PatientData* patient);

STATUS removePatient(long id);

PatientData* findPatientChatId(long chatId);