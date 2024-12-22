// Patient.cpp
#include "Patient.h"
#include "ConsoleColors.h"
#include <iostream>

int Patient::patient_counter = 0;

Patient::Patient() : Human(), medical_history("") {
    patient_counter++;
    patient_id = "P" + to_string(patient_counter);
}

Patient::Patient(const string& name_, int age_, const string& medical_history_)
    : Human(name_, age_), medical_history(medical_history_) {
    patient_counter++;
    patient_id = "P" + to_string(patient_counter);
}

void Patient::display() const {
    Console::print_colored("Patient ID: " + patient_id + ", Name: " + name + ", Age: " + to_string(age) + ", Medical History: " + medical_history, Console::GREEN);
}

string Patient::get_patient_id() const {
    return patient_id;
}

string Patient::get_medical_history() const {
    return medical_history;
}

void Patient::set_patient_id(const string& new_id) {
    patient_id = new_id;
    // Update patient_counter based on the numeric part of id
    if (new_id.length() > 1) {
        int num = stoi(new_id.substr(1));
        if (num > patient_counter) {
            patient_counter = num;
        }
    }
}

void Patient::set_medical_history(const string& history) {
    medical_history = history;
}
