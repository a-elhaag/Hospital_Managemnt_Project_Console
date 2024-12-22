#include "Doctor.h"
#include "ConsoleColors.h"
#include <iostream>

int Doctor::doc_counter = 0;

Doctor::Doctor() : Human(), specialization(Specialization::GENERAL), password("") {
    doc_counter++;
    id = "D" + to_string(doc_counter);
}

Doctor::Doctor(const string& name_, int age_, Specialization specialization_, const string& password_)
    : Human(name_, age_), specialization(specialization_), password(password_) {
    doc_counter++;
    id = "D" + to_string(doc_counter);
}

void Doctor::display() const {
    string spec_str;
    switch (specialization) {
    case Specialization::GENERAL: spec_str = "General"; break;
    case Specialization::CARDIOLOGIST: spec_str = "Cardiologist"; break;
    case Specialization::NEUROLOGIST: spec_str = "Neurologist"; break;
    case Specialization::PEDIATRICIAN: spec_str = "Pediatrician"; break;
    case Specialization::SURGEON: spec_str = "Surgeon"; break;
    default: spec_str = "Unknown"; break;
    }
    Console::print_colored("Doctor ID: " + id + ", Name: " + name + ", Age: " + to_string(age) + ", Specialization: " + spec_str, Console::BLUE);
}

void Doctor::set_specialization(Specialization spec) {
    specialization = spec;
}

string Doctor::get_id() const {
    return id;
}

Specialization Doctor::get_specialization() const {
    return specialization;
}

string Doctor::get_password() const {
    return password;
}

void Doctor::set_id(const string& new_id) {
    id = new_id;
    // Update doc_counter based on the numeric part of id
    if (new_id.length() > 1) {
        int num = stoi(new_id.substr(1));
        if (num > doc_counter) {
            doc_counter = num;
        }
    }
}
