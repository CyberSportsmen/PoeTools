//
// Created by Alex on 10 Apr 2025.
//

#ifndef CRAFTINGBENCH_H
#define CRAFTINGBENCH_H

#include "ModPool.h"
#include "Item.h"
#include <iostream>

//-----------------------------------------------------------------
// CraftingBench Class
// This class simulates a bench that can add or remove mods from a weapon's mod pool.
//-----------------------------------------------------------------

class CraftingBench
{
    ModPool benchPool;  // Internal mod pool available on the bench.
public:
    CraftingBench() = default;
    explicit CraftingBench(ModPool  bench_pool)
        : benchPool(std::move(bench_pool))
    {
    }
    // Add a mod to the bench's pool.
    void addModToBenchPool(const Mod& mod);

    // Remove a mod from the bench's pool.
    [[maybe_unused]]bool removeModFromBenchPool(const Mod& mod);

    // Adaugă un mod, daca are loc
    static bool addModToWeapon(Item& weapon, const Mod& mod);

    bool removeModFromWeapon(Item& weapon, const Mod& mod);

    void listBenchMods() const;
};

#endif //CRAFTINGBENCH_H
