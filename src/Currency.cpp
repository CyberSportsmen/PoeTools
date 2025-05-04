//
// Created by Alex on 04/05/2025.
//
#include "../include/Currency.h"

bool operator!=(const Currency &lhs, const Currency &rhs) {
    return !(lhs == rhs);
}

bool operator==(const Currency &lhs, const Currency &rhs) {
    return static_cast<const Item &>(lhs) == static_cast<const Item &>(rhs)
           && lhs.targetRarity == rhs.targetRarity
           && lhs.currencyType == rhs.currencyType;
}

