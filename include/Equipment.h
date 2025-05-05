//
// Created by Alex on 18 Apr 2025.
//

#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <utility>

#include "Item.h"
#include "../utils/enumerators.h"
#include "Mod.h"
#include "ModPool.h"

class Equipment : public Item
{
private:
    unsigned int quality;
    equipmentTypes type;
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
    explicit Equipment(unsigned int quality, equipmentTypes type, itemRarities rarity,const std::string& name, const std::string& description, unsigned int width, unsigned int height, unsigned int maxSockets, unsigned int sockets, ModPool pool) : Item(name, description, EQUIPMENT, width, height, 1, maxSockets, sockets), quality(quality), type(type), rarity(rarity), pool(std::move(pool)){};

    ~Equipment() override = default;
    // getters
    ModPool& getModPool() { return pool; }
    std::vector<Mod>& getCurrentPrefixes(){return prefixes;}
    std::vector<Mod>& getCurrentSuffixes(){return suffixes;}
    friend std::ostream& operator<<(std::ostream& os, Equipment& equipment); // outputs all the mods of an item
    void addPrefix(const Mod& mod);
    void addSuffix(const Mod& mod);
    std::vector<Mod>& getCurrentImplicits(){return implicits;}
    [[nodiscard]] itemRarities get_current_rarity() const;
    void set_rarity(itemRarities rarity);
    void setQuality(unsigned int quality);
    void setPrefixes(const std::vector<Mod>& prefixes);
    void setSuffixes(const std::vector<Mod>& suffixes);
    void setImplicits(const std::vector<Mod>& implicits);
};

#endif //EQUIPMENT_H
