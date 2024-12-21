#pragma once
#include "Human.h"
#include <string>
using namespace std;

class Patient : public Human {
private:
    static int patient_counter;
    string patient_id;
    string medical_history;
    string password;
public:
    Patient();
    void set_medical_history(const string& history);
    string get_patient_id() const;
    string get_medical_history() const;
    string get_password() const;
    void set_password(const string& pwd);
    void display() const override;
    friend ostream& operator<<(ostream& os, const Patient& patient);
};
