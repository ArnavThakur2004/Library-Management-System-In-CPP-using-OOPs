#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip> // for setw()

using namespace std;

class LibrarySystem {
private:
    string bookID;
    string bookName;
    string authorName;
    int price;
    string studentID;
    int pages;

public:
    // Constructor
    LibrarySystem() {}

    // Get information about the book and student
    void getInfo() {
        cout << "Enter the Book ID (13 characters): ";
        cin >> setw(13) >> bookID;
        cout << "Enter the Book Name: ";
        cin.ignore(); // Clear newline character left in the buffer
        getline(cin, bookName);
        cout << "Enter the Author Name: ";
        getline(cin, authorName);
        cout << "Enter the Number of Pages: ";
        cin >> pages;
        cout << "Enter the Price of the Book: ";
        cin >> price;
        cout << "Enter your Student ID: ";
        cin >> studentID;
    }

    // Check if a given ID already exists in the file
    bool idExists(const string& searchID) {
        ifstream fin("C:\\Users\\arnav\\Desktop\\library_data.txt");
        if (!fin.is_open()) {
            cerr << "Error: Unable to open file for reading!" << endl;
            return false;
        }

        string tempID;
        string line;
        while (getline(fin, line)) {
            istringstream iss(line);
            iss >> tempID;
            if (tempID == searchID) {
                fin.close();
                return true;
            }
        }

        fin.close();
        return false;
    }

    // Write book information to file
    void writeToFile() {
        ofstream fout("C:\\Users\\arnav\\Desktop\\library_data.txt", ios::app); // Open file in append mode
        if (!fout.is_open()) {
            cerr << "Error: Unable to open file for writing!" << endl;
            return;
        }

        fout << setw(13) << bookID << "\t" << bookName << "\t" << authorName << "\t" << pages << "\t" << price << "\t" << studentID << endl;
        fout.close();
    }

    // Delete data from the file based on book ID
    void deleteFromFile(const string& searchID) {
        ifstream fin("C:\\Users\\arnav\\Desktop\\library_data.txt");
        ofstream fout("temp.txt");

        if (!fin.is_open() || !fout.is_open()) {
            cerr << "Error: Unable to open file for reading or writing!" << endl;
            return;
        }

        string line;
        while (getline(fin, line)) {
            istringstream iss(line);
            string tempID;
            iss >> tempID;
            if (tempID != searchID) {
                fout << line << endl;
            }
        }

        fin.close();
        fout.close();

        // Remove the original file
        remove("C:\\Users\\arnav\\Desktop\\library_data.txt");
        // Rename temp file to original file
        rename("temp.txt", "C:\\Users\\arnav\\Desktop\\library_data.txt");
    }
};

int main() {
    LibrarySystem lib;
    int option;

    do {
        cout << "\n1. Enter the Book details" << endl;
        cout << "2. Show all the data saved in the file" << endl;
        cout << "3. Delete data from the file" << endl;
        cout << "4. Stop" << endl;
        cout << "Enter your option: ";
        cin >> option;

        switch(option) {
            case 1: {
                string bookID;
                cout << "Enter the Book ID (13 characters): ";
                cin >> setw(13) >> bookID;

                if (bookID.length() != 13) {
                    cout << "Book ID must be exactly 13 characters long." << endl;
                    break;
                }

                if (lib.idExists(bookID)) {
                    cout << "Book with ID " << bookID << " already exists. Please enter a different ID." << endl;
                    break;
                }

                lib.getInfo();
                lib.writeToFile();
                cout << "Book details saved successfully!" << endl;
                break;
            }
            case 2: {
                ifstream fin("C:\\Users\\arnav\\Desktop\\library_data.txt");
                if (!fin.is_open()) {
                    cerr << "Error: Unable to open file for reading!" << endl;
                    break;
                }

                string line;
                while (getline(fin, line)) {
                    cout << line << endl;
                }

                fin.close();
                break;
            }
            case 3: {
                string bookID;
                cout << "Enter the Book ID to delete: ";
                cin >> setw(13) >> bookID;

                if (!lib.idExists(bookID)) {
                    cout << "Book with ID " << bookID << " does not exist." << endl;
                    break;
                }

                lib.deleteFromFile(bookID);
                cout << "Book with ID " << bookID << " deleted successfully!" << endl;
                break;
            }
            case 4: {
                cout << "Exiting program..." << endl;
                break;
            }
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 4);

    return 0;
}
