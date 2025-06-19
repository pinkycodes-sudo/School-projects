#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

const int MAX_PATIENTS = 100;
string patientRecords[MAX_PATIENTS][12]; // ID, Name, Age, Cell, Address, Reason, KinName, KinCell, KinLoc, Email, Gender, Emergency
int patientCount = 0;
string comments[MAX_PATIENTS];
string patientIDs[MAX_PATIENTS];
string appointmentHistory[MAX_PATIENTS][3];

const int TOTAL_SLOTS = 5;
string appointmentSlots[TOTAL_SLOTS] =

{
    "2025-04-21 09:00 AM",
    "2025-04-21 10:00 AM",
    "2025-04-21 11:00 AM",
    "2025-04-21 01:00 PM",
    "2025-04-21 02:00 PM"
};
bool slotBooked[TOTAL_SLOTS] = { false };

void setColor(int color)

{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

bool loginSystem()
 {
    string username, password;
    int attempts = 0;
    do
        {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        if (username == "admin" && password == "pass123")
            return true;
        setColor(12);
        cout << "Incorrect. Try again." << endl;
        setColor(7);
        attempts++;
    }
    while (attempts < 3);
    return false;
}

void registerPatient()

{
    if (patientCount < MAX_PATIENTS)

        {
        cin.ignore();
        cout << "Enter Patient ID: ";
        getline(cin, patientRecords[patientCount][0]);
        cout << "Enter Name: ";
        getline(cin, patientRecords[patientCount][1]);
        cout << "Enter Age: ";
        getline(cin, patientRecords[patientCount][2]);
        cout << "Enter Patient Cell Number: ";
        getline(cin, patientRecords[patientCount][3]);
        cout << "Enter Home Address: ";
        getline(cin, patientRecords[patientCount][4]);
        cout << "What are you consulting for?: ";
        getline(cin, patientRecords[patientCount][5]);

        cout << "Next of Kin Name: ";
        getline(cin, patientRecords[patientCount][6]);
        cout << "Next of Kin Cell Number: ";
        getline(cin, patientRecords[patientCount][7]);
        cout << "Next of Kin Location: ";
        getline(cin, patientRecords[patientCount][8]);

        cout << "Enter Your Email Address: ";
        getline(cin, patientRecords[patientCount][9]);

        cout << "Select Gender:\n1. Male\n2. Female\n3. Other\nChoice: ";
        int genderChoice;
        cin >> genderChoice;
        cin.ignore();
        switch (genderChoice)

        {
            case 1: patientRecords[patientCount][10] = "Male"; break;
            case 2: patientRecords[patientCount][10] = "Female"; break;
            case 3: patientRecords[patientCount][10] = "Other"; break;
            default: patientRecords[patientCount][10] = "Unspecified"; break;
        }

        cout << "Is the next of kin your emergency contact? (yes/no): ";
        string response;
        getline(cin, response);
        patientRecords[patientCount][11] = (response == "yes" || response == "Yes") ? "Yes" : "No";

        patientCount++;
        setColor(10);
        cout << "Patient registered successfully." << endl;
        setColor(7);
    }

    else

    {
        setColor(12);
        cout << "Max patients reached." << endl;
        setColor(7);
    }
}

void bookAppointment()
{
    string id;
    cout << "Enter Patient ID for booking: ";
    cin >> id;
    cout << "\nAvailable Appointment Slots:\n";
    for (int i = 0; i < TOTAL_SLOTS; i++)

        {

        if (!slotBooked[i]) {
            cout << i + 1 << ". " << appointmentSlots[i] << endl;
        }
    }
    int choice;
    cout << "Select a slot number (1-" << TOTAL_SLOTS << "): ";
    cin >> choice;
    if (choice < 1 || choice > TOTAL_SLOTS)

        {
        cout << "Invalid slot number." << endl;
    }

    else if (slotBooked[choice - 1])

    {
        cout << "Slot already booked. Please choose another." << endl;
    }
    else

    {
        slotBooked[choice - 1] = true;
        for (int i = 0; i < patientCount; i++)
        {
            if (patientRecords[i][0] == id)
                {
                for (int j = 0; j < 3; j++)
                {
                    if (appointmentHistory[i][j].empty())

                        {
                        appointmentHistory[i][j] = appointmentSlots[choice - 1];
                        break;
                    }
                }
                break;
            }
        }
        setColor(10);
        cout << "Appointment booked for " << id << " at " << appointmentSlots[choice - 1] << endl;
        setColor(7);
    }
}

bool findAppointmentRecursive(int patientIndex, int slotIndex, const string& targetSlot)

{
    if (slotIndex >= 3) return false;
    if (appointmentHistory[patientIndex][slotIndex] == targetSlot) return true;
    return findAppointmentRecursive(patientIndex, slotIndex + 1, targetSlot);
}

void searchAppointmentBySlot()

{
    string id, slot;
    cout << "Enter Patient ID to search appointments: ";
    cin >> id;
    cin.ignore();
    cout << "Enter appointment slot (e.g., 2025-04-21 10:00 AM): ";
    getline(cin, slot);

    for (int i = 0; i < patientCount; i++)

    {
        if (patientRecords[i][0] == id)

            {
            bool found = findAppointmentRecursive(i, 0, slot);
            if (found)
                cout << "Appointment slot found for patient " << patientRecords[i][1] << endl;
            else
                cout << "Appointment slot NOT found for this patient." << endl;
            return;
        }
    }
    cout << "No patient found with ID: " << id << endl;
}

void addComment(string id)

{
    string comment;
    cout << "Enter comment: ";
    cin.ignore();
    getline(cin, comment);
    for (int i = 0; i < patientCount; i++)

     {
        if (patientRecords[i][0] == id)

            {
            comments[i] = comment;
            patientIDs[i] = id;
            break;
        }
    }
    cout << "Comment added successfully." << endl;
}

void searchComments(string id)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patientIDs[i] == id)

            {
            cout << "Comment found: " << comments[i] << endl;
            return;
        }
    }
    cout << "No comment found for ID: " << id << endl;
}

