//
// Created by ducan on 13.06.2022.
//
#pragma once
#include <string>
#ifndef PROJEKTMENADZERHASELDUCANHDINH_MANAGER_H
#define PROJEKTMENADZERHASELDUCANHDINH_MANAGER_H

using namespace std;
class manager {
private:
    bool exit;


    void removePassword();



    void editPassword();



    void addCategory();



    void removeCategory();


    void addPassword();



    void findPasswords();



    void sortPasswords();



    void saveAndExit(string path, string filePassword);



    void menuHandler(string path, string filePassword);

public:

    manager() ;

    void programLoop(string path, string filePassword);


};


#endif //PROJEKTMENADZERHASELDUCANHDINH_MANAGER_H
