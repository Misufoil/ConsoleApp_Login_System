#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Human {
public:
    Human() {
    };
    Human(string login, string password, string first_Name, string last_Name, int age);

    string getLogin() {
        return login;
    }
    string getPasword() {
        return password;
    }

    void information_print();

private:
    string login;
    string password;
    string first_Name;
    string last_Name;
    int age = 0;
};

Human::Human(string login, string password, string first_Name, string last_Name, int age) {
    this->login = login;
    this->password = password;
    this->first_Name = first_Name;
    this->last_Name = last_Name;
    this->age = age;
}

void Human::information_print() {
    cout << "Login: " << login << endl;
    cout << "Pasword: " << password << endl;
    cout << "First name: " << first_Name << endl;
    cout << "Last name: " << last_Name << endl;
    cout << "Age: " << age << endl;
}

template<typename T>
T InputError(T number) {
    while (!(cin >> number) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Input error! Retry input: ";
    }
    return number;
}


void IsLoggedIn() {

    string login, password, lg, pw;

    cout << "\nEnter login: ";  cin >> login;
    cout << "Enter password: "; cin >> password;

    ifstream fin;
    fin.open(login + ".txt");
    try {
        if (!fin.is_open()) {
            throw "Incorrect login or password.";
        }
    }
    catch (const char *ex) {
        cout << ex << endl;
    }
    

    Human prsn;
    fin.read((char*)&prsn, sizeof(Human));

    lg = prsn.getLogin();
    pw = prsn.getPasword();

    if (lg == login && pw == password) {
        cout << "Succesfully logged in!" << endl;
        cout << "\n\t\tACCAUNT DETAILS\n";
        prsn.information_print();
    }
    fin.close();
}

int main() {
    bool choice = 0;

    cout << "0: Register\n1: Login\nYour choice: ";
    choice = InputError(choice);

    if (choice == 0) {

        string login, pasword, first_Name, last_Name, path;
        int age;

        while (true) {
            cout << "\nCreate a login: "; cin >> login;

            path = login + ".txt";

            ifstream my_file(path);
            if (my_file) {
                cout << "This login already exists!" << endl;
            }
            else {
                break;
            }
        }

        cout << "Create a pasword: "; cin >> pasword;
        cout << "Enter first name: "; cin >> first_Name;
        cout << "Enter last name: "; cin >> last_Name;
        cout << "Enter age: "; cin >> age;
        cout << endl;

        Human person(login, pasword, first_Name, last_Name, age);

        ofstream file;
        file.open(path);
        file.write((char*)&person, sizeof(Human));
        file.close();

        cout << "///////////////////////////////////////////////////" << endl;
        cout << "Registration completed successfully !" << endl;
        cout << "///////////////////////////////////////////////////" << endl << endl;

        main();
    }
    else if (choice == 1) {
        try {
            IsLoggedIn();
        }
        catch (...) {
            cout << "Incorrect login or password." << endl;
        }
    }
}