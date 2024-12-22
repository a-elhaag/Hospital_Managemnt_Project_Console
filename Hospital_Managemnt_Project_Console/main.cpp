#include <iostream>
#include <limits>
#include "HospitalManagement.h"
#include "ConsoleColors.h"


#include <windows.h>

using namespace std;

void adminMenu(HospitalManagement& hm);
void doctorMenu(HospitalManagement& hm, Doctor* doctor);
void patientMenu(HospitalManagement& hm, Patient* patient);
void clearInputBuffer();

int main() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    HospitalManagement hm;
    int roleChoice;

    while (true) {
        Console::print_colored("\n=== Hospital Management System ===", Console::CYAN);
        Console::print_colored("1. Admin Login", Console::YELLOW);
        Console::print_colored("2. Doctor Login", Console::BLUE);
        Console::print_colored("3. Patient Login", Console::GREEN);
        Console::print_colored("4. Exit", Console::RED);
        Console::print_colored("Choose a role (1-4): ", Console::WHITE);

        cin >> roleChoice;
        clearInputBuffer();

        switch (roleChoice) {
        case 1: { // Admin
            if (hm.admin_login()) {
                Console::print_colored("Welcome, Admin!", Console::GREEN);
                adminMenu(hm);
            }
            else {
                Console::print_colored("Invalid Admin credentials.", Console::RED);
            }
            break;
        }
        case 2: { // Doctor
            Doctor* doctor = hm.doctor_login();
            if (doctor) {
                doctorMenu(hm, doctor);
            }
            break;
        }
        case 3: { // Patient
            Patient* patient = hm.patient_login();
            if (patient) {
                patientMenu(hm, patient);
            }
            break;
        }
        case 4: { // Exit
            Console::print_colored("Exiting the system. Goodbye!", Console::MAGENTA);
            return 0;
        }
        default:
            Console::print_colored("Invalid choice. Please select between 1 and 4.", Console::RED);
        }
    }

    return 0;
}

// Function to clear the input buffer
void clearInputBuffer() {
    char c;
    while ((c = cin.get()) != '\n' && c != EOF);
}

// Admin Menu Function
void adminMenu(HospitalManagement& hm) {
    int adminChoice;
    while (true) {
        Console::print_colored("\n--- Admin Menu ---", Console::YELLOW);
        Console::print_colored("1. Add a New Doctor", Console::BLUE);
        Console::print_colored("2. Add a New Patient", Console::GREEN);
        Console::print_colored("3. List All Doctors", Console::BLUE);
        Console::print_colored("4. List All Patients", Console::GREEN);
        Console::print_colored("5. Create an Appointment", Console::CYAN);
        Console::print_colored("6. Edit an Appointment", Console::CYAN);
        Console::print_colored("7. Delete an Appointment", Console::CYAN);
        Console::print_colored("8. Save Data", Console::MAGENTA);
        Console::print_colored("9. Load Data", Console::MAGENTA);
        Console::print_colored("10. Logout", Console::RED);
        Console::print_colored("Choose an option (1-10): ", Console::WHITE);

        cin >> adminChoice;
        clearInputBuffer();

        switch (adminChoice) {
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
        case 5:
            hm.create_appointment();
            break;
        case 6:
            hm.edit_appointment();
            break;
        case 7:
            hm.delete_appointment();
            break;
        case 8:
            hm.save_to_file();
            break;
        case 9:
            hm.load_from_file();
            break;
        case 10:
            Console::print_colored("Logging out from Admin account.", Console::RED);
            return;
        default:
            Console::print_colored("Invalid option. Please select between 1 and 10.", Console::RED);
        }
    }
}

// Doctor Menu Function
void doctorMenu(HospitalManagement& hm, Doctor* doctor) {
    int doctorChoice;
    while (true) {
        Console::print_colored("\n--- Doctor Menu ---", Console::BLUE);
        Console::print_colored("1. View My Details", Console::BLUE);
        Console::print_colored("2. View My Appointments", Console::CYAN);
        Console::print_colored("3. Logout", Console::RED);
        Console::print_colored("Choose an option (1-3): ", Console::WHITE);

        cin >> doctorChoice;
        clearInputBuffer();

        switch (doctorChoice) {
        case 1:
            doctor->display();
            break;
        case 2: {
            vector<Appointment> myAppointments = hm.get_appointments_for_doctor(doctor);
            if (myAppointments.empty()) {
                Console::print_colored("No appointments found.", Console::RED);
            }
            else {
                for (const auto& appt : myAppointments) {
                    appt.display();
                }
            }
            break;
        }
        case 3:
            Console::print_colored("Logging out from Doctor account.", Console::RED);
            return;
        default:
            Console::print_colored("Invalid option. Please select between 1 and 3.", Console::RED);
        }
    }
}

// Patient Menu Function
void patientMenu(HospitalManagement& hm, Patient* patient) {
    int patientChoice;
    while (true) {
        Console::print_colored("\n--- Patient Menu ---", Console::GREEN);
        Console::print_colored("1. View My Details", Console::GREEN);
        Console::print_colored("2. View My Appointments", Console::CYAN);
        Console::print_colored("3. Logout", Console::RED);
        Console::print_colored("Choose an option (1-3): ", Console::WHITE);

        cin >> patientChoice;
        clearInputBuffer();

        switch (patientChoice) {
        case 1:
            patient->display();
            break;
        case 2: {
            vector<Appointment> myAppointments = hm.get_appointments_for_patient(patient);
            if (myAppointments.empty()) {
                Console::print_colored("No appointments found.", Console::RED);
            }
            else {
                for (const auto& appt : myAppointments) {
                    appt.display();
                }
            }
            break;
        }
        case 3:
            Console::print_colored("Logging out from Patient account.", Console::RED);
            return;
        default:
            Console::print_colored("Invalid option. Please select between 1 and 3.", Console::RED);
        }
    }
}
