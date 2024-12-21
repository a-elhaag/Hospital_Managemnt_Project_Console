#include "Patient.h"
#include "ConsoleColors.h"

int Patient::patient_counter = 0;

Patient::Patient() : Human() {
    patient_counter++;
    patient_id = "P" + to_string(patient_counter);
    cout << "Please enter your medical history: ";
    getline(cin, medical_history);
    cout << "Set your password: ";
    cin >> password;
    cin.ignore();
    Console::print_colored("Patient registered successfully! Your Patient ID is " + patient_id + ".", Console::GREEN, Console::BG_CYAN);
}

void Patient::set_medical_history(const string& history) {
    medical_history = history;
}

string Patient::get_patient_id() const {
    return patient_id;
}

string Patient::get_medical_history() const {
    return medical_history;
}

string Patient::get_password() const {
    return password;
}

void Patient::set_password(const string& pwd) {
    password = pwd;
}

void Patient::display() const {
    cout << Console::BG_CYAN << Console::GREEN;
    cout << "Patient ID: " << patient_id << ", Name: " << name << ", Age: " << age << ", Medical History: " << medical_history << endl;
    cout << Console::RESET;
}

ostream& operator<<(ostream& os, const Patient& patient) {
    os << "Patient ID: " << patient.patient_id << ", Name: " << patient.name << ", Age: " << patient.age << ", Medical History: " << patient.medical_history;
    return os;
}
