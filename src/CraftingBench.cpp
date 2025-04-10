//
// Created by Alex on 10 Apr 2025.
//

#pragma once

#include "../include/CraftingBench.h"

void CraftingBench::addModToBenchPool(const Mod& mod)
{
    benchPool.addAffix(mod);
}

[[maybe_unused]]bool CraftingBench::removeModFromBenchPool(const Mod& mod)
{
    return benchPool.removeAffix(mod);
}

bool CraftingBench::addModToWeapon(Item& weapon, const Mod& mod)
{
    // FIXME: FLIP A COIN TO CHOOSE PREFIX/SUFFIX (ish), THEN USE AUXILIARY FUNCTION
    std::vector<Mod> mods = weapon.get_affixes();
    if (const unsigned int allowed = weapon.get_maxPrefixes() + weapon.get_maxSuffixes(); mods.size() < allowed)
    {
        mods.push_back(mod);
        weapon.set_affixes(mods);
        std::cout << "Added mod " << mod.getShortName() << " to weapon " << weapon.get_name() << std::endl;
        return true;
    }
    std::cout << "Cannot add more mods to " << weapon.get_name() << std::endl;
    return false;
}

bool CraftingBench::removeModFromWeapon(Item& weapon, const Mod& mod)
{
    std::vector<Mod> mods = weapon.get_affixes();
    if (const auto it = std::ranges::find(mods, mod); it != mods.end())
    {
        mods.erase(it);
        weapon.set_affixes(mods);
        std::cout << "Removed mod " << mod.getShortName() << " from weapon " << weapon.get_name() << std::endl;
        // adaugă inapoi in benchPool (optional)
        benchPool.addAffix(mod);
        return true;
    }
    std::cout << "Mod " << mod.getShortName() << " not found on weapon " << weapon.get_name() << std::endl;
    return false;
}

void CraftingBench::listBenchMods() const
{
    std::cout << "Bench Affix Mods:" << std::endl;
    for (const auto& mod : benchPool.getAffixes())
    {
        std::cout << " - " << mod.getShortName() << ": " << mod.getLongName()
                  << " (Tier " << mod.getTier() << ")" << std::endl;
    }
}