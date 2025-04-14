//
// Created by Alex on 10 Apr 2025.
//

#ifndef MODPOOL_H
#define MODPOOL_H
#include "Mod.h"
#include <vector>
#include <map>

class ModPool
{
    std::vector<Mod> prefixes;
    std::vector<Mod> suffixes;
    std::map<unsigned int, Mod> weights; // Each mod has a weight for selection
    // TODO: REMOVE AFFIXES, REDUNDANT!
    std::vector<Mod> affixes; // suffix + prefix
public:
    // adaugă mod-uri

    void addPrefix(const Mod& mod);
    void addSuffix(const Mod& mod);
    void addAffix(const Mod& mod);

    // FIXME: completely wrong logic.
    void addWeightedMod(unsigned int weight, const Mod& mod);

    //sterge un prefix, daca exista
    [[maybe_unused]]bool removePrefix(const Mod& mod);
    //sterge un sufix, daca exista
    [[maybe_unused]]bool removeSuffix(const Mod& mod);
    // sterge un afix, daca exista
    [[maybe_unused]] bool removeAffix(const Mod& mod);

    [[nodiscard]] const std::vector<Mod>& getPrefixes() const; //{ return prefixes; }
    [[nodiscard]] const std::vector<Mod>& getSuffixes() const; //{ return suffixes; }
    [[nodiscard]] const std::vector<Mod>& getAffixes()  const; //{ return affixes; }
    [[nodiscard]] const std::map<unsigned int, Mod>& getWeights() const; // { return weights; }

    friend std::ostream& operator<<(std::ostream& os, const ModPool& modPool);
};
#endif //MODPOOL_H
