#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

struct Contact {
    char firstName[11];
    char lastName[21];
    char phoneNumber[13];
};

const int MAX_ENTRIES = 20;
vector<Contact> phonebook;

bool isUniquePhoneNumber(const string& phoneNumber) {
    for (const auto& contact : phonebook) {
        if (phoneNumber == contact.phoneNumber) {
            return false;
        }
    }
    return true;
}

// Додати запис
void addContact() {


    Contact newContact;
    cout << "Name: ";
    cin >> setw(11) >> newContact.firstName;
    cout << "Surname: ";
    cin >> setw(21) >> newContact.lastName;
    cout << "Number: ";
    cin >> setw(13) >> newContact.phoneNumber;

    if (isUniquePhoneNumber(newContact.phoneNumber)) {
        phonebook.push_back(newContact);
        cout << "succesfully added.\n";
    }
    else {
        cout << "this number is there.\n";
    }
}

void deleteContact() {
    string phoneNumber;
    cout << "number for delete: ";
    cin >> phoneNumber;

    for (auto it = phonebook.begin(); it != phonebook.end(); ++it) {
        if (phoneNumber == it->phoneNumber) {
            phonebook.erase(it);
            cout << "succesfully added.\n";
            return;
        }
    }
    cout << "with this number did not find anything.\n";
}


void findContact() {
    string lastName;
    cout << "write surname: ";
    cin >> lastName;

    bool found = false;
    for (const auto& contact : phonebook) {
        if (lastName == contact.lastName) {
            cout << "Name: " << contact.firstName << ", Surname: " << contact.lastName
                << ", Number: " << contact.phoneNumber << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "did not find with this surname.\n";
    }
}

void showAllContacts() {
    if (phonebook.empty()) {
        cout << "ist leer.\n";
        return;
    }

    for (const auto& contact : phonebook) {
        cout << "Name: " << contact.firstName << ", Suename: " << contact.lastName
            << ", Number: " << contact.phoneNumber << endl;
    }
}

void saveToFile() {
    ofstream outFile("phone.dat", ios::binary);
    if (outFile) {
        for (const auto& contact : phonebook) {
            outFile.write(reinterpret_cast<const char*>(&contact), sizeof(Contact));
        }
        cout << "Succesfully added to the file.\n";
    }
    else {
        cout << "Fale.\n";
    }
    outFile.close();
}

void loadFromFile() {
    ifstream inFile("phone.dat", ios::binary);
    if (inFile) {
        phonebook.clear();
        Contact contact;
        while (inFile.read(reinterpret_cast<char*>(&contact), sizeof(Contact))) {
            phonebook.push_back(contact);
        }
        cout << "succesfully loaded from file.\n";
    }
    else {
        cout << "fale from file.\n";
    }
    inFile.close();
}

void displayMenu() {
    cout << "\ntelephone list:\n";
    cout << "1. add digit\n";
    cout << "2. delete digit\n";
    cout << "3. find digit\n";
    cout << "4. show all digits\n";
    cout << "5. save wrote digits\n";
    cout << "6. download\n";
    cout << "7. exit\n";
    cout << "choose options: ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            addContact();
            break;
        case 2:
            deleteContact();
            break;
        case 3:
            findContact();
            break;
        case 4:
            showAllContacts();
            break;
        case 5:
            saveToFile();
            break;
        case 6:
            loadFromFile();
            break;
        case 7:
            cout << "exit.\n";
            break;
        default:
            cout << "wrong. try again.\n";
        }

        if (choice != 7) {
            cout << "\npush enter to continue...\n";
            cin.ignore();
        }

    } while (choice != 7);

    return 0;
}
