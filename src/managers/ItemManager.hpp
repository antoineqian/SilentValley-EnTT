#pragma once
#include "../Item.hpp"
#include <fstream>

class ItemManager
{
private:
    std::vector<const Item> availableItems;

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
            std::cout << "New Line\n";
            std::istringstream iss(line);
            string name;
            int price;
            while (iss >> name >> price)
            {
                availableItems.push_back(Item({price, name}));
            }
        }
    }
    std::vector<const Item> getAvailableItems()
    {
        return availableItems;
    };
};
