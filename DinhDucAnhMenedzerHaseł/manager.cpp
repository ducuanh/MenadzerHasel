#include <iostream>
#include "category.h"
#include "password.h"
#include "IOhandler.h"
#include "manager.h"
#include <algorithm>

using namespace std;




/**
 * @brief allowes user to remove password from passwords
 *
 */
void manager::removePassword()
{
    string name;

    cin.clear();
    fflush(stdin);
    cout << "Podaj nazwe hasla ktore chcesz usunac: ";
    getline(cin, name);
    cout << endl;

    if (PasswordManager::checkIfPasswordExists(name))
    {
        string confirmation;

        cout << "Czy napewno chcesz usunac haslo - " << name << "?(y/N) : ";
        cin >> confirmation;

        if (confirmation == "y")
        {
            PasswordManager::removePassword(name);
            cout << "Haslo - " << name << " zostalo usuniete!" << endl
                 << endl;
        }
        else
        {
            cout << endl
                 << endl;
        }
    }
    else
    {
        cout << "Haslo o zadanej nazwie nie istnieje!" << endl
             << endl;
    }
}

/**
 * @brief allowes user to edit any password from passwords
 *
 */
void manager::editPassword() {
    string name;

    cin.clear();
    fflush(stdin);
    cout << "Podaj nazwe hasla ktore chcesz edytowac: ";
    getline(cin, name);
    cout << endl;

    if (PasswordManager::checkIfPasswordExists(name))
    {

        char choice = 0;

        cout << "Co chcesz zmienic w tym hasle:" << endl;
        cout << "1- nazwe" << endl;
        cout << "2- haslo" << endl;
        cout << "3- dodac kategorie" << endl;
        cout << "4- usunac kategorie" << endl;
        cout << "5- dodac serwis/strone WWW" << endl;
        cout << "6- usunac serwis/strone WWW" << endl;
        cout << "7- dodac login" << endl;
        cout << "8- usunac login" << endl;
        cout << "9- wyjdz bez zmian" << endl;
        cin >> choice;


        switch (choice)
        {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                PasswordManager::editPassword(name, choice);
                break;
            case '9':
                break;
            default:
                cout << "Wybrano nieprawidlowa opcje!" << endl;
                break;
        }
    }
    else
    {
        cout << "Haslo o zadanej nazwie nie istnieje!" << endl
             << endl;
    }
}

/**
 * @brief Allowes user to create new category for later usage
 *
 */
void manager::addCategory() {
    string newCatName;

    cin.clear();
    fflush(stdin);
    cout << endl
         << endl
         << "Podaj nazwe kategori ktora chcesz utworzyc: ";
    getline(cin, newCatName);
    cout << endl;

    if (!CategoryManager::checkIfCategoryExists(newCatName))
    {
        CategoryManager::createCategory(newCatName);
        cout << "Kategoria " << newCatName << " zostala pomyslnie utworzona" << endl
             << endl;
    }
    else
    {
        cout << "istnieje juz taka kategoria, nowa nie zostala utworzona!" << endl
             << endl;
    }
}

/**
 * @brief Allowes user to remove any category and it's dependants
 *
 */
void manager::removeCategory()
{
    string name;

    cin.clear();
    fflush(stdin);
    cout << "Podaj nazwe kategori ktora chcesz usunac: ";
    getline(cin, name);
    cout << endl;

    if (CategoryManager::checkIfCategoryExists(name))
    {
        string confirmation;

        cout << "Czy napewno chcesz usunac kategorie - " << name << "?(y/N) : ";
        cin >> confirmation;

        if (confirmation == "y")
        {
            PasswordManager::removePasswordsWithCategory(name);
            CategoryManager::removeCategory(name);
            cout << "Kategoria - " << name << " zostala usunieta, razem z haslami po niej dziedziczacymi!" << endl
                 << endl;
        }
        else
        {
            cout << endl
                 << endl;
        }
    }
    else
    {
        cout << "Kategoria o takiej nazwie nie istnieje, nic nie zostalo usuniete!" << endl
             << endl;
    }
}

