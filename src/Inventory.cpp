//
// Created by Alex on 2 Apr 2025.
//

#include "../include/Inventory.h"

#include <iostream>
#include "../include/Item.h"

bool Inventory::check_if_item_fits(const Item& item, unsigned int row, unsigned int column) const
{
    unsigned int item_width = item.get_width();
    unsigned int item_height = item.get_height();
    for (unsigned int i = row; i < row + item_height; i++)
    {
        for (unsigned int j = column; j < column + item_width; j++)
        {
            if (!inside(i, j) ||
                inventory[i][j] == nullptr ||
                inventory[i][j]->get_name() != "emptySlot")
                return false;
        }
    }
    return true;
}

void Inventory::set_item_in_inventory_slot(const Item& item, unsigned int row, unsigned int column)
{
    inventory[row][column] = std::make_unique<Item>(item);
}

bool Inventory::tryStackItem(const Item& item) const
{
    // We assume stackable items have maxStackSize > 1.
    if (item.get_maxStackSize() <= 1)
        return false;

    for (unsigned int i = 0; i < 6; i++)
    {
        for (unsigned int j = 0; j < 10; j++)
        {
            if (inventory[i][j] != nullptr &&
                inventory[i][j]->get_name() == item.get_name() && inventory[i][j]->get_current_stack_size() < inventory[i][j]->get_maxStackSize())
            {
                unsigned int current = inventory[i][j]->get_current_stack_size();
                inventory[i][j]->set_current_stack_size(current + 1);
                return true;
            }
        }
    }
    return false;
}

Inventory::Inventory()
{
    // Initialize each cell with a default "empty" generic item.
    for (unsigned int i = 0; i < 6; i++)
    {
        for (unsigned int j = 0; j < 10; j++)
        {
            inventory[i][j] = std::make_unique<Item>();
        }
    }
}

void Inventory::place_item(const Item& item)
{
    if (tryStackItem(item))
        return; // Stacked successfully.

    unsigned int item_width = item.get_width();
    unsigned int item_height = item.get_height();
    for (unsigned int j = 0; j < 10; j++)
    {
        for (unsigned int i = 0; i < 6; i++)
        {
            if (check_if_item_fits(item, i, j))
            {
                // Record top-left position using the item's unique ID.
                item_positions[item.get_unique_id()] = {i, j};
                for (unsigned int k = i; k < i + item_height; k++)
                {
                    for (unsigned int l = j; l < j + item_width; l++)
                    {
                        set_item_in_inventory_slot(item, k, l);
                    }
                }
                return;
            }
        }
    }
    std::cout << item.get_name() << " could not be placed in the inventory." << std::endl;
}


bool Inventory::inside(unsigned int x, unsigned int y)
{
    return (x < 6 && y < 10);
}

void Inventory::print_inventory() const
{
    for (unsigned int row = 0; row < 6; row++)
    {
        for (unsigned int column = 0; column < 10; column++)
        {
            if (inventory[row][column] != nullptr)
                std::cout << inventory[row][column]->get_name() << " x"
                          << inventory[row][column]->get_current_stack_size() << "   ";
            else
                std::cout << "empty   ";
        }
        std::cout << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Inventory& inventory)
{
    for (unsigned int row = 0; row < 6; row++)
    {
        for (unsigned int column = 0; column < 10; column++)
        {
            if (inventory.inventory[row][column] != nullptr)
                os << inventory.inventory[row][column]->get_name() << " x"
                    << inventory.inventory[row][column]->get_current_stack_size() << "   ";
            else
                os << "empty   ";
        }
        os << std::endl;
    }
    return os;
}

