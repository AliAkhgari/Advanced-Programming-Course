#ifndef __JSON_BUILDER_H__
#define __JSON_BUILDER_H__ "__JSON_BUILDER_H__"

#include <string>
#include <vector>
#include "Container.hpp"
#include <random>
#include "invalidId.hpp"
#include "DuplicateKey.hpp"
#include "UndefinedType.hpp"
#include <exception>

class JsonBuilder
{
    private:
        Container container;

    public:
        JsonBuilder()
        {
            container.addMotherObject();
        }
        
        int randomNumber();

        void addStringToObject(int parentId, std::string key, std::string value);

        void addIntegerToObject(int parentId, std::string key, int value);

        int addContainerToObject(int parentId, std::string key, std::string type);
       
        void addStringToArray(int parentId, std::string value);

        void addIntegerToArray(int parentId, int value);

        int addContainerToArray(int parentId, std::string type);

        void print(int id);

};

bool isTypeDefined(std::string type);

#endif 