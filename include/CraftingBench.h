//
// Created by Alex on 10 Apr 2025.
//

#ifndef CRAFTINGBENCH_H
#define CRAFTINGBENCH_H

#include <random>
#include <ctime>
#include "Equipment.h"

//-----------------------------------------------------------------
// CraftingBench
// This class simulates a bench that can add or remove mods from a weapon's mod pool.
// TODOD: This should and will be made a struct
//-----------------------------------------------------------------
struct CraftingBench
{
    CraftingBench() = delete;
    ~CraftingBench() = delete;
    // Adaugă un mod, daca are loc
    static bool addModToEquipment(Equipment& target, const Mod& mod);
    static bool removeModFromEquipment(Equipment& target, const Mod& mod);
    static bool addPrefixToEquipment(Equipment& target, const Mod& mod);
    static bool addSuffixToEquipment(Equipment& target, const Mod& mod);
    static bool addRandomModToEquipment(Equipment& target);
    static void removeAllModFromEquipment(Equipment& target);
    static bool removeRandomModFromEquipment(Equipment& target, const Mod& mod);
};

#endif //CRAFTINGBENCH_H
