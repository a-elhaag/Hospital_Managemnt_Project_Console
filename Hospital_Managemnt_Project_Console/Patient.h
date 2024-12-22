#pragma once
#include "Human.h"
#include <string>

using namespace std;

class Patient : public Human {
private:
    static int patient_counter;
    string patient_id;
    string medical_history;
public:
    Patient();
    Patient(const string& name, int age, const string& medical_history_);
    void display() const override;
    string get_patient_id() const;
    string get_medical_history() const;
    void set_patient_id(const string& new_id); // For loading from file
    void set_medical_history(const string& history);
};
