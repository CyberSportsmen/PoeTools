//
// Created by Alex on 2 Apr 2025.
//

#ifndef INVENTORY_H
#define INVENTORY_H
#include <array>
#include <map>
#include <memory>
#include "Item.h"

//-----------------------------------------------------------------
// Inventory Class (6x10 grid)
//-----------------------------------------------------------------
class Inventory
{
private:
    std::array<std::array<std::unique_ptr<Item>, 10>, 6> inventory{};
    std::map<unsigned int, std::pair<unsigned int, unsigned int>> item_positions;
    static bool inside(unsigned int x, unsigned int y);
    [[nodiscard]] bool check_if_item_fits(const Item& item, unsigned int row, unsigned int column) const;
    void set_item_in_inventory_slot(const Item& item, unsigned int row, unsigned int column);
    [[nodiscard]] bool tryStackItem(const Item& item) const;
public:
    Inventory();
    void place_item(const Item& item);
    void print_inventory() const;
    friend std::ostream& operator<<(std::ostream& os, const Inventory& inventory);

};

#endif //INVENTORY_H
