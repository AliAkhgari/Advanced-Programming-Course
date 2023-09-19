#include "Container.hpp"

using namespace std;

void tab(int number);

void Container::addMotherObject()
{
    Object* mother_object = new Object(MOTHER_OBJECT_ID, MOTHER_OBJECT_ID, MOTHER_OBJECT);
    objects.push_back(mother_object);
}

void Container::addStringToObject(int parentId, string key, string value)
{
    if(!isObjectExists(parentId))
        throw InvalidId();
    if(!isKeyUnique(key))
        throw DuplicateKey();

    keys.push_back(key);
    KeyString* key_string = new KeyString(parentId, key, value);
    key_string->dataType = KEY_STRING;
    datas.push_back(key_string);
}

void Container::addIntToObject(int parentId, string key, int value)
{
    if(!isObjectExists(parentId))
        throw InvalidId();
    if(!isKeyUnique(key))
        throw DuplicateKey();

    keys.push_back(key);
    KeyInt* key_int = new KeyInt(parentId, key, value);
    key_int->dataType = KEY_INT;
    datas.push_back(key_int);
}

void Container::addObjectToObject(int parentId, int id, string key, string type)
{
    if(!isObjectExists(parentId))
        throw InvalidId();
    if(!isKeyUnique(key))
        throw DuplicateKey();

    keys.push_back(key);//______________________________*******________________________________
    Object* object = new Object(parentId, id, key);
    object->dataType = OBJECT;
    datas.push_back(object);
    objects.push_back(object);
}

void Container::addArrayToObject(int parentId, int id, string key, string type)
{
    if(!isObjectExists(parentId))
        throw InvalidId();
    if(!isKeyUnique(key))
        throw DuplicateKey();

    keys.push_back(key);//______________________________*******________________________________
    Array* array = new Array(parentId, id, key);
    array->dataType = ARRAY;
    datas.push_back(array);
    arrays.push_back(array);
}

void Container::addStringToArray(int parentId, string value)
{
    if(!isArrayExists(parentId))
        throw InvalidId();

    String* string_ = new String(parentId, value);
    string_->dataType = STRING;
    datas.push_back(string_);
}

void Container::addIntegerToArray(int parentId, int value)
{
    if(!isArrayExists(parentId))
        throw InvalidId();

    Int* int_ = new Int(parentId, value);
    int_->dataType = INT;
    datas.push_back(int_);
}

void Container::addObjectToArray(int parentId, int id, string type)
{
    if(!isArrayExists(parentId))
        throw InvalidId();

    Object* object = new Object(parentId, id, NULL_KEY);
    object->dataType = OBJECT;
    datas.push_back(object);
    objects.push_back(object);
}

void Container::addArrayToArray(int parentId, int id, string type)
{
    if(!isArrayExists(parentId))
        throw InvalidId();

    Array* array = new Array(parentId, id, NULL_KEY);
    array->dataType = ARRAY;
    datas.push_back(array);
    arrays.push_back(array);
}

void Container::print(int id)
{
    if(!isObjectExists(id))
        throw InvalidId();
        
    vector <Data*> infos = childsInfo(id);
    cout << OPEN_BRACE;
    if(infos.size() != 0)
        cout << endl;

    printJsonInfo(infos);

    cout << CLOSE_BRACE << endl;
}

vector <Data*> Container::childsInfo(int parentId)
{
    vector <Data*> data;
    for(int i = 0; i < datas.size(); i++)
    {
        if(datas[i]->getParentId() == parentId)
            data.push_back(datas[i]);
    }
    return data;
}

void decideToPutComma(int i, int parentDataSize)
{
    if(i != parentDataSize - 1)
        cout << ",\n";
    else
        cout << "\n";
}

void printContainerFormat(Data* info, string containerSign, int tabNumber)
{
    string doubleQoute = "\"";
    string key = doubleQoute + info->getKey() + doubleQoute + ": " + containerSign;

    tab(tabNumber);

    if(info->getKey() == NULL_KEY)
        cout << containerSign;
    else
        cout << key;
    
}

bool Container::isObjectExists(int id)
{
    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i]->getId() == id)
            return true;
    }

    return false;
}

bool Container::isArrayExists(int id)
{
    for(int i = 0; i < arrays.size(); i++)
    {
        if(arrays[i]->getId() == id)
            return true;
    }

    return false;
}

bool Container::isKeyUnique(string key)
{
    for(int i = 0; i < keys.size(); i++)
    {
        if(keys[i] == key)
            return false;
    }

    return true;
}

void Container::printJsonInfo(vector <Data*> infos)
{
    static int tabNumber = 1;

    for(int i = 0; i < infos.size(); i++)
    {
        bool hasChild = false;
        if(infos[i]->dataType == ARRAY || infos[i]->dataType == OBJECT)
        {
            tab(tabNumber);
            infos[i]->print();
            tabNumber++;
            if(childsInfo(infos[i]->getId()).size() != 0)
            {
                hasChild = true;
                NEW_LINE;
            }
            printJsonInfo(childsInfo(infos[i]->getId()));
            tabNumber--;
            if(hasChild)
                tab(tabNumber);
            infos[i]->printContainerSign();
            decideToPutComma(i, infos.size());
        }
        else
        {
            tab(tabNumber);
            infos[i]->print();
            decideToPutComma(i, infos.size());
        }
    }
}

void tab(int number)
{
    for(int i = 0; i < number; i++)
        TAB;
}
