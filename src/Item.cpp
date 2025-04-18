//
// Created by Alex on 2 Apr 2025.
//

#include "../include/Item.h"
#include "../ResourceManager.hpp"
// Should be used for making empty inventory slots only!
// TODO: ask if it can be made protected friend of inventory class
Item::Item()
{
    unique_id = ++item_count;
    //TODO: add "emptySlot", an empty png just for this special item with special proprieties
    //texture = ResourceManager::Instance().getTexture(name + ".png");
    name = "emptySlot";
    description = "";
    type = EQUIPMENT; // should not be relevant for our purposes
    width = 1;
    height = 1;
    maxStackSize = 1;
    currentStackSize = 1;
    maxSockets = 0;
    sockets = 0;
}

Item::Item(const std::string& name, const std::string& description, itemTypes type, unsigned int width, unsigned int height, unsigned int maxStackSize, unsigned int maxSockets, unsigned int sockets)
{
    unique_id = ++item_count;
    this->name = name;
    this->texture = ResourceManager::Instance().getTexture(name + ".png");
    this->description = description;
    this->type = type;
    this->width = width;
    this->height = height;
    this->maxStackSize = maxStackSize;
    this->currentStackSize = 1; // when an item is created, there is only one of it created, even if stackable
    this->maxSockets = maxSockets;
    this->sockets = sockets;
    // switch (rarity)
    // {
    // case NORMAL:
    //     this->rarity = NORMAL;
    //     maxPrefixes = 0;
    //     maxSuffixes = 0;
    //     break;
    // case MAGIC:
    //     this->rarity = MAGIC;
    //     maxPrefixes = 1;
    //     maxSuffixes = 1;
    //     break;
    // case RARE:
    //     this->rarity = RARE;
    //     maxPrefixes = 3;
    //     maxSuffixes = 3;
    //     break;
    // default:
    //     this->rarity = NORMAL;
    //     maxPrefixes = 0;
    //     maxSuffixes = 0;
    //     break;
    // }
}

const std::string& Item::get_name() const
{
    return name;
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

unsigned int Item::get_maxStackSize() const
{
    return this->maxStackSize;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "Name: " << item.name << std::endl;
    os << "Description: " << item.description << std::endl;
    os << "Type: " << item.type << std::endl;
    os << "Max Stack Size: " << item.maxStackSize << std::endl;
    os << "Max Sockets: " << item.maxSockets << std::endl;
    os << "Sockets: " << item.sockets << std::endl;
    os << "Width: " << item.width << std::endl;
    os << "Height: " << item.height << std::endl;
    os << "Current Stack Size: " << item.currentStackSize << std::endl;
    os << "Affixes: " << std::endl;
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
               lhs.maxSockets == rhs.maxSockets &&
               lhs.sockets == rhs.sockets;
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





