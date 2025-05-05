#include <iostream>
#include <string>
#include "include/Inventory.h"
#include "include/Item.h"
#include "utils/enumerators.h"
#include "include/CraftingBench.h"
#include "include/Currency.h"
#include "utils/CurrencyTable.h"
//-----------------------------------------------------------------
// TODO: ask about WinMain
// main function, will probably be made singleton
//-----------------------------------------------------------------
int main() {
    srand(time(0));
    // Creez ModPool
    ModPool modPool;
    modPool.addPrefix(Mod("IncPhyDmg", "Increased Physical Damage", 1));
    modPool.addPrefix(Mod("AddFirDmg", "Adds Fire Damage", 2));
    modPool.addPrefix(Mod("IncAtkSpd", "Increased Attack Speed", 2));

    modPool.addSuffix(Mod("IncLife", "Increased Life", 1));
    modPool.addSuffix(Mod("IncEva", "Increased Evasion Rating", 1));
    modPool.addSuffix(Mod("IncCrit", "Increased Critical Strike Chance", 3));


    Item *Sword = new Equipment(20, WEAPON, RARE, "Sword", "sabiuta care taie foarte tare si bine", 2, 6, 6, 4, modPool);
    //Item Chaos_Orb("Chaos Orb", "Reforges a rare item with new random properties", CURRENCY, 1, 1, 20, 0, 0);
    //Item *chaos_orb = new Currency(RARE, CHAOS, "Chaos Orb", "Reforges a rare item with new random properties");
    Item * chaos_orb = CurrencyTable::GetOrb(CHAOS);
    Item * transmutation_orb = CurrencyTable::GetOrb(TRANSMUTATION);
    Inventory inventory;
    inventory.place_item(*chaos_orb);
    inventory.place_item(*Sword);
    inventory.place_item(*transmutation_orb);
    inventory.place_item(*chaos_orb); // Ar trebui sa fie stackabile
    //inventory.place_item(*alchemy_orb);
    chaos_orb = CurrencyTable::GetOrb(CHAOS);
    inventory.print_inventory();
    Equipment* sw = dynamic_cast<Equipment*>(Sword);
    //sw->addPrefix(Mod("IncPhyDmg", "Increased Physical Damage", 1));
    //CraftingBench::addModToEquipment(*sw, Mod("IncPhyDmg", "Increased Physical Damage", 1));
    //CraftingBench::addModToEquipment(*sw, Mod("IncCrit", "Increased Critical Strike Chance", 3));
    CraftingBench::addRandomModToEquipment(*sw);
    CraftingBench::addRandomModToEquipment(*sw);
    CraftingBench::addRandomModToEquipment(*sw);
    CraftingBench::addRandomModToEquipment(*sw);
    CraftingBench::addRandomModToEquipment(*sw);
    CraftingBench::addRandomModToEquipment(*sw);
    std::cout << *sw << '\n';
    //CraftingBench::removeAllModsFromEquipment(*sw);
    CraftingBench::removeRandomModFromEquipment(*sw);
    CraftingBench::removeRandomModFromEquipment(*sw);
    CraftingBench::removeRandomModFromEquipment(*sw);
    CraftingBench::removeRandomModFromEquipment(*sw);
    CraftingBench::removeRandomModFromEquipment(*sw);
    CraftingBench::removeRandomModFromEquipment(*sw);
    CraftingBench::removeRandomModFromEquipment(*sw);
    std::cout << *sw << '\n';

    // std::cout << modPool << "\n";
    return 0;
}
