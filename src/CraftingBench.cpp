//
// Created by Alex on 10 Apr 2025.
//

#include "../include/CraftingBench.h"

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
            std::cout << "Could not remove Mod " << mod.getShortName() << " from Equipment " << target.get_name() << std::endl;
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
            std::cout << "Could not remove Mod " << mod.getShortName() << " from Equipment " << target.get_name() << std::endl;
            return false;
        }
    }
    std::cout << "Mod " << mod.getShortName() << " not found on weapon " << target.get_name() << std::endl;
    return false;
}
