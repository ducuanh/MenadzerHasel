
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <time.h>
#include "password.h"

#include "category.h"

using namespace std;
/**
 * @brief Construct a new Password object
 *
 */
Password::Password()
{
    password = "";
    name = "";
    login = "";
    service = "";
    hasLogin = false;
    hasService = false;
}

/**
 * @brief Construct a new Password object
 *
 * @param name_ user defined name of this password
 * @param password_ acctual password user want to save
 */
Password::Password(string name_, string password_) {
    password = password_;
    name = name_;
}

/**
 * @brief add category to password object
 *
 * @param cat category name
 * @return true if category exists ad was added succesfuly
 * @return false if category of given name does not exists
 */
bool Password::addCategory(string cat)
{
    if (CategoryManager::checkIfCategoryExists(cat))
    {
        Category c = CategoryManager::getCategoryByName(cat);
        categories.push_back(c);
        return true;
    }

    cout << "Kategoria o takiej nazwie nie istnieje!" << endl;
    return false;
}

/**
 * @brief adds service parameter
 *
 * @param service_ service name
 */
void Password::addService(string service_)
{
    service = service_;
    hasService = true;
}

/**
 * @brief adds login parameter
 *
 * @param login_ login to service
 */
void Password::addLogin(string login_)
{
    login = login_;
    hasLogin = true;
}

/**
 * @brief deletes passwords login
 *
 */
void Password::deleteLogin()
{
    hasLogin = false;
    login = "";
}

/**
 * @brief returns if password has login value
 *
 * @return true if has login value
 * @return false if dont
 */
bool Password::hasLoginf()
{
    return hasLogin;
}
/**
 * @brief Get the Login attribue
 *
 * @return string passwords login
 */
string Password::getLogin() const
{
    return login;
}
/**
 * @brief returns if password has service value
 *
 * @return true if has service value
 * @return false if dont
 */
bool Password::hasServicef()
{
    return hasService;
}
/**
 * @brief Get the service attribue
 *
 * @return string passwords service
 */
string Password::getService() const
{
    return service;
}

/**
 * @brief deletes passwords service
 *
 */
void Password::deleteService() {
    hasService = false;
    service = "";
}

/**
 * @brief Get the name attribute
 *
 * @return string name attribute
 */
string Password::getName() const {
    return name;
}
/**
 * @brief Set the Name attribute
 *
 * @param name_ new name
 */
void Password::setName(string name_) {
    name = name_;
}
/**
 * @brief Set the password attribute
 *
 * @param name_ new password
 */
void Password::setPassword(string pass) {
    password = pass;
}
/**
 * @brief Get the password attribute
 *
 * @return string password attribute
 */
string Password::getPassword() const
{
    return password;
}

/**
 * @brief checks if password has specified category assigned
 *
 * @param name category name
 * @return true if has
 * @return false if dont
 */
