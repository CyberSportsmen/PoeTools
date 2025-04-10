//
// Created by Alex on 10 Apr 2025.
//
#pragma once

#include "../include/ModPool.h"
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
void ModPool::addWeightedMod(unsigned int weight, const Mod& mod) { weights[weight] = mod; }

[[maybe_unused]] bool ModPool::removeAffix(const Mod& mod) {
    auto it = std::ranges::find(affixes, mod);
    if(it != affixes.end()){
        affixes.erase(it);
        return true;
    }
    return false;
}

//sterge un prefix, daca exista
[[maybe_unused]]bool ModPool::removePrefix(const Mod& mod) {
    auto it = std::ranges::find(prefixes, mod);
    if(it != prefixes.end()){
        prefixes.erase(it);
        return true;
    }
    return false;
}

[[maybe_unused]]bool ModPool::removeSuffix(const Mod& mod) {
    auto it = std::ranges::find(suffixes, mod);
    if(it != suffixes.end()){
        suffixes.erase(it);
        return true;
    }
    return false;
}