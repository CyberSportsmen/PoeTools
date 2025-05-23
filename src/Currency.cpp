//
// Created by Alex on 04/05/2025.
//
#include "../include/Currency.h"

#include "../include/Equipment.h"
#include "../include/Errors.h"

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

Item* Currency::clone() const {
    Currency* newCurrency = new Currency(*this); // Create a copy
    newCurrency->unique_id = ++item_count; // Assign a new unique ID
    return newCurrency;
}

// void Currency::use_item() override {
//     // can only use an item if
//     // 1. the item is selected (rmb)
//     // 2. the item that is under the mouse when we press lmb (to use the currency) is an equipment type
//     // check which type of currency we are dealing with
//     Item* target_item = get_item_under_rmb();
//     auto target_equipment = dynamic_cast<Equipment*>(target_item);
//     if (target_equipment == nullptr) {
//         // throw CraftingError(this->get_name() + " used with " + target_item->get_name(), "Target item is not an equipment type!");
//         return;
//     }
//     // we can craft
//     switch (getCurrencyType()) {
//         case CHAOS:
//             use_chaos_orb(target_item);
//             break;
//         case TRANSMUTATION:
//             use_transmutation_orb();
//             break;
//         case ALCHEMY:
//             use_alchemy_orb();
//             break;
//         case SCOURING:
//             use_scouring_orb();
//             break;
//         case EXALTED:
//             user_exalted_orb();
//             break;
//         case ANNULMENT:
//             use_annulment_orb();
//             break;
//     }
//
// }
