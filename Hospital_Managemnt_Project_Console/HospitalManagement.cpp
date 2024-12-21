#include "HospitalManagement.h"
#include <iostream>
#include <fstream>
#include "ConsoleColors.h"
using namespace std;

void HospitalManagement::add_doctor() {
    Doctor new_doctor;
    doctors.push_back(new_doctor);
}

void HospitalManagement::add_patient() {
    Patient new_patient;
    patients.push_back(new_patient);
}

void HospitalManagement::list_doctors() const {
    if (doctors.empty()) {
        Console::print_colored("No doctors available.", Console::RED, Console::BG_BLACK);
        return;
    }
    for (const auto& doctor : doctors) {
        doctor.display();
    }
}

void HospitalManagement::list_patients() const {
    if (patients.empty()) {
        Console::print_colored("No patients available.", Console::RED, Console::BG_BLACK);
        return;
    }
    for (const auto& patient : patients) {
        patient.display();
    }
}

Doctor* HospitalManagement::find_doctor_by_id(const string& id) {
    for (auto& doctor : doctors) {
        if (doctor.get_id() == id) {
            return &doctor;
        }
    }
    return nullptr;
}

Patient* HospitalManagement::find_patient_by_id(const string& id) {
    for (auto& patient : patients) {
        if (patient.get_patient_id() == id) {
            return &patient;
        }
    }
    return nullptr;
}

void HospitalManagement::book_appointment() {
    if (doctors.empty()) {
        Console::print_colored("No doctors available to book an appointment.", Console::RED, Console::BG_BLACK);
        return;
    }
    if (patients.empty()) {
        Console::print_colored("No patients available to book an appointment.", Console::RED, Console::BG_BLACK);
        return;
    }
    string doctor_id, patient_id, date;
    cout << "Enter Doctor ID: ";
    cin >> doctor_id;
    cin.ignore();
    Doctor* doctor = find_doctor_by_id(doctor_id);
    if (!doctor) {
        Console::print_colored("Doctor with ID " + doctor_id + " not found.", Console::RED, Console::BG_BLACK);
        return;
    }
    cout << "Enter Patient ID: ";
    cin >> patient_id;
    cin.ignore();
    Patient* patient = find_patient_by_id(patient_id);
    if (!patient) {
        Console::print_colored("Patient with ID " + patient_id + " not found.", Console::RED, Console::BG_BLACK);
        return;
    }
    cout << "Enter Appointment Date (e.g., 2024-12-31): ";
    getline(cin, date);
    for (const auto& appt : appointments) {
        if (appt.get_doctor() == doctor && appt.get_date() == date) {
            Console::print_colored("Doctor is not available on this date.", Console::RED, Console::BG_BLACK);
            return;
        }
    }
    Appointment new_appointment(doctor, patient, date);
    appointments.push_back(new_appointment);
    Console::print_colored("Appointment booked successfully with ID " + new_appointment.get_appointment_id() + ".", Console::GREEN, Console::BG_BLACK);
}

void HospitalManagement::list_appointments() const {
    if (appointments.empty()) {
        Console::print_colored("No appointments booked.", Console::RED, Console::BG_BLACK);
        return;
    }
    for (const auto& appointment : appointments) {
        appointment.display();
    }
}

void HospitalManagement::save_to_file() {
    ofstream file("hospital_data.txt");
    if (!file.is_open()) {
        Console::print_colored("Error opening file for saving.", Console::RED, Console::BG_BLACK);
        return;
    }
    file << "Doctors\n";
    for (const auto& doctor : doctors) {
        file << doctor.get_id() << "," << doctor.get_name() << "," << doctor.get_age() << "," << doctor.get_specialization() << "," << doctor.get_password() << "\n";
    }
    file << "Patients\n";
    for (const auto& patient : patients) {
        file << patient.get_patient_id() << "," << patient.get_name() << "," << patient.get_age() << "," << patient.get_medical_history() << "," << patient.get_password() << "\n";
    }
    file << "Appointments\n";
    for (const auto& appointment : appointments) {
        file << appointment.get_appointment_id() << "," << appointment.get_doctor()->get_id() << "," << appointment.get_patient()->get_patient_id() << "," << appointment.get_date() << "\n";
    }
    file.close();
    Console::print_colored("Data saved successfully.", Console::GREEN, Console::BG_BLACK);
}

