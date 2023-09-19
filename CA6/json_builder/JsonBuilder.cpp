#include "JsonBuilder.hpp"

using namespace std;

int JsonBuilder::randomNumber()
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(1,1000);
    return dist6(rng);
}

void JsonBuilder::addStringToObject(int parentId, string key, string value)
{
    container.addStringToObject(parentId, key, value);
}

void JsonBuilder::addIntegerToObject(int parentId, string key, int value)
{   
    container.addIntToObject(parentId, key, value);
}

int JsonBuilder::addContainerToObject(int parentId, string key, string type)
{
    int id;

    id = randomNumber();
    if(type == OBJECT)
    {
        container.addObjectToObject(parentId, id, key, type);
    }
    else if(type == ARRAY)
    {
        container.addArrayToObject(parentId, id, key, type);
    }
    else//_______________******________________
        throw UndefinedType();
    
    return id;
}

void JsonBuilder::addStringToArray(int parentId, string value)
{
    container.addStringToArray(parentId, value);
}

void JsonBuilder::addIntegerToArray(int parentId, int value)
{
    container.addIntegerToArray(parentId, value);
}

int JsonBuilder::addContainerToArray(int parentId, string type)
{
    int id;

    id = randomNumber();
    if(type == OBJECT)
    {
        container.addObjectToArray(parentId, id, type);
    }
    else if(type == ARRAY)
    {
        container.addArrayToArray(parentId, id, type);
    }
    else//_______________******________________
        throw UndefinedType();

    return id;
}

void JsonBuilder::print(int id)
{
    container.print(id);
}
