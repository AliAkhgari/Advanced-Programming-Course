#ifndef __CONTAINER_H__
#define __CONTAINER_H__ "__CONTAINER_H__"

#include <string>
#include <vector>
#include "Object.hpp"
#include "Data.hpp"
#include "Array.hpp"
#include <iostream>
#include "invalidId.hpp"
#include "DuplicateKey.hpp"
#include "UndefinedType.hpp"

#define TAB cout << "    "
#define NULL_KEY ""
#define ARRAY "array"
#define OBJECT "object"
#define KEY_STRING "keyString"
#define KEY_INT "keyInt"
#define INT "int"
#define STRING "string"
#define MOTHER_OBJECT "mother"
#define MOTHER_OBJECT_ID 0
#define OPEN_BRACE "{"
#define CLOSE_BRACE "}"
#define OPEN_BRACKET "["
#define CLOSE_BRACKET "]"
#define NEW_LINE cout << std::endl

class Container
{

private:
    std::vector < Data* > datas;
    std::vector < Array* > arrays;
    std::vector < Object* > objects;
    std::vector < std::string > keys;
    InvalidId* invalidId;
    UndefinedType* undefinedType;
    DuplicateKey* duplicateKey;
public:
    void addMotherObject();

    void addStringToObject(int parentId, std::string key, std::string value);

    void addIntToObject(int parentId, std::string key, int value);

    void addObjectToObject(int parentId, int id, std::string key, std::string type);
 
    void addArrayToObject(int parentId, int id, std::string key, std::string type);

    void addStringToArray(int parentId, std::string value);
   
    void addIntegerToArray(int parentId, int value);

    void addObjectToArray(int parentId, int id, std::string type);

    void addArrayToArray(int parentId, int id, std::string type);

    bool isObjectExists(int id);

    bool isArrayExists(int id);

    bool isKeyUnique(std::string key);
 
    std::vector < Data* > childsInfo(int parentId);

    void print(int id);

    void printJsonInfo(std::vector < Data* > parentData);

};

bool isTypeDefined(std::string type);

#endif