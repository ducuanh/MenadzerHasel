
#include <vector>
#include <string>
#include "category.h"


using namespace std;


/**
 * @brief Construct a new Category object
 *
 */
Category::Category()
{
    name = "";
}

/**
 * @brief Construct a new Category object
 *
 * @param name_ category name
 */
Category::Category(string name_) {
    name = name_;
}

/**
 * @brief Get the Name property
 *
 * @return string
 */
string Category::getName() const
{
    return name;
}

/**
 * @brief checks if category of given name exists
 *
 * @param category category name
 * @return true if category of that name exists
 * @return false if not
 */
bool CategoryManager::checkIfCategoryExists(const string category){
    for (int i = 0; i < categories.size(); i++)
    {
        if (categories[i].getName() == category)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the Category By Name property
 *
 * @param category
 * @return Category
 */
Category  CategoryManager::getCategoryByName(const string category){
    for (int i = 0; i < categories.size(); i++)
    {
        if (categories[i].getName() == category)
        {
            return categories[i];
        }
    }
    return categories[0];
}

/**
 * @brief Create a Category object
 *
 * @param name new category name
 */
void CategoryManager::createCategory(const string name){
    categories.push_back(Category(name));
}

/**
 * @brief removes category object
 *
 * @param name category name
 */
void CategoryManager::removeCategory(const string name){
    for(int i=0; i<categories.size(); i++){
        if(categories[i].getName() == name) {
            categories.erase(categories.begin() + i);
            return;
        }
    }
}


