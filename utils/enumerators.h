//
// Created by Alex on 2 Apr 2025.
//

#ifndef ENUMERATORS_H
#define ENUMERATORS_H
#include <map>
#include <string>

enum itemTypes
{
    EQUIPMENT,
    CURRENCY,
    MAP,
    GEM,      // socketable
    SPECIAL,  // quest items, shown in green text
};

const std::map<itemTypes, std::string> itemTypesToString = {
    {EQUIPMENT, "EQUIPMENT"},
    {CURRENCY, "CURRENCY"},
    {MAP, "MAP"},
    {GEM, "GEM"},
    {SPECIAL, "SPECIAL"}
};

enum itemRarities
{
    NORMAL,
    MAGIC,       // blue
    RARE,
    UNIQUE,
    UNIQUE_FOIL, // shiny unique
    NO_RARITY,
};

const std::map<itemRarities, std::string> itemRaritiesToString = {
    {NORMAL, "NORMAL"},
    {MAGIC, "MAGIC"},
    {RARE, "RARE"},
    {UNIQUE, "UNIQUE"},
    {UNIQUE_FOIL, "UNIQUE_FOIL"},
    {NO_RARITY, "NO_RARITY"}
};

enum equipmentTypes
{
    WEAPON,
    BODYARMOR,
    BOOTS,
    GLOVES,
    HELMET,
    RING,
    AMULET,
    JEWEL,
    BELT,
    FLASK,
};

const std::map<equipmentTypes, std::string> equipmentTypesToString = {
    {WEAPON, "WEAPON"},
    {BODYARMOR, "BODYARMOR"},
    {BOOTS, "BOOTS"},
    {GLOVES, "GLOVES"},
    {HELMET, "HELMET"},
    {RING, "RING"},
    {AMULET, "AMULET"},
    {JEWEL, "JEWEL"},
    {BELT, "BELT"},
    {FLASK, "FLASK"}
};

#endif //ENUMERATORS_H
