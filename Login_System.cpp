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

void IsLoggedIn() {

    string login, password, lg, pw;

    cout << "\nEnter login: ";  cin >> login;
    cout << "Enter password: "; cin >> password;

    ifstream fin;
    fin.open(login + ".txt");
    if (!fin.is_open()) {
        throw exception("Incorrect login or password.");    
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
    else {
        fin.close();
        throw "Incorrect login or password";
    }
    //fin.close();
}

int main() {
    int choice;

    cout << "1: Register\n2: Login\nYour choice: "; cin >> choice;

    if (choice == 1) {

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
    else if (choice == 2) {
        try {
            IsLoggedIn();
        }
       // catch (exception &ex) {
        //    cout << endl << ex.what() << endl << endl;
       //     main();
        //}
        //catch (const char *ex) {
         //   cout << endl << ex << endl << endl;
        //    main();
        //}
        catch (...)  {
            cout << endl << "Incorrect login or password." << endl << endl;
           // main();
        }
    }
}