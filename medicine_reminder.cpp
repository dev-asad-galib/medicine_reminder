#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> // For system()

using namespace std;

// Struct for Medicine
struct Medicine {
    string name;
    int amount;
    string time;
};

// User Info
struct User {
    string name;
    int age;
};

// Globals
vector<Medicine> medicineLibrary = {
    {"Nafa_A", 0, ""},
    {"Nafa_B", 0, ""},
    {"Nafa_C", 0, ""},
    {"Nafa_D", 0, ""}
};
User currentUser;

// Function Prototypes
void userRegistration();
void viewMedicineLibrary();
void addMedicine();
int searchMedicine(string name);
void setMedicineSchedule();
void triggerNotification(const Medicine &med);
void recordHistory(const Medicine &med);
void saveMedicineData();
void loadMedicineData();

int main() {
    loadMedicineData();
    cout << "Medicine Reminder & Assistant System\n";
    userRegistration();

    char choice;
    do {
        cout << "\n1. View Medicine Library\n2. Add New Medicine\n3. Search Medicine\n4. Set Medicine Schedule\n5. Save Data & Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                viewMedicineLibrary();
                break;
            case '2':
                addMedicine();
                break;
            case '3': {
                cout << "Enter medicine name to search: ";
                string name;
                cin >> name;
                int idx = searchMedicine(name);
                if (idx != -1) {
                    cout << "Medicine found: " << medicineLibrary[idx].name << endl;
                } else {
                    cout << "Medicine not found.\n";
                }
                break;
            }
            case '4':
                setMedicineSchedule();
                break;
            case '5':
                saveMedicineData();
                cout << "Data saved. Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != '5');

    return 0;
}

void userRegistration() {
    cout << "Enter your name: ";
    cin >> currentUser.name;
    cout << "Enter your age: ";
    cin >> currentUser.age;
}

void viewMedicineLibrary() {
    cout << "=== Medicine Library ===\n";
    for (const auto& med : medicineLibrary) {
        cout << "Name: " << med.name << ", Amount: " << med.amount << ", Time: " << med.time << endl;
    }
}

void addMedicine() {
    Medicine med;
    cout << "Enter medicine name: ";
    cin >> med.name;
    cout << "Enter amount: ";
    cin >> med.amount;
    cout << "Enter taking time (e.g. 8AM): ";
    cin >> med.time;
    medicineLibrary.push_back(med);
}

int searchMedicine(string name) {
    for (size_t i = 0; i < medicineLibrary.size(); i++) {
        if (medicineLibrary[i].name == name)
            return i;
    }
    return -1;
}

void setMedicineSchedule() {
    string name;
    cout << "Enter medicine name to schedule: ";
    cin >> name;
    int idx = searchMedicine(name);
    if (idx != -1) {
        cout << "Set time for taking " << medicineLibrary[idx].name << " (24-hour format, e.g., 14:00): ";
        cin >> medicineLibrary[idx].time;
        cout << "Time set to " << medicineLibrary[idx].time << " for " << medicineLibrary[idx].name << endl;
        triggerNotification(medicineLibrary[idx]);
    } else {
        cout << "Medicine not found.\n";
    }
}

void triggerNotification(const Medicine &med) {
    cout << "\n--- Reminder ---\n";
    cout << "Time to take: " << med.name << " Amount: " << med.amount << " at " << med.time << endl;

    // Play sound notification
    system("start ringtone-126505.mp3"); // Windows-specific command

    string confirm;
    cout << "Have you taken the medicine? (yes/no): ";
    cin >> confirm;

    if (confirm == "yes") {
        recordHistory(med);
    } else {
        cout << "Reminder will repeat later.\n";
    }
}

void recordHistory(const Medicine &med) {
    cout << "Recording that you took " << med.name << endl;
}

void saveMedicineData() {
    ofstream file("medicines.txt");
    for (const auto& med : medicineLibrary) {
        file << med.name << " " << med.amount << " " << med.time << endl;
    }
    file.close();
}

void loadMedicineData() {
    ifstream file("medicines.txt");
    Medicine med;
    while (file >> med.name >> med.amount >> med.time) {
        medicineLibrary.push_back(med);
    }
    file.close();
}
