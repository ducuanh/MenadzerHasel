//
// Created by ducan on 13.06.2022.
//
#pragma once
#include <string>
#include <vector>
#ifndef PROJEKTMENADZERHASELDUCANHDINH_CATEGORY_H
#define PROJEKTMENADZERHASELDUCANHDINH_CATEGORY_H
using namespace std;


class Category {
private:
    string name;

public:

    Category();


    Category(string name_);


    string getName() const;


};
class CategoryManager {
private:
    static vector<Category> categories;

public:

    bool static checkIfCategoryExists(string category);


    Category static getCategoryByName(string category);


    void static createCategory(string name);


    void static removeCategory(string name);


};
#endif //PROJEKTMENADZERHASELDUCANHDINH_CATEGORY_H;
