//
// Created by Alex on 04/05/2025.
//

#include "CurrencyTable.h"

Item* CurrencyTable::chaos_orb         = new Currency(RARE, CHAOS,         "Chaos Orb",        "Reforges a rare item with new random properties");
Item* CurrencyTable::transmutation_orb = new Currency(NORMAL, TRANSMUTATION, "Transmutation Orb","Upgrades a normal item to Magic rarity");
Item* CurrencyTable::alchemy_orb       = new Currency(NORMAL, ALCHEMY,       "Alchemy Orb",      "Upgrades a normal item to Rare rarity");
Item* CurrencyTable::scouring_orb      = new Currency(ANY,    SCOURING,      "Scouring Orb",     "Removes all mods from an item and makes it normal");
Item* CurrencyTable::exalted_orb       = new Currency(RARE,   EXALTED,       "Exalted Orb",      "Adds a new random modifier to a rare item");
Item* CurrencyTable::annulment_orb     = new Currency(ANY,    ANNULMENT,     "Annul Orb",        "Removes a random modifier from an item");


Item* CurrencyTable::GetOrb(currencyTypes curr) {
    switch (curr) {
        case CHAOS: {
            return chaos_orb;
        }
        case TRANSMUTATION: {
            return transmutation_orb;
        }
        case ALCHEMY: {
            return alchemy_orb;
        }
        case SCOURING: {
            return scouring_orb;
        }
        case EXALTED: {
            return exalted_orb;
        }
        case ANNULMENT: {
            return annulment_orb;
        }
    }
    return chaos_orb;
}