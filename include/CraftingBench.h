//
// Created by Alex on 10 Apr 2025.
//

#ifndef CRAFTINGBENCH_H
#define CRAFTINGBENCH_H

#include "ModPool.h"
#include "Equipment.h"
#include <iostream>

//-----------------------------------------------------------------
// CraftingBench
// This class simulates a bench that can add or remove mods from a weapon's mod pool.
// TODOD: This should and will be made a struct
//-----------------------------------------------------------------
struct CraftingBench
{
    CraftingBench() = default;
    ~CraftingBench() = default;
    // Adaugă un mod, daca are loc
    static bool addModToEquipment(Equipment& target, const Mod& mod);
    static bool removeModFromEquipment(Equipment& target, const Mod& mod);
};

#endif //CRAFTINGBENCH_H
