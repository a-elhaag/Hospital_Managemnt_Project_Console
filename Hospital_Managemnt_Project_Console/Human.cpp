// Human.cpp
#include "Human.h"

Human::Human() : name(""), age(0) {}

Human::Human(const string& name_, int age_) : name(name_), age(age_) {}

void Human::set_age(int age_) {
    age = age_;
}

void Human::set_name(const string& name_) {
    name = name_;
}

int Human::get_age() const {
    return age;
}

string Human::get_name() const {
    return name;
}
