//
// Created by Alex on 27/05/2025.
//

#include "../include/CurrencyProcessor.h"

#include <iostream>

#include "../include/Currency.h"
#include "../include/Equipment.h"

#include "../include/TransmutationOrbStrategy.h"
// #include "ChaosOrbStrategy.h"
// #include "AlchemyOrbStrategy.h"
// #include "ScouringOrbStrategy.h"
// #include "ExaltedOrbStrategy.h"
// #include "AnnulmentOrbStrategy.h"

void CurrencyProcessor::registerStrategies() {
    strategies[TRANSMUTATION] = std::make_unique<TransmutationOrbStrategy>();
    // strategies[CHAOS] = std::make_unique<ChaosOrbStrategy>(); // De-comentează și adaugă când sunt gata
    // strategies[ALCHEMY] = std::make_unique<AlchemyOrbStrategy>();
    // strategies[SCOURING] = std::make_unique<ScouringOrbStrategy>();
    // strategies[EXALTED] = std::make_unique<ExaltedOrbStrategy>();
    // strategies[ANNULMENT] = std::make_unique<AnnulmentOrbStrategy>();
    // ... adaugă toate celelalte strategii aici
}

CurrencyProcessor::CurrencyProcessor() {
    registerStrategies();
}

bool CurrencyProcessor::use_currency(Currency* currency, Equipment* target) {
    if (!currency || !target) {
        //std::cerr << "Currency or Target is nullptr." << std::endl;
        return false;
    }

    itemRarities targetedRarity = currency->getRarity(); // Raritatea pe care o așteaptă moneda de la item
    itemRarities currentItemRarity = target->get_current_rarity();

    // Exceptie pentru Scouring Orb sau Annulment Orb care pot functiona pe ANY
    if (targetedRarity != ANY && targetedRarity != currentItemRarity) {
        // std::cout << "Currency " << currency->get_name()
        //           << " targets " << itemRaritiesToString.at(targetedRarity)
        //           << " items, but item is " << itemRaritiesToString.at(currentItemRarity) << std::endl;
        return false;
    }

    auto it = strategies.find(currency->getCurrencyType());
    if (it == strategies.end() || !(it->second)) {
        std::cerr << "No strategy found for currency type: " << currency->getCurrencyType() << std::endl;
        return false; // Nu există strategie pentru acest tip de monedă
    }

    ICurrencyEffectStrategy* strategy = it->second.get();

    // 3. Aplică strategia
    bool success = strategy->applyEffect(target, currency);

    if (success) {
        // std::cout << currency->get_name() << " successfully used on " << target->get_name() << std::endl;
        // Aici ai putea, de exemplu, să elimini moneda din inventarul jucătorului dacă operațiunea a reușit.
    } else {
        // std::cout << "Failed to use " << currency->get_name() << " on " << target->get_name() << std::endl;
    }

    return success;
}

CurrencyProcessor::~CurrencyProcessor() = default;