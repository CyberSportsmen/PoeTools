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

std::size_t hash_value(const Currency &obj) {
    std::size_t seed = 0x3AADE70D;
    seed ^= (seed << 6) + (seed >> 2) + 0x73586A73 + hash_value(static_cast<const Item &>(obj));
    seed ^= (seed << 6) + (seed >> 2) + 0x7D0A2F7A + static_cast<std::size_t>(obj.targetRarity);
    seed ^= (seed << 6) + (seed >> 2) + 0x7810A410 + static_cast<std::size_t>(obj.currencyType);
    return seed;
}