/**
 * @brief allowes user to create new password and saves it in mamory
 *
 */
void manager::addPassword() {
    cin.clear();
    fflush(stdin);

    // name
    cout << endl
         << endl
         << "Podaj nazwe dla nowego hasla: ";
    string newName;
    getline(cin, newName);

    if (PasswordManager::checkIfPasswordExists(newName))
    {
        cout << "Haslo o takiej nazwie juz istnieje!! Powtorz probe z inna nazwa!" << endl;
        return;
    }

    // password
    char newChoice;
    string newValue, newPassword;
    int newLength;
    char decision, decision2;

    cout << "Wybierz opcje: " << endl;
    cout << "1- wpisz recznie nowe haslo" << endl;
    cout << "2- wygeneruj nowe haslo" << endl;
    cin >> newChoice;

    switch (newChoice)
    {
        case '1':
            cout << endl
                 << "Wpisz nowe haslo: " << endl;
            cin >> newValue;

            if (PasswordManager::checkIfPasswordWasUsed(newValue))
            {
                cout << "Haslo bylo juz uzyte wczeniej, zalecana jego zmiana!!!!" << endl;
            }

            newPassword = newValue;

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

            newPassword = newValue;

            cout << "Haslo zostalo ustawione i wynosi: " << newValue << endl;
            break;
        default:
            cout << endl
                 << "Wybrano nieprawidlowa opcje! Powtorz operacje" << endl;
            return;
    }

    // category
    cin.clear();
    fflush(stdin);
    cout << "Podaj kategorie dla nowego hasla: ";
    string newCategory;
    getline(cin, newCategory);

    if (!CategoryManager::checkIfCategoryExists(newCategory))
    {
        cout << "Kategoria o takiej nazwie nie istnieje!! Rozpocznij proces tworzenia do nowa" << endl;
        return;
    }

    // service/www
    cin.clear();
    fflush(stdin);
    cout << "Podaj serwis dla nowego hasla(lub wpisz ';' aby pomiac): ";
    string newService;
    getline(cin, newService);

    // login
    cin.clear();
    fflush(stdin);
    cout << "Podaj login dla nowego hasla(lub wpisz ';' aby pomiac): ";
    string newlogin;
    getline(cin, newlogin);

    PasswordManager::createPassword(newName, newPassword, newCategory, newService, newlogin);
    cout << endl
         << "Haslo zostalo utworzone!!" << endl;
}

/**
 * @brief Allowes user to find and display passwords using simple serach function
 *
 */
