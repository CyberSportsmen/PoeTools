#include <iostream>
#include <chrono>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include "include/Inventory.h"
#include "include/Item.h"
#include "utils/enumerators.h"
#include "include/Mod.h"
#include "include/ModPool.h"
#include "include/CraftingBench.h"

//-----------------------------------------------------------------
// main function
//-----------------------------------------------------------------
int main() {
    // 2 iteme, o sabie si un chaos orb
    Item sword("Sword", "A sharp blade", EQUIPMENT, MAGIC, 20, 83, 2, 3, 1, 1, 3, 1);
    Item Chaos_Orb("Chaos Orb", "Reforges a rare item with new random properties", CURRENCY, NO_RARITY, 0, 0, 1, 1, 20, 1, 0, 0);

    Inventory inventory;
    inventory.place_item(Chaos_Orb);
    inventory.place_item(sword);
    inventory.place_item(Chaos_Orb); // Ar trebui sa fie stackabile
    inventory.print_inventory();

    // Creez ModPool
    ModPool modPool;
    modPool.addPrefix(Mod("IncPhyDmg", "Increased Physical Damage", 1));
    modPool.addPrefix(Mod("AddFirDmg", "Adds Fire Damage", 2));
    modPool.addPrefix(Mod("IncAtkSpd", "Increased Attack Speed", 2));

    modPool.addSuffix(Mod("IncLife", "Increased Life", 1));
    modPool.addSuffix(Mod("IncEva", "Increased Evasion Rating", 1));
    modPool.addSuffix(Mod("IncCrit", "Increased Critical Strike Chance", 3));

    modPool.addAffix(Mod("PhysCrit", "Increased Physical Damage and Critical Strike Chance", 3));

    modPool.addWeightedMod(10, Mod("IncPhyDmg", "Increased Physical Damage", 1));
    modPool.addWeightedMod(15, Mod("IncLife", "Increased Life", 1));
    modPool.addWeightedMod(20, Mod("IncCrit", "Increased Critical Strike Chance", 3));

    std::cout << modPool << "\n";
    // ModPool showcase
    // std::cout << "\nPrefix Mods:" << std::endl;
    // for (const auto& mod : modPool.getPrefixes())
    // {
    //     std::cout << " - " << mod.getShortName() << ": " << mod.getLongName()
    //               << " (Tier " << mod.getTier() << ")" << std::endl;
    // }
    //
    // std::cout << "\nSuffix Mods:" << std::endl;
    // for (const auto& mod : modPool.getSuffixes())
    // {
    //     std::cout << " - " << mod.getShortName() << ": " << mod.getLongName()
    //               << " (Tier " << mod.getTier() << ")" << std::endl;
    // }
    //
    // std::cout << "\nWeighted Mods:" << std::endl;
    // for (const auto& entry : modPool.getWeights())
    // {
    //     const auto& mod = entry.second;
    //     std::cout << "Weight " << entry.first << " -> " << mod.getShortName() << ": "
    //               << mod.getLongName() << " (Tier " << mod.getTier() << ")" << std::endl;
    // }

    // // Cream un craftingbench
    // CraftingBench bench;
    // bench.addModToBenchPool(Mod("ExtraCrit", "Extra Critical Strike Chance", 2));
    // bench.listBenchMods();
    //
    // // Adaugam un mod pe o arma
    // CraftingBench::addModToWeapon(sword, Mod("IncPhyDmg", "Increased Physical Damage", 1));
    // // Stergem un mod de pe o arma
    // bench.removeModFromWeapon(sword, Mod("IncPhyDmg", "Increased Physical Damage", 1));
    // std::cout << inventory << std::endl;
    // std::cout << sword << std::endl;
    // std::cout << "\nProgram execution finished.\n";
    //
    // Mod k{};
    // ModPool m{};
    // m.addAffix(k);
    // m.removeAffix(k);
    return 0;
}
