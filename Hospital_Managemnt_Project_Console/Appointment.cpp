#include "Appointment.h"
#include "Doctor.h"
#include "Patient.h"
#include "ConsoleColors.h"
#include <iostream>

int Appointment::appointment_counter = 0;

Appointment::Appointment() : doctor(nullptr), patient(nullptr), date("") {
    appointment_counter++;
    appointment_id = "A" + to_string(appointment_counter);
}

Appointment::Appointment(Doctor* doc, Patient* pat, const string& date_)
    : doctor(doc), patient(pat), date(date_) {
    appointment_counter++;
    appointment_id = "A" + to_string(appointment_counter);
}

void Appointment::display() const {
    string date_str = date;
    string doctor_info = (doctor != nullptr) ? doctor->get_name() + " (" + doctor->get_id() + ")" : "Unknown";
    string patient_info = (patient != nullptr) ? patient->get_name() + " (" + patient->get_patient_id() + ")" : "Unknown";
    Console::print_colored(
        "Appointment ID: " + appointment_id + ", Date: " + date_str +
        ", Doctor: " + doctor_info + ", Patient: " + patient_info,
        Console::MAGENTA
    );
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

void Appointment::set_doctor(Doctor* new_doctor) {
    doctor = new_doctor;
}

void Appointment::set_patient(Patient* new_patient) {
    patient = new_patient;
}

void Appointment::set_date(const string& new_date_) {
    date = new_date_;
}

void Appointment::set_appointment_id(const string& new_id) {
    appointment_id = new_id;
    if (new_id.length() > 1) {
        int num = stoi(new_id.substr(1));
        if (num > appointment_counter) {
            appointment_counter = num;
        }
    }
}