void HospitalManagement::load_from_file() {
    ifstream file("hospital_data.txt");
    if (!file.is_open()) {
        Console::print_colored("Error opening file for loading.", Console::RED, Console::BG_BLACK);
        return;
    }
    string line;
    enum Section { NONE, DOCTORS, PATIENTS, APPOINTMENTS };
    Section current_section = NONE;
    while (getline(file, line)) {
        if (line == "Doctors") {
            current_section = DOCTORS;
            continue;
        }
        if (line == "Patients") {
            current_section = PATIENTS;
            continue;
        }
        if (line == "Appointments") {
            current_section = APPOINTMENTS;
            continue;
        }
        if (current_section == DOCTORS) {
            string id, name, age_str, spec_str, password;
            size_t pos = 0;
            pos = line.find(',');
            id = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            age_str = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            spec_str = line.substr(0, pos);
            line.erase(0, pos + 1);
            password = line;
            Doctor doc;
            doc.set_name(name);
            doc.set_age(stoi(age_str));
            doc.set_specialization(static_cast<Specialization>(stoi(spec_str)));
            doc.set_password(password);
            doctors.push_back(doc);
        }
        else if (current_section == PATIENTS) {
            string pid, name, age_str, history, password;
            size_t pos = 0;
            pos = line.find(',');
            pid = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            age_str = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            history = line.substr(0, pos);
            line.erase(0, pos + 1);
            password = line;
            Patient pat;
            pat.set_name(name);
            pat.set_age(stoi(age_str));
            pat.set_medical_history(history);
            pat.set_password(password);
            patients.push_back(pat);
        }
        else if (current_section == APPOINTMENTS) {
            string aid, did, pid, date;
            size_t pos = 0;
            pos = line.find(',');
            aid = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            did = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            pid = line.substr(0, pos);
            line.erase(0, pos + 1);
            date = line;
            Doctor* doctor = find_doctor_by_id(did);
            Patient* patient = find_patient_by_id(pid);
            if (doctor && patient) {
                Appointment appt(doctor, patient, date);
                appointments.push_back(appt);
            }
        }
    }
    file.close();
    Console::print_colored("Data loaded successfully.", Console::GREEN, Console::BG_BLACK);
}

bool HospitalManagement::admin_login() {
    string username, password;
    cout << "Enter Admin username: ";
    cin >> username;
    cout << "Enter Admin password: ";
    cin >> password;
    cin.ignore();
    return (username == "admin" && password == "admin123");
}

Doctor* HospitalManagement::doctor_login() {
    string id, password;
    cout << "Enter Doctor ID: ";
    cin >> id;
    cout << "Enter Doctor password: ";
    cin >> password;
    cin.ignore();
    Doctor* doctor = find_doctor_by_id(id);
    if (doctor && doctor->get_password() == password) {
        return doctor;
    }
    return nullptr;
}

Patient* HospitalManagement::patient_login() {
    string id, password;
    cout << "Enter Patient ID: ";
    cin >> id;
    cout << "Enter Patient password: ";
    cin >> password;
    cin.ignore();
    Patient* patient = find_patient_by_id(id);
    if (patient && patient->get_password() == password) {
        return patient;
    }
    return nullptr;
}

vector<Appointment> HospitalManagement::get_appointments_for_doctor(const Doctor* doctor) const {
    vector<Appointment> result;
    for (const auto& appt : appointments) {
        if (appt.get_doctor() == doctor) {
            result.push_back(appt);
        }
    }
    return result;
}

vector<Appointment> HospitalManagement::get_appointments_for_patient(const Patient* patient) const {
    vector<Appointment> result;
    for (const auto& appt : appointments) {
        if (appt.get_patient() == patient) {
            result.push_back(appt);
        }
    }
    return result;
}
