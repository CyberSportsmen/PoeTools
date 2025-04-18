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
// TODO: ask about WinMain
// main function, will probably be made singleton
//-----------------------------------------------------------------
int main() {
    // 2 iteme, o sabie si un chaos orb
    //TODO: CREATE A STRUCT THAT CONTAINS AND INITIALISES ALL CURRENCY ITEMS IN THE GAME
    Item sword("Sword", "A sharp blade", EQUIPMENT, 2, 5, 1, 6, 5);
    Item Chaos_Orb("Chaos Orb", "Reforges a rare item with new random properties", CURRENCY, 1, 1, 20, 0, 0);

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

    // std::cout << modPool << "\n";
    return 0;
}
