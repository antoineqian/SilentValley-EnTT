#pragma once
#include <string>
using std::string;

class Item
{
public:
    Item(int price, string name) : price(price), name(name)
    {
        path = "assets/map/objects/" + name + ".png";
    }
    void selectItem()
    {
    }
    const string& getPath() const { return path; }

    const string& getName() const { return name; }
    int getPrice() const { return price; }

private:
    int price;
    string name;
    string path;
};
