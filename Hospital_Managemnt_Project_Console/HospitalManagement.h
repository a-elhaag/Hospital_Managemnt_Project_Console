#pragma once
#include <vector>
#include <string>
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
using namespace std;

class HospitalManagement {
private:
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointments;
public:
    void add_doctor();
    void add_patient();
    void list_doctors() const;
    void list_patients() const;
    Doctor* find_doctor_by_id(const string& id);
    Patient* find_patient_by_id(const string& id);
    void book_appointment();
    void list_appointments() const;
    void save_to_file();
    void load_from_file();
    bool admin_login();
    Doctor* doctor_login();
    Patient* patient_login();
    vector<Appointment> get_appointments_for_doctor(const Doctor* doctor) const;
    vector<Appointment> get_appointments_for_patient(const Patient* patient) const;
};
