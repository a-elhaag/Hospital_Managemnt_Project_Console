#pragma once
#include "Human.h"
#include <string>
using namespace std;

enum Specialization {
    General = 1,
    Cardiologist,
    Neurologist,
    Pediatrician,
    Surgeon
};

class Doctor : public Human {
private:
    static int doc_counter;
    string id;
    string password;
    Specialization specialization;
public:
    Doctor();
    void set_specialization(Specialization specialization);
    string get_id() const;
    Specialization get_specialization() const;
    string get_password() const;
	void set_password(const string& password);
    void display() const override;
    friend ostream& operator<<(ostream& os, const Doctor& doctor);
};
