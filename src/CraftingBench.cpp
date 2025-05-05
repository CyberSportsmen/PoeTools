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
    // search if it is a prefix or suffix
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
                if (!target.getCurrentPrefixes().empty())
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
        // it is a suffix
        switch (target.get_current_rarity()) {
            case NORMAL:
                return false;
            case MAGIC:
                if (!target.getCurrentSuffixes().empty())
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
    return false; // problem with program
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
// DEPRICATED, should not use at all, but is faster
bool CraftingBench::addPrefixToEquipment(Equipment& target, const Mod& mod) {
    // verificam daca avem loc
    auto targPref = target.getCurrentPrefixes();
    auto rarity = target.get_current_rarity();
    if (rarity == RARE && targPref.size() >= 3)
        return false;
    if (rarity == MAGIC && !targPref.empty())
        return false;
    if (rarity != RARE && rarity != MAGIC)
        return false;
    // putem adauga fara probleme
    targPref.push_back(mod);
    target.setPrefixes(targPref);
    return true;
}
// DEPRICATED, should not use at all, but is faster;
bool CraftingBench::addSuffixToEquipment(Equipment& target, const Mod& mod) {
    // verificam daca avem loc
    auto targSuf = target.getCurrentSuffixes();
    auto rarity = target.get_current_rarity();
    if (rarity == RARE && targSuf.size() >= 3)
        return false;
    if (rarity == MAGIC && !targSuf.empty())
        return false;
    if (rarity != RARE && rarity != MAGIC)
        return false;
    // putem adauga fara probleme
    targSuf.push_back(mod);
    target.setSuffixes(targSuf);
    return true;
}

bool CraftingBench::addRandomModToEquipment(Equipment& target) {
    auto targetpool = target.getModPool();
    auto sufixpool = targetpool.getSuffixes();
    auto prefixpool = targetpool.getPrefixes();
    auto rarity = target.get_current_rarity();
    int suffxnr = target.getCurrentSuffixes().size();
    int prefixnr = target.getCurrentPrefixes().size();
    int slotsavailable;
    if (rarity == RARE)
        slotsavailable = 6;
    else if (rarity == MAGIC)
        slotsavailable = 2;
    else
        slotsavailable = 0;
    slotsavailable -= suffxnr + prefixnr;
    if (slotsavailable <= 0)
        return false;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    int which = 2; // 0 for prefix, 1 for suffix
    if (suffxnr > 0 && prefixnr > 0) {
        // flip a coin if we add a prefix or a suffix
        which = dist(gen);
    }
    else if (suffxnr > 0)
        which = 1;
    else which = 0;
    if (which == 2)
        return false;
    if (which == 0)
    {
        // add a random prefix;
        auto mod = sufixpool[rand() % sufixpool.size()];
        addModToEquipment(target, mod); // should work
    }
    else {
        // add a random suffix
        auto mod = prefixpool[rand() % prefixpool.size()];
        addModToEquipment(target, mod);
    }
    return true;
}

void CraftingBench::removeAllModFromEquipment(Equipment& target) {
    // TODO: for scouring orb also modify rarity of item.
    target.setPrefixes(std::vector<Mod>{});
    target.setSuffixes(std::vector<Mod>{});
}
bool CraftingBench::removeRandomModFromEquipment(Equipment& target, const Mod& mod) {
    return false;
}

