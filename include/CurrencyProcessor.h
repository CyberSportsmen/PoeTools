//
// Created by Alex on 27/05/2025.
//

#ifndef CURRENCYPROCESSOR_H
#define CURRENCYPROCESSOR_H

#include <map>
#include <memory>
#include "../utils/enumerators.h" // Pentru currencyTypes

// Forward declarații
class ICurrencyEffectStrategy;
class Currency;
class Equipment;

class CurrencyProcessor {
private:
    std::map<currencyTypes, std::unique_ptr<ICurrencyEffectStrategy>> strategies;

    void registerStrategies(); // Metodă privată pentru a încărca strategiile

public:
    CurrencyProcessor();
    ~CurrencyProcessor(); // unique_ptr se va ocupa de memorie

    // Funcția pe care o vei folosi
    bool use_currency(Currency* currency, Equipment* target);
};

#endif //CURRENCYPROCESSOR_H
