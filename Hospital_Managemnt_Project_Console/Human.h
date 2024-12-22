#pragma once
#include <string>

using namespace std;
class Human {
protected:
    int age;
    string name;
public:
    Human();
    Human(const string& name, int age);
    virtual void display() const = 0; // Pure virtual function
    void set_age(int age);
    void set_name(const string& name);
    int get_age() const;
    string get_name() const;
};
