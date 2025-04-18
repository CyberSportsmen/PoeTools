//
// Created by Alex on 18 Apr 2025.
//

#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"
#include "../utils/enumerators.h"
#include "Mod.h"
#include "ModPool.h"

class Equipment : public Item
{
private:
    unsigned int quality;
    itemTypes type = EQUIPMENT;
    itemRarities rarity;
    std::vector<Mod> suffixes;
    std::vector<Mod> prefixes;
    std::vector<Mod> implicits;
    // Atentie mare, cand adaugam un sufix, prefix !
    // TODO: trebuie marcat in modpool ca fiind prezent pe item
    // astfel incat sa nu afectam outcome-ul craft-urilor sau
    // sa avem dubluri de mod-uri!!
    // TODO: acest lucru se va verifica in clasa CraftingBench!
    ModPool pool; // de aici stim pentru fiecare item ce mod-uri poate primi
public:
    Equipment();
    Equipment(unsigned int quality, itemTypes type, itemRarities rarity);
    ~Equipment() = default;
    // getters
    ModPool& getModPool() { return pool; }
    std::vector<Mod>& getCurrentPrefixes(){return prefixes;}
    std::vector<Mod>& getCurrentSuffixes(){return suffixes;}
    std::vector<Mod>& getCurrentImplicits(){return implicits;}
    void setQuality(unsigned int quality);
    void setPrefixes(const std::vector<Mod>& prefixes);
    void setSuffixes(const std::vector<Mod>& suffixes);
    void setImplicits(const std::vector<Mod>& implicits);
};

#endif //EQUIPMENT_H
