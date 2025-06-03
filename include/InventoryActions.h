//
// Created by Alex on 03/06/2025.
//

#ifndef INVENTORYACTIONS_H
#define INVENTORYACTIONS_H

#include "Inventory.h"
#include "Item.h"

class Equipment;
class Currency;

template <typename TargetItemType, typename Action>
void applyToAllOfTypeInInventory(Inventory& inventory, Action action) {
    for (unsigned int r = 0; r < 6; ++r) {
        for (unsigned int c = 0; c < 10; ++c) {
            if (Item* rawItemPtr = inventory.get_item(r, c); rawItemPtr && rawItemPtr->get_name() != "emptySlot") {
                auto* specificItem = dynamic_cast<TargetItemType*>(rawItemPtr);
                if (specificItem) {
                    action(*specificItem);
                }
            }
        }
    }
}

#endif // INVENTORYACTIONS_H