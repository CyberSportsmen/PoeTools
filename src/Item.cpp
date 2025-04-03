//
// Created by Alex on 2 Apr 2025.
//

#include "../include/Item.h"
#include "../ResourceManager.hpp"
Item::Item()
{
    unique_id = ++item_count;
    name = "genericItem";
    description = "This item has no description";
    type = EQUIPMENT;
    rarity = NORMAL;
    quality = 0;
    itemLevel = 100;
    width = 1;
    height = 1;
    maxStackSize = 1;
    minStackSize = 1;
    maxSockets = 0;
    sockets = 0;
}

Item::Item(const std::string& name, const std::string& description, itemTypes type, itemRarities rarity, unsigned int quality, unsigned int itemLevel, unsigned int width, unsigned int height, unsigned int maxStackSize, unsigned int minStackSize, unsigned int maxSockets, unsigned int sockets)
{
    unique_id = ++item_count;
    this->name = name;
    this->texture = ResourceManager::Instance().getTexture(name + ".png");
    this->quality = quality;
    this->itemLevel = itemLevel;
    this->description = description;
    this->type = type;
    this->width = width;
    this->height = height;
    this->maxStackSize = maxStackSize;
    this->minStackSize = minStackSize;
    this->maxSockets = maxSockets;
    this->sockets = sockets;
    switch (rarity)
    {
    case NORMAL:
        this->rarity = NORMAL;
        maxPrefixes = 0;
        maxSuffixes = 0;
        break;
    case MAGIC:
        this->rarity = MAGIC;
        maxPrefixes = 1;
        maxSuffixes = 1;
        break;
    case RARE:
        this->rarity = RARE;
        maxPrefixes = 3;
        maxSuffixes = 3;
        break;
    default:
        this->rarity = NORMAL;
        maxPrefixes = 0;
        maxSuffixes = 0;
        break;
    }
}

const std::string& Item::get_name() const
{
    return name;
}

const std::vector<Mod>& Item::get_affixes() const
{
    return this->affixes;
}

unsigned int Item::get_current_stack_size() const
{
    return this->currentStackSize;
}

unsigned int Item::get_height() const
{
    return this->height;
}

unsigned int Item::get_unique_id() const
{
    return unique_id;
}

unsigned int Item::get_width() const
{
    return this->width;
}

void Item::set_current_stack_size(unsigned int current_stack_size)
{
    this->currentStackSize = current_stack_size;
}

unsigned int Item::get_maxPrefixes() const
{
    return this->maxPrefixes;
}

unsigned int Item::get_maxSuffixes() const
{
    return this->maxSuffixes;
}

unsigned int Item::get_maxStackSize() const
{
    return this->maxStackSize;
}

void Item::set_affixes(const std::vector<Mod>& newAffixes)
{
    this->affixes = newAffixes;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "Name: " << item.name << std::endl;
    os << "Description: " << item.description << std::endl;
    os << "Type: " << item.type << std::endl;
    os << "Item Level: " << item.itemLevel << std::endl;
    os << "Quality: " << item.quality << std::endl;
    os << "Max Stack Size: " << item.maxStackSize << std::endl;
    os << "Max Prefixes: " << item.maxPrefixes << std::endl;
    os << "Max Suffixes: " << item.maxSuffixes << std::endl;
    os << "Max Sockets: " << item.maxSockets << std::endl;
    os << "Sockets: " << item.sockets << std::endl;
    os << "Width: " << item.width << std::endl;
    os << "Height: " << item.height << std::endl;
    os << "Current Stack Size: " << item.currentStackSize << std::endl;
    os << "Rarity: " << item.rarity << std::endl;
    os << "Affixes: " << std::endl;
    for (const auto& mod : item.affixes)
    {
        os << mod << std::endl;
    }
    return os;
}

bool operator==(const Item& lhs, const Item& rhs)
{
    return lhs.name == rhs.name &&
               lhs.description == rhs.description &&
               lhs.type == rhs.type &&
               lhs.width == rhs.width &&
               lhs.height == rhs.height &&
               lhs.maxStackSize == rhs.maxStackSize &&
               lhs.minStackSize == rhs.minStackSize &&
               lhs.maxSockets == rhs.maxSockets &&
               lhs.sockets == rhs.sockets &&
               lhs.itemLevel == rhs.itemLevel &&
               lhs.rarity == rhs.rarity &&
               lhs.maxPrefixes == rhs.maxPrefixes &&
               lhs.maxSuffixes == rhs.maxSuffixes &&
               lhs.quality == rhs.quality &&
               lhs.affixes == rhs.affixes &&
               lhs.implicit == rhs.implicit;
}

bool operator!=(const Item& lhs, const Item& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Item& lhs, const Item& rhs)
{
    return lhs.unique_id < rhs.unique_id;
}

// IMPORTANT!
unsigned int Item::item_count = 0;





