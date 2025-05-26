//
// Created by Alex on 27/05/2025.
//

#ifndef ICURRENCYEFFECTSTRATEGY_H
#define ICURRENCYEFFECTSTRATEGY_H

class Equipment;
class Currency;

class ICurrencyEffectStrategy {
public:
    virtual ~ICurrencyEffectStrategy() = default;
    virtual bool applyEffect(Equipment* target, Currency* currency) = 0;
};

#endif //ICURRENCYEFFECTSTRATEGY_H
