//
// Created by Alex on 10 Apr 2025.
//

#include "../include/CraftingBench.h"
#include <vector>      // for std::vector
#include <algorithm>   // for std::find
#include <iostream>
// TODO: change Item& weapon to Weapon& weapon after creating child class EVERYWHERE where Item is in CraftingBench Class
// STATUS: in progress

// bool CraftingBench::addModToWeapon(Item& weapon, const Mod& mod)
// {
//     // FIXME: FLIP A COIN TO CHOOSE PREFIX/SUFFIX (ish), THEN USE AUXILIARY FUNCTION
//     std::vector<Mod> mods = weapon.get_affixes();
//     if (const unsigned int allowed = weapon.get_maxPrefixes() + weapon.get_maxSuffixes(); mods.size() < allowed)
//     {
//         mods.push_back(mod);
//         weapon.set_affixes(mods);
//         std::cout << "Added mod " << mod.getShortName() << " to weapon " << weapon.get_name() << std::endl;
//         return true;
//     }
//     std::cout << "Cannot add more mods to " << weapon.get_name() << std::endl;
//     return false;
// }

//searches through target's suffixes and prefixes and removes a mod, if found

[[maybe_unused]] bool CraftingBench::addModToEquipment(Equipment& target, const Mod& mod) {
    bool canBeAdded = false;
    for (const auto& modPoolMod : target.getModPool().getAffixes()) {
        if (mod == modPoolMod)
            canBeAdded = true;
        // mod is from modpool so it can be added
    }
    if (!canBeAdded)
        return false;
    // the mod is in the modpool
    // search wether it is a prefix or suffix
    bool isPrefix = false;
    for (const auto& modPoolMod : target.getModPool().getPrefixes()) {
        if (mod == modPoolMod)
            isPrefix = true;
    }
    if (isPrefix) {
        // it is a prefix
        // check if it has space to be placed
        switch (target.get_current_rarity()) {
            case NORMAL:
                return false;
            case MAGIC:
                if (target.getCurrentPrefixes().size() >= 2)
                    return false;
                break;
            case RARE:
                if (target.getCurrentPrefixes().size() >= 3)
                    return false;
                break;
            default:
                return false;
        }
        // add the prefix, since we can
        target.addPrefix(mod);
        return true;
    }
    bool isSuffix = false;
    for (const auto& modPoolMod : target.getModPool().getSuffixes()) {
        if (mod == modPoolMod)
            isSuffix = true;
    }
    if (isSuffix) {
        // it is a prefix
        switch (target.get_current_rarity()) {
            case NORMAL:
                return false;
            case MAGIC:
                if (target.getCurrentSuffixes().size() >= 2)
                    return false;
                break;
            case RARE:
                if (target.getCurrentSuffixes().size() >= 3)
                    return false;
                break;
            default:
                return false;
        }
        target.addSuffix(mod);
        return true;
    }
    // should be in affixes though
    return false;
}

bool CraftingBench::removeModFromEquipment(Equipment& target, const Mod& mod)
{
    std::vector<Mod> prefixes = target.getCurrentPrefixes();
    std::vector<Mod> suffixes = target.getCurrentSuffixes();
    if (const auto it = std::ranges::find(prefixes, mod); it != prefixes.end())
    {
        try
        {
            prefixes.erase(it);
            target.setPrefixes(prefixes);
            std::cout << "Removed mod " << mod.getShortName() << " from weapon " << target.get_name() << std::endl;
            return true;
        }
        catch (const std::exception& e)
        {
            std::cout << "Could not remove prefix " << mod.getShortName() << " from Equipment " << target.get_name() << std::endl;
            std::cout << e.what() << std::endl;
            return false;
        }
    }
    if (const auto it = std::ranges::find(suffixes, mod); it != suffixes.end())
    {
        try
        {
            suffixes.erase(it);
            target.setSuffixes(suffixes);
            std::cout << "Removed mod " << mod.getShortName() << " from weapon " << target.get_name() << std::endl;
            return true;
        }
        catch (const std::exception& e)
        {
            std::cout << "Could not remove suffix " << mod.getShortName() << " from Equipment " << target.get_name() << std::endl;
            std::cout << e.what() << std::endl;
            return false;
        }
    }
    std::cout << "Mod " << mod.getShortName() << " not found on weapon " << target.get_name() << std::endl;
    return false;
}
