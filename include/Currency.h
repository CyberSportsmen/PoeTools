// Currency.h
#pragma once

#include "Item.h"
#include "../utils/enumerators.h"

class Currency : public Item {
    itemRarities   targetRarity;
    currencyTypes  currencyType;

public:
    // your existing constructor
    explicit Currency(itemRarities rarityTarget,
                      currencyTypes typecurr,
                      const std::string& name,
                      const std::string& description)
      : Item(name, description, CURRENCY, 1, 1, 20, 0, 0),
        targetRarity(rarityTarget),
        currencyType(typecurr)
    {}
    itemRarities getRarity() const {return targetRarity;}
    currencyTypes getCurrencyType() const {return currencyType;}

    friend std::size_t hash_value(const Currency &obj);

    ~Currency() = default;
    Currency(const Currency&) = default;
    Currency(Currency&&) = default;
    Currency() = delete;

    Item* clone() const override; // Ensure it's marked override

    //void use_item() override;

    friend bool operator==(const Currency &lhs, const Currency &rhs);
    friend bool operator!=(const Currency &lhs, const Currency &rhs);
};
