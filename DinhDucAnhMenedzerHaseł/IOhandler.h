//
// Created by ducan on 13.06.2022.
//
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include "password.h"
#ifndef PROJEKTMENADZERHASELDUCANHDINH_IOHANDLER_H
#define PROJEKTMENADZERHASELDUCANHDINH_IOHANDLER_H


using namespace std;
class  IOhandler {
private:
    static bool wasError;


    string static decodeValue(string value, int key);



    string static encodeValue(string value, int key);



    vector<string> static preprocessLine(string line, int index, int key);

public:

    int static convertPassword(string filePassword);


    void static loadFile(string path, string filePassword);


    void static encodeAndSave(string filePath, int key);


    bool static getWasError();
};
#endif //PROJEKTMENADZERHASELDUCANHDINH_IOHANDLER_H