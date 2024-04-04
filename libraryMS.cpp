#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib> 
using namespace std;

class LibraryManagementSystem {
private:
    string id, name, author, search;
    fstream file;

public:
    void addBook();
    void showAll();
    void extractBook();
    void deleteBook(); 
    void handleErrors();
    void menu();
    LibraryManagementSystem(); 
    ~LibraryManagementSystem(); 
};

LibraryManagementSystem::LibraryManagementSystem() {
    file.open("bookData.txt", ios::in | ios::out | ios::app);
    if (!file) {
        cerr << "Error: Unable to open the file." << endl;
        exit(EXIT_FAILURE);
    }
}

LibraryManagementSystem::~LibraryManagementSystem() {
    file.close();
}

void LibraryManagementSystem::addBook() {
    cout << "\nEnter Book ID :: ";
    getline(cin, id);
    cout << "Enter Book Name :: ";
    getline(cin, name);
    cout << "Enter Book's Author name :: ";
    getline(cin, author);

    file << id << "*" << name << "*" << author << endl;
    cout << "Book added successfully." << endl;
}

void LibraryManagementSystem::showAll() {
    file.clear(); 
    file.seekg(0, ios::beg); 

    cout << "\n\n";
    cout << "\t\t Book Id \t\t\t Book Name \t\t\t Author's Name" << endl;
    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');
        cout << "\t\t " << id << " \t\t\t\t " << name << " \t\t\t " << author << endl;
    }
}

void LibraryManagementSystem::extractBook() {
    showAll();
    cout << "Enter Book Id :: ";
    getline(cin, search);

    file.clear();
    file.seekg(0, ios::beg);

    bool found = false;
    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');
        if (search == id) {
            cout << "\t\t " << id << " \t\t\t " << name << " \t\t\t " << author << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Book not found." << endl;
}

void LibraryManagementSystem::deleteBook() {
    string tempFileName = "tempBookData.txt";
    fstream tempFile(tempFileName, ios::out | ios::app);

    cout << "Enter Book ID to delete: ";
    string idToDelete;
    cin >> idToDelete;

    bool found = false;
    file.clear();
    file.seekg(0, ios::beg);
    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');
        if (idToDelete == id) {
            cout << "Book with ID " << id << " has been deleted." << endl;
            found = true;
        } else {
            tempFile << id << "*" << name << "*" << author << endl;
        }
    }

    if (!found) {
        cout << "Book with ID " << idToDelete << " not found." << endl;
    }

    file.close();
    tempFile.close();
    remove("bookData.txt");
    rename(tempFileName.c_str(), "bookData.txt");
}

void LibraryManagementSystem::menu() {
    char choice;
    do {
        cout << "----------------------------------" << endl;
        cout << "1-Show All Books" << endl;
        cout << "2-Extract Book" << endl;
        cout << "3-Add books(ADMIN)" << endl;
        cout << "5-Exit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Enter Your Choice :: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case '1':
                showAll();
                break;
            case '2':
                extractBook();
                break;
            case '3':
                addBook();
                break;
            case '4':
                deleteBook(); 
                break;
            case '5':
                exit(EXIT_SUCCESS);
                break;
            default:
                cout << "Invalid Choice...!" << endl;
        }
    } while (true);
}

int main() {
    LibraryManagementSystem obj;
    obj.menu();
    return 0;
}