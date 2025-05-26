#include <iostream>
#include <string>

#include "include/ErrorHandler.h"
#include "ResourceManager.hpp"
#include "include/Inventory.h"
#include "include/Item.h"
#include "utils/enumerators.h"
#include "include/CraftingBench.h"
#include "include/CurrencyProcessor.h"
#include "utils/CurrencyTable.h"
#include "include/Player.h"
//-----------------------------------------------------------------
// TODO: ask about WinMain
// main function, will probably be made singleton
//-----------------------------------------------------------------


void test_currency_processor() {
    // NEVER EVER USE AN EMPTY MODPOOL!
    ModPool basicModPool; // Un ModPool gol sau cu câteva moduri de test
    basicModPool.addPrefix(Mod("IncPhyDmg", "Increased Physical Damage", 1));
    basicModPool.addPrefix(Mod("AddFirDmg", "Adds Fire Damage", 2));
    basicModPool.addPrefix(Mod("IncAtkSpd", "Increased Attack Speed", 3));
    basicModPool.addSuffix(Mod("IncLife", "Increased Life", 1));
    basicModPool.addSuffix(Mod("IncEva", "Increased Evasion Rating", 1));
    basicModPool.addSuffix(Mod("IncCrit", "Increased Critical Strike Chance", 3));

    auto* sword = new Equipment(0, WEAPON, NORMAL, "Basic Sword", "A simple sword.", 1, 3, 0, 0, basicModPool);

    auto* transmuteOrb = dynamic_cast<Currency*>(CurrencyTable::GetOrb(TRANSMUTATION)); // Clonezi pentru a avea o instanță unică

    CurrencyProcessor processor;

    std::cout << "Sword before transmutation: Rarity " << itemRaritiesToString.at(sword->get_current_rarity()) << std::endl;
    std::cout << *sword << std::endl;

    // Folosește moneda pe item
    bool result = processor.use_currency(transmuteOrb, sword);
    if (result) {
        std::cout << "Sword after transmutation: Rarity " << itemRaritiesToString.at(sword->get_current_rarity()) << std::endl;
        std::cout << *sword << std::endl;
    } else {
        std::cout << "Failed to apply Transmutation Orb." << std::endl;
    }

    delete sword;
    delete transmuteOrb;
}

void work() {
    // Creez ModPool
    ModPool modPool;
    modPool.addPrefix(Mod("IncPhyDmg", "Increased Physical Damage", 1));
    modPool.addPrefix(Mod("AddFirDmg", "Adds Fire Damage", 2));
    modPool.addPrefix(Mod("IncAtkSpd", "Increased Attack Speed", 2));

    modPool.addSuffix(Mod("IncLife", "Increased Life", 1));
    modPool.addSuffix(Mod("IncEva", "Increased Evasion Rating", 1));
    modPool.addSuffix(Mod("IncCrit", "Increased Critical Strike Chance", 3));


    //Item Chaos_Orb("Chaos Orb", "Reforges a rare item with new random properties", CURRENCY, 1, 1, 20, 0, 0);
    //Item *chaos_orb = new Currency(RARE, CHAOS, "Chaos Orb", "Reforges a rare item with new random properties");
    Item *Sword = new Equipment(20, WEAPON, RARE, "Sword", "sabiuta care taie foarte tare si bine", 2, 6, 6, 4, modPool);
    Inventory inventory;
    inventory.place_item(*Sword);

    auto* sw = dynamic_cast<Equipment*>(Sword);
    CraftingBench::addRandomModToEquipment(*sw);
    CraftingBench::addRandomModToEquipment(*sw);

    inventory.clear();
    inventory.place_item(*Sword);


    Player::get_instance();
    Player::get_instance().set_inventory(&inventory);
    Player::get_instance().get_inventory()->place_item(*Sword);
    Player::get_instance().get_inventory()->print_inventory();
    auto *item_selectat = Player::get_instance().get_inventory()->get_item(2, 1);
    Player::get_instance().select_item(item_selectat);
    std::cout << *dynamic_cast<Equipment*>(item_selectat) << '\n';

    test_currency_processor();
}

int main() {
    ErrorHandler::initLog("PoeTools.log");
    try {
        // NU mai este nevoie de nicio linie aici pentru ResourceManager
        // Instanța ResourceManager va fi creata
        work();
    }
    catch (const std::exception& e) {
        ErrorHandler::handle(e, "main");
        return EXIT_FAILURE;
    }
    ErrorHandler::shutdown();
    return EXIT_SUCCESS;
}