void manager::findPasswords()
{
    char choice;
    string newVal;
    bool found = false;
    vector<Password> passwords = PasswordManager::getAllPasswords();

    cout << "Wybierz po jakim parametrze chcesz wyszukac hasla: " << endl;
    cout << "1- nazwa" << endl;
    cout << "2- haslo" << endl;
    cout << "3- kategoria" << endl;
    cout << "4- serwis" << endl;
    cout << "5- login" << endl;
    cout << "Twoj wybor: ";
    cin >> choice;

    switch (choice)
    {
        case '1':
            cout << "Podaj nazwe hasla ktorego szukasz: " << endl;

            cin.clear();
            fflush(stdin);
            getline(cin, newVal);

            cout << "Nazwa\tHaslo\tKategorie(po przecinku)\tSerwis(opcjonalny)\tLogin(opcjonalny)" << endl;

            for (int i = 0; i < passwords.size(); i++)
            {
                if (passwords[i].getName() == newVal)
                {
                    found = true;

                    cout << passwords[i].getName() << " | " << passwords[i].getPassword() << " | " << passwords[i].getCategoriesHuman() << " | " << (passwords[i].hasServicef() ? passwords[i].getService() : "-") << " | " << (passwords[i].hasLoginf() ? passwords[i].getLogin() : "-") << endl;
                }
            }

            if (!found)
            {
                cout << "BRAK!" << endl;
            }

            break;
        case '2':
            cout << "Podaj wartosc hasla ktorego szukasz: " << endl;

            cin.clear();
            fflush(stdin);
            getline(cin, newVal);

            cout << "Nazwa\tHaslo\tKategorie(po przecinku)\tSerwis(opcjonalny)\tLogin(opcjonalny)" << endl;

            for (int i = 0; i < passwords.size(); i++)
            {
                if (passwords[i].getPassword() == newVal)
                {
                    found = true;

                    cout << passwords[i].getName() << " | " << passwords[i].getPassword() << " | " << passwords[i].getCategoriesHuman() << " | " << (passwords[i].hasServicef() ? passwords[i].getService() : "-") << " | " << (passwords[i].hasLoginf() ? passwords[i].getLogin() : "-") << endl;
                }
            }

            if (!found)
            {
                cout << "BRAK!" << endl;
            }
            break;

        case '3':
            cout << "Podaj kategorie po ktorej chcesz szukac: " << endl;

            cin.clear();
            fflush(stdin);
            getline(cin, newVal);

            cout << "Nazwa\tHaslo\tKategorie(po przecinku)\tSerwis(opcjonalny)\tLogin(opcjonalny)" << endl;

            for (int i = 0; i < passwords.size(); i++)
            {
                if (passwords[i].containCategory(newVal))
                {
                    found = true;

                    cout << passwords[i].getName() << " | " << passwords[i].getPassword() << " | " << passwords[i].getCategoriesHuman() << " | " << (passwords[i].hasServicef() ? passwords[i].getService() : "-") << " | " << (passwords[i].hasLoginf() ? passwords[i].getLogin() : "-") << endl;
                }
            }

            if (!found)
            {
                cout << "BRAK!" << endl;
            }
            break;
        case '4':
            cout << "Podaj serwis po ktorym chcesz szukac: " << endl;

            cin.clear();
            fflush(stdin);
            getline(cin, newVal);

            cout << "Nazwa\tHaslo\tKategorie(po przecinku)\tSerwis(opcjonalny)\tLogin(opcjonalny)" << endl;

            for (int i = 0; i < passwords.size(); i++)
            {
                if (passwords[i].getService() == newVal && passwords[i].hasServicef())
                {
                    found = true;

                    cout << passwords[i].getName() << " | " << passwords[i].getPassword() << " | " << passwords[i].getCategoriesHuman() << " | " << (passwords[i].hasServicef() ? passwords[i].getService() : "-") << " | " << (passwords[i].hasLoginf() ? passwords[i].getLogin() : "-") << endl;
                }
            }

            if (!found)
            {
                cout << "BRAK!" << endl;
            }
            break;

        case '5':
            cout << "Podaj login po ktorym chcesz szukac: " << endl;

            cin.clear();
            fflush(stdin);
            getline(cin, newVal);

            cout << "Nazwa\tHaslo\tKategorie(po przecinku)\tSerwis(opcjonalny)\tLogin(opcjonalny)" << endl;

            for (int i = 0; i < passwords.size(); i++)
            {
                if (passwords[i].getLogin() == newVal && passwords[i].hasLoginf())
                {
                    found = true;

                    cout << passwords[i].getName() << " | " << passwords[i].getPassword() << " | " << passwords[i].getCategoriesHuman() << " | " << (passwords[i].hasServicef() ? passwords[i].getService() : "-") << " | " << (passwords[i].hasLoginf() ? passwords[i].getLogin() : "-") << endl;
                }
            }

            if (!found)
            {
                cout << "BRAK!" << endl;
            }
            break;
    }
}

/**
 * @brief displayes all passwords from memory sorted by specified parameter
 *
 */
