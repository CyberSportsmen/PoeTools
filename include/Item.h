//
// Created by Alex on 2 Apr 2025.
//

#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "../include/Mod.h"
#include "../utils/enumerators.h"
#include "SFML/Graphics/Texture.hpp"

class Item
{
    static unsigned int item_count;
    std::string name;
    std::string description;
    itemTypes type;
    unsigned int unique_id{};
    unsigned int width;
    unsigned int height;
    unsigned int maxStackSize;
    unsigned int currentStackSize; // for inventory management
    unsigned int maxSockets;
    unsigned int sockets;
    sf::Texture texture; // item image
public:
    Item();
    Item(const std::string& name, const std::string& description, itemTypes type, unsigned int width, unsigned int height,
         unsigned int maxStackSize, unsigned int maxSockets, unsigned int sockets);
    Item(const Item& other) = default;
    Item(Item&& other) noexcept = default;
    Item& operator=(const Item& other) = default;
    Item& operator=(Item&& other) noexcept = default;
    const std::string& get_name() const;
    // [[maybe_unused]]void set_name(const std::string& newName) { name = newName; } //nu redenumim item-ul inca (la crafting se va redenumi)
    // [[maybe_unused]]void set_description(const std::string& newDescription) { this->description = newDescription; }
    // [[maybe_unused]]itemTypes get_type() const { return type; }
    // [[maybe_unused]]void set_type(itemTypes type) { this->type = type; }
    // [[maybe_unused]]sf::Texture get_texture() const { return texture; }
    // [[maybe_unused]]void set_texture(const sf::Texture& texture) { this->texture = texture; }
    unsigned int get_current_stack_size() const;
    void set_current_stack_size(unsigned int current_stack_size);
    unsigned int get_maxStackSize() const;
    unsigned int get_width() const;
    unsigned int get_height() const;
    unsigned int get_unique_id() const;
    // [[maybe_unused]]void print_quality() const { std::cout << "Quality: " << quality << std::endl; }
    // [[maybe_unused]]void print_item_level() const { std::cout << "Item Level: " << itemLevel << std::endl; }
    // [[maybe_unused]]void print_size() const { std::cout << "Width: " << width << " Height: " << height << std::endl; }
    // [[maybe_unused]]void print_unique_id() const { std::cout << "Unique ID: " << unique_id << std::endl; }
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
    friend bool operator==(const Item& lhs, const Item& rhs);
    friend bool operator!=(const Item& lhs, const Item& rhs);
    friend bool operator<(const Item& lhs, const Item& rhs);
    ~Item() = default;
};

#endif //ITEM_H
