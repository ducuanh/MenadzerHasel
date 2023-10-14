#include "manager.h"
#include <string>
#include <vector>
#include "IOhandler.h"

using namespace std;


vector<Password> PasswordManager::passwords = vector<Password>();
vector<Category> CategoryManager::categories = vector<Category>();

bool IOhandler::wasError = false;

int main()
{
    string path = "", filePassword = "";


    cout << "Podaj sciezke do pliku ktorym chcesz sie zajac: ";
    getline(cin, path);
    cout<<endl;

    cout << "Podaj haslo ktorym chcesz odblokwoac ten plik: ";
    getline(cin, filePassword);
    cout<<endl;


    IOhandler::loadFile(path, filePassword);
    if(!IOhandler::getWasError()){

        manager manager;
        manager.programLoop(path, filePassword);
    }



    return 0;

}