//
// Created by Alex on 04/05/2025.
//

#ifndef CURRENCYTABLE_H
#define CURRENCYTABLE_H
#include "../include/Currency.h"
// CHAOS
// TRANSMUTATION
// ALCHEMY
// SCOURING
// EXALTED
// ANNULMENT


class CurrencyTable {
private:
    static Item *chaos_orb; // = new Currency(RARE, CHAOS, "Chaos Orb", "Reforges a rare item with new random properties");
    static Item *transmutation_orb; // = new Currency(NORMAL, TRANSMUTATION, "Transmutation Orb","Upgrades a normal item to Magic rarity");
    static Item *alchemy_orb; // = new Currency(NORMAL, ALCHEMY, "Alchemy Orb", "Upgrades a normal item to Rare rarity");
    static Item *scouring_orb; // = new Currency(ANY, SCOURING, "Scouring Orb", "Removes all mods from an item and makes it normal");
    static Item *exalted_orb; // = new Currency(RARE, EXALTED, "Exalted Orb", "Adds a new random modifier to a rare item");
    static Item *annulment_orb; // = new Currency(ANY, ANNULMENT, "Annul Orb", "Removes a random modifier from an item");

public:
    // prevent instantiation
    CurrencyTable() = delete;
    static Item* GetOrb(currencyTypes curr);
};
#endif //CURRENCYTABLE_H