bool Password::containCategory(string name) const {
    for (int i = 0; i < categories.size(); i++)
    {
        if (categories[i].getName() == name)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief removes category from password categories
 *
 * @param name category name
 */
void Password::removeCategory(string name) {
    vector<Category>::iterator new_end = remove_if(categories.begin(), categories.end(), [&](const Category &a)
    { return a.getName() == name; });

    categories.erase(new_end, categories.end());
}

/**
 * @brief Get the Categories as a human readeable string
 *
 * @return string human readable categories attribute
 */
string Password::getCategoriesHuman() const
{
    string result = "";
    for (int i = 0; i < categories.size(); i++)
    {
        result += categories[i].getName();
        result += ", ";
    }
    return result;
}
/**
 * @brief Get the Categories as a file writable string
 *
 * @return string file writable categories attribute
 */
string Password::getCategoriesFile()
{
    string result = "";
    for (int i = 0; i < categories.size(); i++)
    {
        result += categories[i].getName();
        if (i < categories.size() - 1)
        {
            result += ";";
        }
    }
    return result;
}





/**
 * @brief Get the index of password with specified name from passwords vector
 *
 * @param name password name
 * @return int passwords index
 */
int PasswordManager::getPasswordIndex(string name) {
    for (int i = 0; i < passwords.size(); i++)
    {
        if (passwords[i].getName() == name)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Create a Password object
 *
 * @param name password name
 * @param password password password
 * @param cats  password categories
 * @param website password serivice (blank=';')
 * @param login password login (blank=';')
 */
void PasswordManager::createPassword(string name, string password, string cats, string website, string login) {

    passwords.push_back(Password(name, password));


    vector<string> categoriesNames;
    stringstream s_stream(cats);
    while (s_stream.good())
    {
        string substr;

        getline(s_stream, substr, ';');

        categoriesNames.push_back(substr);
    }


    for (int i = 0; i < categoriesNames.size(); i++)
    {
        if (!CategoryManager::checkIfCategoryExists(categoriesNames[i]))
        {

            CategoryManager::createCategory(categoriesNames[i]);
        }

        passwords[passwords.size() - 1].addCategory(categoriesNames[i]);
    }

    if (website != ";")
    {
        passwords[passwords.size() - 1].addService(website);
    }
    else
    {
        passwords[passwords.size() - 1].deleteService();
    }

    if (login != ";")
    {
        passwords[passwords.size() - 1].addLogin(login);
    }
    else
    {
        passwords[passwords.size() - 1].deleteLogin();
    }
}

/**
 * @brief checks if password with given name exists
 *
 * @param name password name
 * @return true if exists
 * @return false if dont
 */
bool PasswordManager::checkIfPasswordExists(string name) {
    for (int i = 0; i < passwords.size(); i++)
    {
        if (passwords[i].getName() == name)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief removes password from passwords
 *
 * @param name password name that will be removed
 */
void PasswordManager::removePassword(string name) {
    int idx = getPasswordIndex(name);

    if (idx != -1)
    {
        passwords.erase(passwords.begin() + idx);
    }
}

/**
 * @brief removes all password with specified category
 *
 * @param name categpry name
 */
void PasswordManager::removePasswordsWithCategory(string name) {
    vector<Password>::iterator new_end = remove_if(passwords.begin(), passwords.end(), [&](const Password &a)
    { return a.containCategory(name); });

    passwords.erase(new_end, passwords.end());
}

/**
 * @brief eallowes user to edit password object specified by name
 *
 * @param name password name
 * @param choice user chosen edit type
 */
void PasswordManager::editPassword(string name, char choice) {
    int idx = PasswordManager::getPasswordIndex(name);

    string newValue;
    char newChoice;

    int newLength = 0;
    bool capitalLetters = false;
    bool specials = false;
    char decision, decision2;

    cin.clear();
    fflush(stdin);
    switch (choice)
    {
        case '1':
            cout << "Podaj nowa nazwe: ";
            getline(cin, newValue);
            if (!PasswordManager::checkIfPasswordExists(newValue))
            {
                passwords[idx].setName(newValue);
                cout << endl
                     << "Nazwa zostala zmieniona!" << endl;
            }
            else
            {
                cout << endl
                     << endl
                     << "Haslo o takiej nazwie juz istnieje! Nie dokonano zmiany" << endl;
            }
            break;
        case '2':
            cout << endl
                 << endl
                 << "Wybierz opcje: " << endl;
            cout << "1- wpisz recznie nowe haslo" << endl;
            cout << "2- wygeneruj nowe haslo" << endl;
            cin >> newChoice;

            switch (newChoice)
            {
                case '1':
                    cout << endl
                         << endl
                         << "Wpisz nowe haslo: " << endl;
                    cin >> newValue;

                    if (PasswordManager::checkIfPasswordWasUsed(newValue))
                    {
                        cout << "Haslo bylo juz uzyte wczeniej, zalecana jego zmiana!!!!" << endl;
                    }

                    passwords[idx].setPassword(newValue);
                    cout << "Haslo zostalo zmienione" << endl;

                    break;
                case '2':
                    cout << endl
                         << endl
                         << "Podaj ilosc znakow: " << endl;
                    cin >> newLength;
                    cout << "Czy duze i male litery? (y/N): " << endl;
                    cin >> decision;
                    cout << "Czy znaki specialne? (y/N): " << endl;
                    cin >> decision2;

                    newValue = PasswordManager::generatePassword(newLength, decision, decision2);

                    passwords[idx].setPassword(newValue);

                    cout << "Haslo zostalo ustawione i wynosi: " << newValue << endl;
                    break;
                default:
                    cout << endl
                         << "Wybrano nieprawidlowa opcje!" << endl;
            }

            break;
        case '3':
            cout << "Podaj nazwe kategori ktora chcesz dodac: ";
            getline(cin, newValue);
            if (!CategoryManager::checkIfCategoryExists(newValue))
            {
                passwords[idx].addCategory(newValue);
                cout << endl
                     << "Kategoria zostala dodana!" << endl;
            }
            else
            {
                cout << endl
                     << endl
                     << "Kategoria o takiej nazwie nie istnieje! Nic nie dodano" << endl;
            }
            break;
        case '4':
            cout << "Podaj nazwe kategori ktora chcesz usunac: ";
            getline(cin, newValue);
            if (!CategoryManager::checkIfCategoryExists(newValue))
            {
                passwords[idx].removeCategory(newValue);
                cout << endl
                     << "Kategoria zostala usunieta!" << endl;
            }
            else
            {
                cout << endl
                     << endl
                     << "Kategoria o takiej nazwie nie istnieje! Nic nie usunieto" << endl;
            }
            break;
        case '5':
            cout << "Podaj nazwe serwisu ktory chcesz dodac: ";
            getline(cin, newValue);
            passwords[idx].addService(newValue);
            cout << endl
                 << "Serwis zostal dodany!" << endl;
            break;
        case '6':
            passwords[idx].deleteService();
            cout << endl
                 << "Serwis zostal usuniety!" << endl;
            break;
        case '7':
            cout << "Podaj login ktory chcesz dodac: ";
            getline(cin, newValue);
            passwords[idx].addLogin(newValue);
            cout << endl
                 << "Login zostal dodany!" << endl;
            break;
        case '8':
            passwords[idx].deleteLogin();
            cout << endl
                 << "Login zostal usuniety!" << endl;
            break;
    }
}

/**
 * @brief generates new random password
 *
 * @param l length of password
 * @param d1 y if should have upper letters
 * @param d2 y if should have special characters
 * @return string newly generated password
 */
string PasswordManager::generatePassword(int l, char d1, char d2) {
    srand(time(NULL));

    string result;

    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    char lettersUpper[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lettersSpecial[] = "abcdefghijklmnopqrstuvwxyz@#$&";
    char lettersUpperSpecial[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@#$&";

    char *chosen = letters;
    int siz = 26;

    if (d1 == 'y')
    {
        chosen = lettersUpper;
        siz = 52;
        if (d2 == 'y')
        {
            chosen = lettersUpperSpecial;
            siz = 56;
        }
    }
    else
    {
        if (d2 == 'y')
        {
            chosen = lettersSpecial;
            siz = 30;
        }
    }

    for (int i = 0; i < l; i++)
    {
        result += chosen[rand() % siz];
    }

    return result;
}

/**
 * @brief checks if password value was used in other password objects
 *
 * @param pass password attribute
 * @return true if was
 * @return false if dont
 */
bool PasswordManager::checkIfPasswordWasUsed(string pass) {
    for (int i = 0; i < passwords.size(); i++)
    {
        if (passwords[i].getPassword() == pass)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the all password objects
 *
 * @return vector<Password> with all passwords
 */
vector<Password> PasswordManager::getAllPasswords()
{
    return passwords;
}
