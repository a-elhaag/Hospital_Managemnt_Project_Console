#pragma once
#include <iostream>
#include <string>
using namespace std;

class Human {
protected:
    int age;
    string name;
public:
    Human();
    virtual void display() const;
    void set_age(int age);
    void set_name(const string& name);
    int get_age() const;
    string get_name() const;
};
