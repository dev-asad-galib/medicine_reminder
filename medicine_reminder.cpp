#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

// ========================== Structures ==========================
struct UserInfo {
    string name;
    int age;
    string gender;
    string phoneNumber;
};

struct Medicine {
    string name;
};

struct MedicineSchedule {
    string medicineName;
    string time;
};

// ========================== Functions ==========================

// Register user information
UserInfo registerUser() {
    UserInfo user;
    cout << "===== User Registration =====\n";

    cout << "Enter your name: ";
    getline(cin, user.name);

    cout << "Enter your age: ";
    cin >> user.age;
    cin.ignore(); // clear buffer

    cout << "Enter your gender (Male/Female/Other): ";
    getline(cin, user.gender);

    cout << "Enter your phone number: ";
    getline(cin, user.phoneNumber);

    cout << "\nUser Info Registered Successfully!\n";
    cout << "Name: " << user.name << endl;
    cout << "Age: " << user.age << endl;
    cout << "Gender: " << user.gender << endl;
    cout << "Phone: " << user.phoneNumber << endl;

    return user;
}

// Load default medicines
vector<Medicine> loadMedicineLibrary() {
    vector<Medicine> library;
    library.push_back({"Nafa A"});
    library.push_back({"Nafa B"});
    library.push_back({"Nafa C"});
    library.push_back({"Nafa D"});
    return library;
}

// View medicines
void viewMedicines(const vector<Medicine>& library) {
    cout << "\n===== Medicine Library =====\n";
    if (library.empty()) {
        cout << "No medicines in the library.\n";
        return;
    }
    for (int i = 0; i < library.size(); i++) {
        cout << i << ". " << library[i].name << endl;
    }
}

// Add medicine
void addMedicine(vector<Medicine>& library) {
    string medName;
    cout << "Enter new medicine name: ";
    getline(cin, medName);
    library.push_back({medName});
    cout << medName << " added to the library.\n";
}

// Search medicine
void searchMedicine(const vector<Medicine>& library) {
    string searchName;
    cout << "Enter medicine name to search: ";
    getline(cin, searchName);

    bool found = false;
    for (auto& med : library) {
        if (med.name == searchName) {
            cout << searchName << " found in the library.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << searchName << " not found.\n";
}

// Delete medicine
void deleteMedicine(vector<Medicine>& library) {
    string delName;
    cout << "Enter medicine name to delete: ";
    getline(cin, delName);

    for (auto it = library.begin(); it != library.end(); ++it) {
        if (it->name == delName) {
            cout << delName << " deleted from library.\n";
            library.erase(it);
            return;
        }
    }
    cout << delName << " not found.\n";
}

// Medicine library menu
void medicineLibraryMenu(vector<Medicine>& library) {
    int choice;
    do {
        cout << "\n===== Medicine Library Menu =====\n";
        cout << "1. View Medicines\n";
        cout << "2. Add Medicine\n";
        cout << "3. Search Medicine\n";
        cout << "4. Delete Medicine\n";
        cout << "0. Exit Library Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: viewMedicines(library); break;
            case 2: addMedicine(library); break;
            case 3: searchMedicine(library); break;
            case 4: deleteMedicine(library); break;
            case 0: cout << "Exiting Library Menu...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

// Set medicine schedule
vector<MedicineSchedule> setMedicineSchedule(const vector<Medicine>& library) {
    vector<MedicineSchedule> schedule;
    int count;
    cout << "\nHow many medicines do you want to schedule? ";
    cin >> count;
    cin.ignore();

    for (int i = 0; i < count; i++) {
        MedicineSchedule ms;
        cout << "\nSelect medicine index (0-" << library.size() - 1 << "): ";
        int idx;
        cin >> idx;
        cin.ignore();

        if (idx >= 0 && idx < library.size()) {
            ms.medicineName = library[idx].name;
        } else {
            cout << "Invalid index, defaulting to Nafa A.\n";
            ms.medicineName = library[0].name;
        }

        cout << "Enter time for " << ms.medicineName << " (HH:MM, 24hr format): ";
        getline(cin, ms.time);

        schedule.push_back(ms);
    }

    return schedule;
}

// Trigger notification (simulate with sound/text)
void triggerNotification(const vector<MedicineSchedule>& schedule) {
    cout << "\n===== Triggering Notifications =====\n";
    for (auto& ms : schedule) {
        cout << "Reminder: Take " << ms.medicineName
             << " at " << ms.time << " ⏰" << endl;

        // Simulated sound
        cout << "[Playing notification sound...]\n";
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// ========================== Main ==========================
int main() {
    cout << "===== Medicine Management System =====\n";

    // Register User
    UserInfo user = registerUser();

    // Load Medicine Library
    vector<Medicine> medicineLibrary = loadMedicineLibrary();

    // Library Menu
    medicineLibraryMenu(medicineLibrary);

    // Set Schedule
    vector<MedicineSchedule> schedule = setMedicineSchedule(medicineLibrary);

    // Trigger Notifications
    triggerNotification(schedule);

    cout << "\n===== Program Ended =====\n";
    return 0;
}
