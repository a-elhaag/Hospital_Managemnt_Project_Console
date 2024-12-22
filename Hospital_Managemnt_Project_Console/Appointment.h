#pragma once
#include <string>
using namespace std;
class Doctor;
class Patient;

class Appointment {
private:
    static int appointment_counter;
    string appointment_id;
    Doctor* doctor;
    Patient* patient;
    string date;
public:
    Appointment();
    Appointment(Doctor* doc, Patient* pat, const string& date_);
    void display() const;
    string get_appointment_id() const;
    Doctor* get_doctor() const;
    Patient* get_patient() const;
    string get_date() const;
    void set_doctor(Doctor* new_doctor);
    void set_patient(Patient* new_patient);
    void set_date(const string& new_date);
    void set_appointment_id(const string& new_id); // For loading from file
};
