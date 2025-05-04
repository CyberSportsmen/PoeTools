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

// many more but these are the essential, others are niche
enum currencyTypes {
    CHAOS,
    TRANSMUTATION,
    ALCHEMY,
    SCOURING,
    EXALTED,
    ANNULMENT,
};

enum itemRarities
{
    NORMAL,
    MAGIC,       // blue
    RARE,
    UNIQUE,
    UNIQUE_FOIL, // shiny unique
    NO_RARITY,
    ANY, // placeholder for when it does not matter to check the rarity (i.e. Scouring orb (since we don't have unique items))
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
