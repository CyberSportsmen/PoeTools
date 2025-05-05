//
// Created by Alex on 10 Apr 2025.
//
#include "../include/ModPool.h"

#include <ostream>

#include "../include/Mod.h"

[[nodiscard]] const std::vector<Mod>& ModPool::getAffixes() const
{
    return affixes;
}
[[nodiscard]]const std::map<unsigned int, Mod>& ModPool::getWeights() const
{ return weights; }

void ModPool::addAffix(const Mod& mod) { affixes.push_back(mod); }

void ModPool::addPrefix(const Mod& mod) { prefixes.push_back(mod); addAffix(mod); }
void ModPool::addSuffix(const Mod& mod) { suffixes.push_back(mod); addAffix(mod); }

[[nodiscard]] const std::vector<Mod>& ModPool::getPrefixes() const
{ return prefixes; }

[[nodiscard]] const std::vector<Mod>& ModPool::getSuffixes() const
{ return suffixes; }

// FIXME: completely wrong logic.
void ModPool::addWeightedMod(unsigned int weight, const Mod& mod)
{
    weights[weight] = mod;
}

[[maybe_unused]] void ModPool::removeAffix(const Mod& mod) {
    std::vector<Mod> newAffixes;
    for (auto w : affixes) {
        if (w != mod) {
            newAffixes.push_back(w);
        }
    }
    affixes = newAffixes;
}

//sterge un prefix, daca exista
[[maybe_unused]]void ModPool::removePrefix(const Mod& mod) {
    std::vector<Mod> newPrefixes;
    for (auto w : prefixes) {
        if (w != mod) {
            newPrefixes.push_back(w);
        }
    }
    prefixes = newPrefixes;
    removeAffix(mod);
}

[[maybe_unused]]void ModPool::removeSuffix(const Mod& mod) {
    std::vector<Mod> newSuffixes;
    for (auto w : suffixes) {
        if (w != mod) {
            newSuffixes.push_back(w);
        }
    }
    suffixes = newSuffixes;
    removeAffix(mod);
}
std::ostream& operator<<(std::ostream& os, const ModPool& modPool)
{
    os << "Prefixes:" << std::endl;
    for (const auto& mod : modPool.getPrefixes())
        os << mod << std::endl;
    os << "Suffixes:" << std::endl;
    for (const auto& mod : modPool.getSuffixes())
        os << mod << std::endl;
    os << "Weights:" << std::endl;
    for (const auto& mod : modPool.getWeights())
        os << "Weight: " << mod.first << "\n" << mod.second << std::endl;
    return os;
}