#pragma once
#include <string>
using namespace std;

class Doctor;
class Patient;

class Appointment {
private:
    string appointment_id;
    Doctor* doctor;
    Patient* patient;
    string date;
    static int appointment_counter;
public:
    Appointment(Doctor* doc, Patient* pat, const string& date);
    void display() const;
    string get_appointment_id() const;
    Doctor* get_doctor() const;
    Patient* get_patient() const;
    string get_date() const;
};
