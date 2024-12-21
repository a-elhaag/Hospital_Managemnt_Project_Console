#include <iostream>
#include "HospitalManagement.h"
#include "ConsoleColors.h"
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

void admin_menu() {
    Console::print_colored("\n--- Admin Menu ---", Console::YELLOW, Console::BG_BLACK);
    Console::print_colored("1. Add a new doctor", Console::BLUE);
    Console::print_colored("2. Add a new patient", Console::GREEN);
    Console::print_colored("3. View all doctors", Console::BLUE);
    Console::print_colored("4. View all patients", Console::GREEN);
    Console::print_colored("5. Search for a doctor by ID", Console::BLUE);
    Console::print_colored("6. Search for a patient by ID", Console::GREEN);
    Console::print_colored("7. Save data", Console::MAGENTA);
    Console::print_colored("8. Load data", Console::MAGENTA);
    Console::print_colored("9. Logout", Console::RED);
    Console::print_colored("Choose an option (1-9): ", Console::WHITE);
}

void doctor_menu() {
    Console::print_colored("\n--- Doctor Menu ---", Console::BLUE, Console::BG_WHITE);
    Console::print_colored("1. View my details", Console::BLUE);
    Console::print_colored("2. View my appointments", Console::CYAN);
    Console::print_colored("3. Logout", Console::RED);
    Console::print_colored("Choose an option (1-3): ", Console::WHITE);
}

void patient_menu() {
    Console::print_colored("\n--- Patient Menu ---", Console::GREEN, Console::BG_CYAN);
    Console::print_colored("1. View my details", Console::GREEN);
    Console::print_colored("2. View my appointments", Console::CYAN);
    Console::print_colored("3. Logout", Console::RED);
    Console::print_colored("Choose an option (1-3): ", Console::WHITE);
}

int main() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    HospitalManagement hm;
    int role_choice;
    while (true) {
        Console::print_colored("\nLogin as:", Console::WHITE, Console::BG_BLACK);
        Console::print_colored("1. Admin", Console::YELLOW);
        Console::print_colored("2. Doctor", Console::BLUE);
        Console::print_colored("3. Patient", Console::GREEN);
        Console::print_colored("4. Exit", Console::RED);
        Console::print_colored("Choose a role (1-4): ", Console::WHITE);
        cin >> role_choice;
        cin.ignore();
        switch (role_choice) {
        case 1: {
            if (hm.admin_login()) {
                while (true) {
                    admin_menu();
                    int admin_choice;
                    cin >> admin_choice;
                    cin.ignore();
                    switch (admin_choice) {
                    case 1:
                        hm.add_doctor();
                        break;
                    case 2:
                        hm.add_patient();
                        break;
                    case 3:
                        hm.list_doctors();
                        break;
                    case 4:
                        hm.list_patients();
                        break;
                    case 5: {
                        string did;
                        cout << "Enter Doctor ID: ";
                        cin >> did;
                        cin.ignore();
                        Doctor* doctor = hm.find_doctor_by_id(did);
                        if (doctor) {
                            doctor->display();
                        }
                        else {
                            Console::print_colored("Doctor not found.", Console::RED, Console::BG_BLACK);
                        }
                        break;
                    }
                    case 6: {
                        string pid;
                        cout << "Enter Patient ID: ";
                        cin >> pid;
                        cin.ignore();
                        Patient* patient = hm.find_patient_by_id(pid);
                        if (patient) {
                            patient->display();
                        }
                        else {
                            Console::print_colored("Patient not found.", Console::RED, Console::BG_BLACK);
                        }
                        break;
                    }
                    case 7:
                        hm.save_to_file();
                        break;
                    case 8:
                        hm.load_from_file();
                        break;
                    case 9:
                        Console::print_colored("Logging out from Admin account.", Console::RED, Console::BG_BLACK);
                        goto login_menu_end;
                    default:
                        Console::print_colored("Invalid option. Please try again.", Console::RED, Console::BG_BLACK);
                    }
                }
            }
            else {
                Console::print_colored("Invalid Admin credentials.", Console::RED, Console::BG_BLACK);
            }
            break;
        }
        case 2: {
            Doctor* doctor = hm.doctor_login();
            if (doctor) {
                while (true) {
                    doctor_menu();
                    int doctor_choice;
                    cin >> doctor_choice;
                    cin.ignore();
                    switch (doctor_choice) {
                    case 1:
                        doctor->display();
                        break;
                    case 2: {
                        vector<Appointment> docs_appts = hm.get_appointments_for_doctor(doctor);
                        if (docs_appts.empty()) {
                            Console::print_colored("No appointments found.", Console::RED, Console::BG_BLACK);
                        }
                        else {
                            for (const auto& appt : docs_appts) {
                                appt.display();
                            }
                        }
                        break;
                    }
                    case 3:
                        Console::print_colored("Logging out from Doctor account.", Console::RED, Console::BG_BLACK);
                        goto login_menu_end;
                    default:
                        Console::print_colored("Invalid option. Please try again.", Console::RED, Console::BG_BLACK);
                    }
                }
            }
            else {
                Console::print_colored("Invalid Doctor credentials.", Console::RED, Console::BG_BLACK);
            }
            break;
        }
        case 3: {
            Patient* patient = hm.patient_login();
            if (patient) {
                while (true) {
                    patient_menu();
                    int patient_choice;
                    cin >> patient_choice;
                    cin.ignore();
                    switch (patient_choice) {
                    case 1:
                        patient->display();
                        break;
                    case 2: {
                        vector<Appointment> pats_appts = hm.get_appointments_for_patient(patient);
                        if (pats_appts.empty()) {
                            Console::print_colored("No appointments found.", Console::RED, Console::BG_BLACK);
                        }
                        else {
                            for (const auto& appt : pats_appts) {
                                appt.display();
                            }
                        }
                        break;
                    }
                    case 3:
                        Console::print_colored("Logging out from Patient account.", Console::RED, Console::BG_BLACK);
                        goto login_menu_end;
                    default:
                        Console::print_colored("Invalid option. Please try again.", Console::RED, Console::BG_BLACK);
                    }
                }
            }
            else {
                Console::print_colored("Invalid Patient credentials.", Console::RED, Console::BG_BLACK);
            }
            break;
        }
        case 4:
            Console::print_colored("Exiting the program. Goodbye!", Console::RED, Console::BG_BLACK);
            return 0;
        default:
            Console::print_colored("Invalid option. Please try again.", Console::RED, Console::BG_BLACK);
        }
        continue;
    login_menu_end:;
    }
    return 0;
}