void displayAllPatients()
{
    for (int i = 0; i < patientCount; i++)
        {
        cout << "\n--- Patient " << i + 1 << " ---\n";
        cout << "Patient Information:" << endl;
        cout << "ID: " << patientRecords[i][0] << endl;
        cout << "Name: " << patientRecords[i][1] << endl;
        cout << "Age: " << patientRecords[i][2] << endl;
        cout << "Gender: " << patientRecords[i][10] << endl;
        cout << "Cell Number: " << patientRecords[i][3] << endl;
        cout << "Email: " << patientRecords[i][9] << endl;
        cout << "Address: " << patientRecords[i][4] << endl;
        cout << "Reason for Appointment: " << patientRecords[i][5] << endl;
        cout << "\nNext of Kin Information:" << endl;
        cout << "Name: " << patientRecords[i][6] << endl;
        cout << "Cell Number: " << patientRecords[i][7] << endl;
        cout << "Location: " << patientRecords[i][8] << endl;
        cout << "Emergency Contact: " << patientRecords[i][11] << endl;
        cout << "\nAppointment History:" << endl;
        for (int j = 0; j < 3; j++)
        {
            if (!appointmentHistory[i][j].empty())

                {
                cout << "- " << appointmentHistory[i][j] << endl;
            }
        }
        if (!comments[i].empty())

            {
            cout << "\nPatient Comment: " << comments[i] << endl;
        }
    }
}

void searchPatientByID()

{
    string id;
    cout << "Enter Patient ID to search: ";
    cin >> id;
    for (int i = 0; i < patientCount; i++)
    {
        if (patientRecords[i][0] == id)

            {
            cout << "\nPatient Found: " << patientRecords[i][1] << ", Age " << patientRecords[i][2] << endl;
            return;
        }
    }
    cout << "No patient found with ID: " << id << endl;
}

void processBilling()
{
    float consultationFee = 250.00;
    float medicine = 150.00;
    float total = consultationFee + medicine;
    cout << "Total bill: R" << total << endl;
}

void mainMenu()
{
    int choice;
    do
        {
        cout << "\n1. Register Patient\n2. Book Appointment\n3. Billing\n4. Add Comment\n5. Search Comment\n6. Display Patients\n7. Search Patient by ID\n8. Search Appointment by Slot\n9. Exit\nChoice: ";
        cin >> choice;
        switch (choice)
        {
            case 1: registerPatient(); break;
            case 2: bookAppointment(); break;
            case 3: processBilling(); break;
            case 4: {
                string id;
                cout << "Enter Patient ID: ";
                cin >> id;
                addComment(id);
                break;
            }
            case 5:

                {
                string id;
                cout << "Enter Patient ID to search comment: ";
                cin >> id;
                searchComments(id);
                break;
            }
            case 6: displayAllPatients(); break;
            case 7: searchPatientByID(); break;
            case 8: searchAppointmentBySlot(); break;
            case 9: cout << "Exiting..."; break;
            default: cout << "Invalid choice."; break;
        }
    } while (choice != 9);
}

int main()

{
    setColor(11);
    cout << "Welcome to the Hospital Appointment and Patient Management System" << endl;
    setColor(7);
    if (loginSystem())
        {
        mainMenu();
    }

    else

    {
        setColor(12);
        cout << "Too many failed login attempts. Exiting program." << endl;
        setColor(7);
}
    return 0;
}
