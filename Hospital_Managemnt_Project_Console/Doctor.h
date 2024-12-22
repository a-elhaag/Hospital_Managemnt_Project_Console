#pragma once
#include "Human.h"
#include <string>

using namespace std;
enum class Specialization {
    GENERAL = 1,
    CARDIOLOGIST,
    NEUROLOGIST,
    PEDIATRICIAN,
    SURGEON
};

class Doctor : public Human {
private:
    static int doc_counter;
    string id;
    string password;
    Specialization specialization;
public:
    Doctor();
    Doctor(const string& name, int age, Specialization specialization_, const string& password_);
    void display() const override;
    void set_specialization(Specialization spec);
    string get_id() const;
    Specialization get_specialization() const;
    string get_password() const;
    void set_id(const string& new_id); // For loading from file
};
