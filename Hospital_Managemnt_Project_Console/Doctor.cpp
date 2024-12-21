#include "Doctor.h"
#include "ConsoleColors.h"

int Doctor::doc_counter = 0;

Doctor::Doctor() : Human() {
    doc_counter++;
    cout << "Choose your specialization:\n1) General\n2) Cardiologist\n3) Neurologist\n4) Pediatrician\n5) Surgeon\n";
    int choice;
    while (true) {
        cout << "Enter choice (1-5): ";
        cin >> choice;
        cin.ignore();
        if (choice >= 1 && choice <= 5) {
            specialization = static_cast<Specialization>(choice);
            break;
        }
    }
    id = "";
    switch (specialization) {
    case General: id += "G"; break;
    case Cardiologist: id += "C"; break;
    case Neurologist: id += "N"; break;
    case Pediatrician: id += "P"; break;
    case Surgeon: id += "S"; break;
    }
    id += to_string(doc_counter);
    cout << "Enter your password: ";
    cin >> password;
    cin.ignore();
    Console::print_colored("Welcome Dr. " + name + "! Your ID is " + id + ".", Console::BLUE, Console::BG_WHITE);
}

void Doctor::set_specialization(Specialization specialization) {
    this->specialization = specialization;
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

void Doctor::display() const {
    cout << Console::BG_WHITE << Console::BLUE;
    cout << "Doctor ID: " << id << ", Name: " << name << ", Age: " << age << ", Specialization: ";
    switch (specialization) {
    case General: cout << "General"; break;
    case Cardiologist: cout << "Cardiologist"; break;
    case Neurologist: cout << "Neurologist"; break;
    case Pediatrician: cout << "Pediatrician"; break;
    case Surgeon: cout << "Surgeon"; break;
    }
    cout << Console::RESET << endl;
}

ostream& operator<<(ostream& os, const Doctor& doctor) {
    os << "Doctor ID: " << doctor.id << ", Name: " << doctor.name << ", Age: " << doctor.age << ", Specialization: ";
    switch (doctor.specialization) {
    case General: os << "General"; break;
    case Cardiologist: os << "Cardiologist"; break;
    case Neurologist: os << "Neurologist"; break;
    case Pediatrician: os << "Pediatrician"; break;
    case Surgeon: os << "Surgeon"; break;
    }
    return os;
}

void Doctor::set_password(const string& password) {
	this->password = password;
}