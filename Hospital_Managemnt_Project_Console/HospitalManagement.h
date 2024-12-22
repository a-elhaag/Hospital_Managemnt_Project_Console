#pragma once
#include <vector>
#include <string>
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
using  namespace std;
class HospitalManagement {
private:
    std::vector<Doctor> doctors;
    std::vector<Patient> patients;
    std::vector<Appointment> appointments;
public:
    HospitalManagement();

    // Doctor Management
    void add_doctor();
    void add_doctor(const std::string& name, int age, Specialization specialization, const std::string& password);
    void list_doctors() const;
    Doctor* find_doctor_by_id(const std::string& id);

    // Patient Management
    void add_patient();
    void add_patient(const std::string& name, int age, const std::string& medical_history);
    void list_patients() const;
    Patient* find_patient_by_id(const std::string& id);

    // Appointment Management
    void create_appointment();
    void edit_appointment();
    void delete_appointment();
    std::vector<Appointment> get_appointments_for_doctor(const Doctor* doctor) const;
    std::vector<Appointment> get_appointments_for_patient(const Patient* patient) const;

    // Data Persistence
    void save_to_file();
    void load_from_file();

    // Authentication
    bool admin_login();
    Doctor* doctor_login();
    Patient* patient_login();
};
