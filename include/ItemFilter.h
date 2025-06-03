//
// Created by Alex on 03/06/2025.
//

#ifndef ITEMFILTER_H
#define ITEMFILTER_H

#include <vector>
#include "Item.h"

class Currency;
class Equipment;

template <typename TargetType>
class ItemFilter {
public:
    static std::vector<TargetType*> filter(const std::vector<Item*>& sourceItems) {
        std::vector<TargetType*> result;
        for (Item* itemPtr : sourceItems) {
            if (itemPtr) { // pointer is not null
                if (auto* specificItem = dynamic_cast<TargetType*>(itemPtr)) {
                    result.push_back(specificItem);
                }
            }
        }
        return result;
    }
};

#endif // ITEMFILTER_H