#include "HospitalManagement.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "ConsoleColors.h"

HospitalManagement::HospitalManagement() {
    load_from_file();
}

// Doctor Management
void HospitalManagement::add_doctor() {
    string name;
    int age;
    int spec_choice;
    string password;

    cout << "Enter Doctor Name: ";
    getline(cin, name);
    cout << "Enter Doctor Age: ";
    cin >> age;
    cin.ignore();
    cout << "Choose Specialization:\n1. General\n2. Cardiologist\n3. Neurologist\n4. Pediatrician\n5. Surgeon\n";
    cout << "Enter choice (1-5): ";
    cin >> spec_choice;
    cin.ignore();

    if (spec_choice < 1 || spec_choice > 5) {
        Console::print_colored("Invalid specialization choice.", Console::RED);
        return;
    }
    Specialization spec = static_cast<Specialization>(spec_choice);

    cout << "Set Password for Doctor: ";
    getline(cin, password);

    add_doctor(name, age, spec, password);
}

void HospitalManagement::add_doctor(const string& name, int age, Specialization specialization, const string& password) {
    Doctor new_doctor(name, age, specialization, password);
    doctors.push_back(new_doctor);
    Console::print_colored("Doctor added successfully with ID: " + new_doctor.get_id(), Console::GREEN);
    save_to_file();
}

void HospitalManagement::list_doctors() const {
    if (doctors.empty()) {
        Console::print_colored("No doctors available.", Console::RED);
        return;
    }
    for (const auto& doctor : doctors) {
        doctor.display();
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

// Patient Management
void HospitalManagement::add_patient() {
    string name;
    int age;
    string medical_history;

    cout << "Enter Patient Name: ";
    getline(cin, name);
    cout << "Enter Patient Age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter Medical History: ";
    getline(cin, medical_history);

    add_patient(name, age, medical_history);
}

void HospitalManagement::add_patient(const string& name, int age, const string& medical_history) {
    Patient new_patient(name, age, medical_history);
    patients.push_back(new_patient);
    Console::print_colored("Patient added successfully with ID: " + new_patient.get_patient_id(), Console::GREEN);
    save_to_file();
}

void HospitalManagement::list_patients() const {
    if (patients.empty()) {
        Console::print_colored("No patients available.", Console::RED);
        return;
    }
    for (const auto& patient : patients) {
        patient.display();
    }
}

Patient* HospitalManagement::find_patient_by_id(const string& id) {
    for (auto& patient : patients) {
        if (patient.get_patient_id() == id) {
            return &patient;
        }
    }
    return nullptr;
}

// Appointment Management
void HospitalManagement::create_appointment() {
    string doctor_id, patient_id, date;
    cout << "Enter Doctor ID: ";
    cin >> doctor_id;
    cin.ignore();
    Doctor* doctor = find_doctor_by_id(doctor_id);
    if (!doctor) {
        Console::print_colored("Doctor with ID " + doctor_id + " not found.", Console::RED);
        return;
    }

    cout << "Enter Patient ID: ";
    cin >> patient_id;
    cin.ignore();
    Patient* patient = find_patient_by_id(patient_id);
    if (!patient) {
        Console::print_colored("Patient with ID " + patient_id + " not found.", Console::RED);
        return;
    }

    cout << "Enter Appointment Date (e.g., 2024-12-31): ";
    getline(cin, date);

    // Check for conflicting appointments
    for (const auto& appt : appointments) {
        if (appt.get_doctor() == doctor && appt.get_date() == date) {
            Console::print_colored("Doctor is not available on this date.", Console::RED);
            return;
        }
    }

    Appointment new_appointment(doctor, patient, date);
    appointments.push_back(new_appointment);
    Console::print_colored("Appointment created successfully with ID: " + new_appointment.get_appointment_id(), Console::GREEN);
    save_to_file();
}

void HospitalManagement::edit_appointment() {
    string appt_id;
    cout << "Enter Appointment ID to edit: ";
    cin >> appt_id;
    cin.ignore();

    Appointment* appt_to_edit = nullptr;
    for (auto& appt : appointments) {
        if (appt.get_appointment_id() == appt_id) {
            appt_to_edit = &appt;
            break;
        }
    }

    if (!appt_to_edit) {
        Console::print_colored("Appointment with ID " + appt_id + " not found.", Console::RED);
        return;
    }

    cout << "Editing Appointment ID: " << appt_id << endl;
    cout << "1. Change Doctor" << endl;
    cout << "2. Change Patient" << endl;
    cout << "3. Change Date" << endl;
    cout << "Choose an option to edit (1-3): ";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        string new_doctor_id;
        cout << "Enter new Doctor ID: ";
        cin >> new_doctor_id;
        cin.ignore();
        Doctor* new_doctor = find_doctor_by_id(new_doctor_id);
        if (!new_doctor) {
            Console::print_colored("Doctor with ID " + new_doctor_id + " not found.", Console::RED);
            return;
        }
        // Check for doctor's availability on the appointment date
        for (const auto& appt : appointments) {
            if (appt.get_doctor() == new_doctor && appt.get_date() == appt_to_edit->get_date()) {
                Console::print_colored("Doctor is not available on this date.", Console::RED);
                return;
            }
        }
        appt_to_edit->set_doctor(new_doctor);
        Console::print_colored("Doctor updated successfully.", Console::GREEN);
        break;
    }
    case 2: {
        string new_patient_id;
        cout << "Enter new Patient ID: ";
        cin >> new_patient_id;
        cin.ignore();
        Patient* new_patient = find_patient_by_id(new_patient_id);
        if (!new_patient) {
            Console::print_colored("Patient with ID " + new_patient_id + " not found.", Console::RED);
            return;
        }
        appt_to_edit->set_patient(new_patient);
        Console::print_colored("Patient updated successfully.", Console::GREEN);
        break;
    }
    case 3: {
        string new_date;
        cout << "Enter new Appointment Date (e.g., 2024-12-31): ";
        getline(cin, new_date);
        // Check for doctor's availability on the new date
        Doctor* doctor = appt_to_edit->get_doctor();
        for (const auto& appt : appointments) {
            if (appt.get_doctor() == doctor && appt.get_date() == new_date) {
                Console::print_colored("Doctor is not available on this new date.", Console::RED);
                return;
            }
        }
        appt_to_edit->set_date(new_date);
        Console::print_colored("Date updated successfully.", Console::GREEN);
        break;
    }
    default:
        Console::print_colored("Invalid option. Returning to Admin Menu.", Console::RED);
    }
    save_to_file();
}