void manager::sortPasswords() {
    char choice;
    vector<Password> passwords = PasswordManager::getAllPasswords();

    cout << "Wybierz po jakim parametrze chcesz posortowac hasla: " << endl;
    cout << "1- nazwa" << endl;
    cout << "2- haslo" << endl;
    cout << "3- kategoria" << endl;
    cout << "4- serwis" << endl;
    cout << "5- login" << endl;
    cout << "Twoj wybor: ";
    cin >> choice;

    switch (choice)
    {
        case '1':
            sort(passwords.begin(), passwords.end(), [](const Password &a, const Password &b)
            { return a.getName() < b.getName(); });
            break;
        case '2':
            sort(passwords.begin(), passwords.end(), [](const Password &a, const Password &b)
            { return a.getPassword() < b.getPassword(); });
            break;
        case '3':
            sort(passwords.begin(), passwords.end(), [](const Password &a, const Password &b)
            { return a.getCategoriesHuman() < b.getCategoriesHuman(); });
            break;
        case '4':
            sort(passwords.begin(), passwords.end(), [](const Password &a, const Password &b)
            { return a.getService() < b.getService(); });
            break;
        case '5':
            sort(passwords.begin(), passwords.end(), [](const Password &a, const Password &b)
            { return a.getLogin() < b.getLogin(); });
            break;
    }


    cout << endl
         << "Nazwa\tHaslo\tKategorie(po przecinku)\tSerwis(opcjonalny)\tLogin(opcjonalny)" << endl;
    for (int i = 0; i < passwords.size(); i++)
    {
        cout << passwords[i].getName() << " | " << passwords[i].getPassword() << " | " << passwords[i].getCategoriesHuman() << " | " << (passwords[i].hasServicef() ? passwords[i].getService() : "-") << " | " << (passwords[i].hasLoginf() ? passwords[i].getLogin() : "-") << endl;
    }
    cout << endl;
}

/**
 * @brief saves curent memory status back to disk
 *
 * @param path to file on disk
 * @param filePassword password that user used to open the file
 */
void manager::saveAndExit(string path, string filePassword) {
    IOhandler::encodeAndSave(path, IOhandler::convertPassword(filePassword));
    cout << "Do widzenia!" << endl;
    exit = true;
}

/**
 * @brief handles user interface
 *
 * @param path to file on disk
 * @param filePassword password that user used to open the file
 */
void manager::menuHandler(string path, string filePassword)
{
    char choice = 0;

    cout << "Wybierz co chcesz zrobic: " << endl;
    cout << "1- Wyszukaj hasla" << endl;
    cout << "2- Posortuj hasla" << endl;
    cout << "3- Dodaj haslo" << endl;
    cout << "4- Edytuj haslo" << endl;
    cout << "5- Usun haslo" << endl;
    cout << "6- Dodaj kategorie" << endl;
    cout << "7- Usun kategorie" << endl;
    cout << "8- Zapisz i wyjdz z programu" << endl;
    cout << "Twoj wybor: ";
    cin >> choice;


    switch (choice)
    {
        case '1':
            findPasswords();
            break;
        case '2':
            sortPasswords();
            break;
        case '3':
            addPassword();
            break;
        case '4':
            editPassword();
            break;
        case '5':
            removePassword();
            break;
        case '6':
            addCategory();
            break;
        case '7':
            removeCategory();
            break;
        case '8':
            saveAndExit(path, filePassword);
            break;
        default:
            cout << "Wybrano niepoprawna opcje!" << endl
                 << endl
                 << endl;
            break;
    }
}


/**
 * @brief Construct a new Manager object
 *
 */
manager::manager():exit(false)
{

}
/**
 * @brief main program loop that handles everything
 *
 * @param path path to file with passwords on disk
 * @param filePassword password that was used to open the file
 */
void manager::programLoop(string path, string filePassword)
{
    while (!exit)
    {
        menuHandler(path, filePassword);
    }
}
