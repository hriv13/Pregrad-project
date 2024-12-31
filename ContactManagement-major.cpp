#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define MAX 1000 // Maximum number of contacts initially

// Class to represent a Contact
class Contact {
public:
    string name;
    string phone;
    string email;

    void setData() {
        cout << "Enter Name: ";
        cin >> ws; //skips spaces, tabs and newlines
        getline(cin, name);
        cout << "Enter Phone: ";
        cin >> phone;
        cout << "Enter Email: ";
        cin >> email;
    }

    void displayData() const {
        cout << "Name: " << name << "\nPhone: " << phone << "\nEmail: " << email << endl;
    }
};

// Class to manage the Contact List
class ContactList {
private:
    Contact* contacts;  // Dynamic array of contacts
    int size;           // Current number of contacts
    int capacity;       // Maximum capacity of the array

    // Function to resize the array dynamically when needed
    void resizeArray() {
        capacity *= 2;  // Double the capacity
        Contact* newContacts = new Contact[capacity];

        // Copy old contacts to the new array
        for (int i = 0; i < size; i++) {
            newContacts[i] = contacts[i];
        }

        // Delete the old array
        delete[] contacts;
        contacts = newContacts;
    }

public:
    // Constructor to initialize the contact list
    ContactList(int initialCapacity = MAX) {
        size = 0;
        capacity = initialCapacity;
        contacts = new Contact[capacity];
    }

    // Destructor to clear dynamically allocated memory
    ~ContactList() {
        delete[] contacts;
    }

    // Function to add a new contact
    void addContact(Contact contact) {
        if (size == capacity) {
            resizeArray();  // Resize array if it's full
        }
        contacts[size] = contact;
        size++;
        cout << "Contact added successfully." << endl;
    }

    // Function to display all contacts
    void displayAllContacts() const {
        if (size == 0) {
            cout << "No contacts found." << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << "Contact " << i + 1 << ":" << endl;
            contacts[i].displayData();
            cout << "----------------------" << endl;
        }
    }

    // Function to search for a contact by name
    void searchContactByName(const string &name) const {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (contacts[i].name == name) {
                contacts[i].displayData();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

    // Function to delete a contact by name
    void deleteContact(const string &name) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (contacts[i].name == name) {
                for (int j = i; j < size - 1; j++) {
                    contacts[j] = contacts[j + 1];  // Shift elements to the left
                }
                size--;
                found = true;
                cout << "Contact deleted successfully." << endl;
                break;
            }
        }
        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

    // Function to modify a contact by name
    void modifyContact(const string &name) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (contacts[i].name == name) {
                cout << "Enter new details for the contact:" << endl;
                contacts[i].setData();
                found = true;
                cout << "Contact modified successfully." << endl;
                break;
            }
        }
        if (!found) {
            cout << "Contact not found." << endl;
        }
    }

    // Function to save contacts to a file
    void saveToFile(const string &filename) const {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing." << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            file << contacts[i].name << "\n"
                 << contacts[i].phone << "\n"
                 << contacts[i].email << "\n";
        }
        file.close();
        cout << "Contacts saved to file successfully." << endl;
    }

    // Function to load contacts from a file
    void loadFromFile(const string &filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file for reading." << endl;
            return;
        }
        size = 0;  // Reset the contact list
        Contact contact;
        string name, phone, email;

        while (getline(file, name) && getline(file, phone) && getline(file, email)) {
            contact.name = name;
            contact.phone = phone;
            contact.email = email;
            addContact(contact);
        }

        file.close();
        cout << "Contacts loaded from file successfully." << endl;
    }
};

//Menu function
void menu() {
    cout << "\n--- Contact Management System ---" << endl;
    cout << "1. Add Contact" << endl;
    cout << "2. Display All Contacts" << endl;
    cout << "3. Search Contact by Name" << endl;
    cout << "4. Delete Contact" << endl;
    cout << "5. Modify Contact" << endl;
    cout << "6. Save to File" << endl;
    cout << "7. Load from File" << endl;
    cout << "8. Exit" << endl;
}

int main() {
    ContactList list;
    int choice;
    string name;
    Contact contact;
    menu();

    do {
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            contact.setData();
            list.addContact(contact);
            break;
        case 2:
            list.displayAllContacts();
            break;
        case 3:
            cout << "Enter name to search: ";
            cin >> ws;
            getline(cin, name);
            list.searchContactByName(name);
            break;
        case 4:
            cout << "Enter name to delete: ";
            cin >> ws;
            getline(cin, name);
            list.deleteContact(name);
            break;
        case 5:
            cout << "Enter name to modify: ";
            cin >> ws;
            getline(cin, name);
            list.modifyContact(name);
            break;
        case 6:
            list.saveToFile("contacts.txt");
            break;
        case 7:
            list.loadFromFile("contacts.txt");
            break;
        case 8:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);
    return 0;
}