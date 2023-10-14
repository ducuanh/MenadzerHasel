

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include "password.h"
#include "IOhandler.h"


using namespace std;





/**
 * @brief encrypts string
 *
 *
 * @param key encryption key
 * @return string decrypted string
 */
string IOhandler::encodeValue(string value, int key) {
    unsigned char ch;
    string res = "";
    for (int i = 0; i < value.length();i++){
        ch = value[i]+i+key+value.length();
        res += ch;
    }
    return res;
}

/**
 * @brief decodes encrypted string
 *
 *
 * @param key key that will be used for encryptions
 * @return string encrypted string
 */
string IOhandler::decodeValue(string value, int key) {
    unsigned char ch;
    string res = "";
    for (int i = 0; i < value.length();i++){
        ch = value[i]-key-i-value.length();
        res += ch;
    }
    return res;


}

/**
 * @brief preprocesses lines readed from file during initial load from disk
 *
 * @param line line from file
 * @param index line index
 * @param key decryption key
 * @return vector<string> splited line with proper parameters
 */
vector<string> IOhandler::preprocessLine(string line, int index, int key)
{
    vector<string> result;
    stringstream s_stream(line);
    while (s_stream.good())
    {
        string substr;

        getline(s_stream, substr, ',');
        substr = decodeValue(substr, key);

        result.push_back(substr);
    }

    return result;
}


/**
 * @brief converts user password into encryption key
 *
 * @param filePassword user typed password during initail logging
 * @return int generated key
 */
int IOhandler::convertPassword(const string filePassword)
{
    long long int key = 0;
    for (int i = 0; i < filePassword.length(); i++)
    {
        key += static_cast<int>(filePassword[i]);
    }

    return key % 26;
}


/**
 * @brief loads file from disk during startup
 *
 * @param path file with passwords path
 * @param filePassword user typed password during initail logging
 */
void IOhandler::loadFile(const string path, const string filePassword)
{
    int key = convertPassword(filePassword);

    string line = "";
    vector<string> separetedDecodedLine;
    int lineIndex = 0;

    ifstream file;

    file.open(path);

    if (file.is_open())
    {


        while (getline(file, line))
        {
            if(lineIndex > 0){
                separetedDecodedLine = preprocessLine(line, lineIndex, key);

                PasswordManager::createPassword(separetedDecodedLine[0], separetedDecodedLine[1], separetedDecodedLine[2], separetedDecodedLine[3], separetedDecodedLine[4]);


            }
            lineIndex++;
        }
    }
    else
    {
        cout << "Wystapil problem z otwieraniem plku ktory wskazano" << endl;
        wasError = true;
    }

    file.close();
}
/**
 * @brief encrypts and save the data back to disk
 *
 * @param filePath path to file that data will be saved to
 * @param key encryption key
 */
void IOhandler::encodeAndSave(string filePath, int key)
{
    vector<Password> passwords = PasswordManager::getAllPasswords();

    ofstream file;

    file.open(filePath, ofstream::out | ofstream::trunc);
    time_t t = time(0);
    tm* now = localtime(&t);
    file << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << "  czas: "
         <<  now->tm_hour << ':'
         <<  now->tm_min << ':'
         << now->tm_sec
         <<"\n";


    if (file.is_open())
    {
        for (int i = 0; i < passwords.size(); i++)
        {
            file << encodeValue(passwords[i].getName(), key) << "," << encodeValue(passwords[i].getPassword(), key) << "," << encodeValue(passwords[i].getCategoriesFile(), key) << "," << (passwords[i].hasServicef() ? encodeValue(passwords[i].getService(), key) : ";") << "," << (passwords[i].hasLoginf() ? encodeValue(passwords[i].getLogin(), key) : ";") << endl;
        }
        cout << "Pomyslnie zapisano zmiany!" << endl;
    }
    else
    {
        cout << "Wystapil problem z otwieraniem plku ktory wskazano" << endl;
        wasError = true;
    }

    file.close();
}

/**
 * @brief returns was error attrribue value
 * @return was error value
 */
bool IOhandler::getWasError()
{
    return wasError;
}

