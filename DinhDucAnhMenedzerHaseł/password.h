//
// Created by ducan on 13.06.2022.
//
#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "category.h"
#ifndef PROJEKTMENADZERHASELDUCANHDINH_PASSWORD_H
#define PROJEKTMENADZERHASELDUCANHDINH_PASSWORD_H

using namespace std;
class Password
{
private:
    string password;
    string name;
    string login;
    string service;
    bool hasLogin;
    bool hasService;
    vector<Category> categories;

public:

    Password();

    Password(string name_, string password_);

    bool addCategory(string cat);

    void addService(string service_);

    void addLogin(string login_);

    void deleteLogin();


    bool hasLoginf();


    string getLogin() const;


    bool hasServicef();

    string getService() const;


    void deleteService();


    string getName() const;

    void setName(string name_);


    void setPassword(string pass);


    string getPassword() const;



    bool containCategory(string name) const;



    void removeCategory(string name);



    string getCategoriesHuman() const;


    string getCategoriesFile();

};
class PasswordManager {
private:
    static vector<Password> passwords;

    int static getPasswordIndex(string name);

public:
    void static createPassword(string name, string password, string cats, string website, string login);


    bool static checkIfPasswordExists(string name);


    void static removePassword(string name);


    void static removePasswordsWithCategory(string name);


    void static editPassword(string name, char choice);


    string static generatePassword(int l, char d1, char d2);


    bool static checkIfPasswordWasUsed(string pass);


    vector<Password> static getAllPasswords();
};



#endif //PROJEKTMENADZERHASELDUCANHDINH_PASSWORD_H
