//
// Created by Alex on 27/05/2025.
//

#ifndef TRANSMUTATIONORBSTRATEGY_H
#define TRANSMUTATIONORBSTRATEGY_H

#include "ICurrencyEffectStrategy.h"
#include "../include/Equipment.h" // Pentru a avea definiția completă a Equipment
#include "../include/Currency.h"  // Pentru a avea definiția completă a Currency
#include "../include/CraftingBench.h" // Pentru a folosi metodele de crafting
#include "../utils/enumerators.h" // Pentru itemRarities

class TransmutationOrbStrategy : public ICurrencyEffectStrategy {
public:
    bool applyEffect(Equipment* target, Currency* currency) override;
};

#endif //TRANSMUTATIONORBSTRATEGY_H
