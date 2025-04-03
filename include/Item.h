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
    std::string name{"genericItem"};
    std::string description{"This item has no description"};
    itemTypes type{EQUIPMENT}; // default is generic equipment (2x2, no mods)
    unsigned int unique_id{};
    unsigned int width{2};
    unsigned int height{2};
    unsigned int maxStackSize{1};
    unsigned int minStackSize{1};
    unsigned int currentStackSize{1}; // for inventory management
    unsigned int maxSockets{4};
    unsigned int sockets{1};
    unsigned int itemLevel{100}; // default maximum (de obicei 85-86 e maximul pentru orice T1)
    sf::Texture texture; // item image
    itemRarities rarity{NORMAL};
    unsigned int maxPrefixes{0};
    unsigned int maxSuffixes{0};
    unsigned int quality{0};
    std::vector<Mod> affixes{}; // mods applied to the item
    std::vector<Mod> implicit{}; // implicit mods
public:
    Item();
    Item(const std::string& name, const std::string& description, itemTypes type, itemRarities rarity,
         unsigned int quality, unsigned int itemLevel, unsigned int width, unsigned int height,
         unsigned int maxStackSize, unsigned int minStackSize, unsigned int maxSockets, unsigned int sockets);
    Item(const Item& other) = default;
    Item(Item&& other) noexcept = default;
    Item& operator=(const Item& other) = default;
    Item& operator=(Item&& other) noexcept = default;
    const std::string& get_name() const;
    // [[maybe_unused]]void set_name(const std::string& newName) { name = newName; } //nu redenumim item-ul inca (la crafting se va redenumi)
    // [[maybe_unused]]void set_description(const std::string& newDescription) { this->description = newDescription; }
    // [[maybe_unused]]itemTypes get_type() const { return type; }
    // [[maybe_unused]]void set_type(itemTypes type) { this->type = type; }
    // [[maybe_unused]]unsigned int get_item_level() const { return itemLevel; } //util mai tarz
    // [[maybe_unused]]void set_item_level(unsigned int item_level) { itemLevel = item_level; }
    // [[maybe_unused]]sf::Texture get_texture() const { return texture; }
    // [[maybe_unused]]void set_texture(const sf::Texture& texture) { this->texture = texture; }
    // [[maybe_unused]]itemRarities get_rarity() const { return rarity; }
    // [[maybe_unused]]void set_rarity(itemRarities const rarity) { this->rarity = rarity; } // va fi folosit la alchemy, regal, transmutation, scour orb
    // [[maybe_unused]]unsigned int get_quality() const { return quality; }
    // [[maybe_unused]]void set_quality(unsigned int quality) { this->quality = quality; }
    const std::vector<Mod>& get_affixes() const;
    void set_affixes(const std::vector<Mod>& newAffixes);
    // [[maybe_unused]]std::vector<Mod> get_implicit() const { return implicit; }
    // [[maybe_unused]]void set_implicit(const std::vector<Mod>& implicit) { this->implicit = implicit; }
    unsigned int get_current_stack_size() const;
    void set_current_stack_size(unsigned int current_stack_size);
    unsigned int get_maxStackSize() const;
    unsigned int get_width() const;
    unsigned int get_height() const;
    unsigned int get_maxPrefixes() const;
    unsigned int get_maxSuffixes() const;
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
