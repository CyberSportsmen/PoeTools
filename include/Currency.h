//
// Created by Alex on 04/05/2025.
//

#ifndef CURRENCY_H
#define CURRENCY_H

#include <vector>

#include "Item.h"
#include "../utils/enumerators.h"
// the target of a currency item is always an equipment
// we just need to clarify the rarity of said item
class Currency :public Item {
    itemRarities targetRarity;
    currencyTypes currencyType;
public:
    // defaults to making a chaos orb
    explicit Currency(itemRarities rarityTarget, currencyTypes typecurr, const std::string& name, const std::string& description) : Item(name, description, CURRENCY, 1, 1, 20, 0, 0), targetRarity(rarityTarget), currencyType(typecurr){};
    ~Currency() = default;
    Currency(Currency&&) = default;
    Currency() = delete; // should not create our own currencies. all will be already created as there are a fixed number of those
    friend bool operator==(const Currency &lhs, const Currency &rhs);
    friend bool operator!=(const Currency &lhs, const Currency &rhs);

};

#endif //CURRENCY_H
