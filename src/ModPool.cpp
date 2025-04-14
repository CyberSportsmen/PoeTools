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

void ModPool::addPrefix(const Mod& mod) { prefixes.push_back(mod); }
void ModPool::addSuffix(const Mod& mod) { suffixes.push_back(mod); }
void ModPool::addAffix(const Mod& mod) { affixes.push_back(mod); }

[[nodiscard]] const std::vector<Mod>& ModPool::getPrefixes() const
{ return prefixes; }

[[nodiscard]] const std::vector<Mod>& ModPool::getSuffixes() const
{ return suffixes; }

// FIXME: completely wrong logic.
void ModPool::addWeightedMod(unsigned int weight, const Mod& mod)
{
    weights[weight] = mod;
}

[[maybe_unused]] bool ModPool::removeAffix(const Mod& mod) {
    if(const auto it = std::ranges::find(affixes, mod); it != affixes.end()){
        affixes.erase(it);
        return true;
    }
    return false;
}

//sterge un prefix, daca exista
[[maybe_unused]]bool ModPool::removePrefix(const Mod& mod) {
    if(const auto it = std::ranges::find(prefixes, mod); it != prefixes.end()){
        prefixes.erase(it);
        return true;
    }
    return false;
}

[[maybe_unused]]bool ModPool::removeSuffix(const Mod& mod) {
    if(const auto it = std::ranges::find(suffixes, mod); it != suffixes.end()){
        suffixes.erase(it);
        return true;
    }
    return false;
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