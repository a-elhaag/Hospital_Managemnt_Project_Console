#include "Human.h"

Human::Human() {
    cout << "Please enter your name: ";
    getline(cin, name);
    cout << "Please enter your age: ";
    cin >> age;
    cin.ignore();
}

void Human::set_age(int age) {
    this->age = age;
}

void Human::set_name(const string& name) {
    this->name = name;
}

int Human::get_age() const {
    return age;
}

string Human::get_name() const {
    return name;
}

void Human::display() const {
    cout << "Name: " << name << ", Age: " << age;
}