void HospitalManagement::delete_appointment() {
    string appt_id;
    cout << "Enter Appointment ID to delete: ";
    cin >> appt_id;
    cin.ignore();

    auto it = remove_if(appointments.begin(), appointments.end(),
        [&](const Appointment& appt) { return appt.get_appointment_id() == appt_id; });
    if (it != appointments.end()) {
        appointments.erase(it, appointments.end());
        Console::print_colored("Appointment with ID " + appt_id + " deleted successfully.", Console::GREEN);
        save_to_file();
    }
    else {
        Console::print_colored("Appointment with ID " + appt_id + " not found.", Console::RED);
    }
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

// Data Persistence
void HospitalManagement::save_to_file() {
    // Save Doctors
    ofstream doctors_file("doctors.csv");
    if (doctors_file.is_open()) {
        doctors_file << "id,name,age,specialization,password\n";
        for (const auto& doc : doctors) {
            doctors_file << doc.get_id() << ","
                << doc.get_name() << ","
                << doc.get_age() << ","
                << static_cast<int>(doc.get_specialization()) << ","
                << doc.get_password() << "\n";
        }
        doctors_file.close();
    }
    else {
        Console::print_colored("Error opening doctors.csv for writing.", Console::RED);
    }

    // Save Patients
    ofstream patients_file("patients.csv");
    if (patients_file.is_open()) {
        patients_file << "patient_id,name,age,medical_history\n";
        for (const auto& pat : patients) {
            patients_file << pat.get_patient_id() << ","
                << pat.get_name() << ","
                << pat.get_age() << ","
                << pat.get_medical_history() << "\n";
        }
        patients_file.close();
    }
    else {
        Console::print_colored("Error opening patients.csv for writing.", Console::RED);
    }

    // Save Appointments
    ofstream appointments_file("appointments.csv");
    if (appointments_file.is_open()) {
        appointments_file << "appointment_id,doctor_id,patient_id,date\n";
        for (const auto& appt : appointments) {
            appointments_file << appt.get_appointment_id() << ","
                << appt.get_doctor()->get_id() << ","
                << appt.get_patient()->get_patient_id() << ","
                << appt.get_date() << "\n";
        }
        appointments_file.close();
    }
    else {
        Console::print_colored("Error opening appointments.csv for writing.", Console::RED);
    }

    Console::print_colored("Data saved successfully.", Console::GREEN);
}

void HospitalManagement::load_from_file() {
    // Load Doctors
    ifstream doctors_file("doctors.csv");
    if (doctors_file.is_open()) {
        string line;
        // Read header
        getline(doctors_file, line);
        while (getline(doctors_file, line)) {
            // Split CSV line
            stringstream ss(line);
            string id, name, age_str, spec_str, password;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, age_str, ',');
            getline(ss, spec_str, ',');
            getline(ss, password, ',');

            int age = stoi(age_str);
            Specialization spec = static_cast<Specialization>(stoi(spec_str));
            Doctor doc(name, age, spec, password);
            doc.set_id(id);
            doctors.push_back(doc);
        }
        doctors_file.close();
    }
    else {
        Console::print_colored("doctors.csv not found. Starting with empty doctors list.", Console::YELLOW);
    }

    // Load Patients
    ifstream patients_file("patients.csv");
    if (patients_file.is_open()) {
        string line;
        // Read header
        getline(patients_file, line);
        while (getline(patients_file, line)) {
            // Split CSV line
            stringstream ss(line);
            string pid, name, age_str, history;
            getline(ss, pid, ',');
            getline(ss, name, ',');
            getline(ss, age_str, ',');
            getline(ss, history, ',');

            int age = stoi(age_str);
            Patient pat(name, age, history);
            pat.set_patient_id(pid);
            patients.push_back(pat);
        }
        patients_file.close();
    }
    else {
        Console::print_colored("patients.csv not found. Starting with empty patients list.", Console::YELLOW);
    }

    // Load Appointments
    ifstream appointments_file("appointments.csv");
    if (appointments_file.is_open()) {
        string line;
        // Read header
        getline(appointments_file, line);
        while (getline(appointments_file, line)) {
            // Split CSV line
            stringstream ss(line);
            string aid, did, pid, date;
            getline(ss, aid, ',');
            getline(ss, did, ',');
            getline(ss, pid, ',');
            getline(ss, date, ',');

            Doctor* doctor = find_doctor_by_id(did);
            Patient* patient = find_patient_by_id(pid);
            if (doctor && patient) {
                Appointment appt(doctor, patient, date);
                appt.set_appointment_id(aid);
                appointments.push_back(appt);
            }
        }
        appointments_file.close();
    }
    else {
        Console::print_colored("appointments.csv not found. Starting with empty appointments list.", Console::YELLOW);
    }
}

// Authentication
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
        Console::print_colored("Login successful. Welcome, " + doctor->get_name() + "!", Console::GREEN);
        return doctor;
    }
    Console::print_colored("Invalid Doctor credentials.", Console::RED);
    return nullptr;
}

Patient* HospitalManagement::patient_login() {
    string id;
    cout << "Enter Patient ID: ";
    cin >> id;
    cin.ignore();
    Patient* patient = find_patient_by_id(id);
    if (patient) {
        Console::print_colored("Login successful. Welcome, " + patient->get_name() + "!", Console::GREEN);
        return patient;
    }
    Console::print_colored("Invalid Patient ID.", Console::RED);
    return nullptr;
}
