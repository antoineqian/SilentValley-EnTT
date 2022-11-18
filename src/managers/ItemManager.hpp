#pragma once
#include "../Item.hpp"
#include <fstream>
#include <memory>

class ItemManager
{
private:
    std::vector<std::shared_ptr<const Item>> availableItems;

public:
    static ItemManager &inst()
    {
        static ItemManager mgr;
        return mgr;
    }
    void init()
    {
        std::ifstream file("assets/map/objects/itemList.txt");
        string line;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            string name;
            int price;
            while (iss >> name >> price)
            {
                availableItems.push_back(std::make_shared<Item>(price, name));
            }
        }
    }
    std::vector<std::shared_ptr<const Item>> getAvailableItems()
    {
        return availableItems;
    };
};
