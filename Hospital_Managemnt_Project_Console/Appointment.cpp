#include "Appointment.h"
#include "Doctor.h"
#include "Patient.h"
#include "ConsoleColors.h"

int Appointment::appointment_counter = 0;

Appointment::Appointment(Doctor* doc, Patient* pat, const string& date) : doctor(doc), patient(pat), date(date) {
    appointment_counter++;
    appointment_id = "A" + to_string(appointment_counter);
}

void Appointment::display() const {
    cout << Console::BG_MAGENTA << Console::WHITE;
    cout << "Appointment ID: " << appointment_id << ", Date: " << date << endl;
    cout << "Doctor: " << doctor->get_name() << " (ID: " << doctor->get_id() << "), ";
    cout << "Patient: " << patient->get_name() << " (ID: " << patient->get_patient_id() << ")" << endl;
    cout << Console::RESET;
}

string Appointment::get_appointment_id() const {
    return appointment_id;
}

Doctor* Appointment::get_doctor() const {
    return doctor;
}

Patient* Appointment::get_patient() const {
    return patient;
}

string Appointment::get_date() const {
    return date;
}
