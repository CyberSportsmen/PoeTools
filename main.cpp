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
#include "include/ItemFilter.h"
#include "include/InventoryActions.h"
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

void test_domain_specific_templates() {
    std::cout << "\n--- Testing Template Features ---\n";

    Player& player = Player::get_instance();
    Inventory* pInventory = player.get_inventory();
    if (!pInventory) { // Ensure inventory exists
        pInventory = new Inventory();
        player.set_inventory(pInventory);
    }
    pInventory->clear(); // Clear for a predictable test state

    // Setup: Add a few items to the inventory for testing
    ModPool emptyPool; // Simple pool for test equipment
    // Note: Inventory::place_item(const Item&) clones the item.
    // CurrencyTable::GetOrb returns Item*, need to cast and then it will be cloned.
    pInventory->place_item(*dynamic_cast<Currency*>(CurrencyTable::GetOrb(TRANSMUTATION)->clone()));
    pInventory->place_item(*Equipment(0, WEAPON, NORMAL, "Test Sword", "desc", 1, 2, 0,0, emptyPool).clone());
    pInventory->place_item(*dynamic_cast<Currency*>(CurrencyTable::GetOrb(ALCHEMY)->clone()));
    pInventory->place_item(*Equipment(0, HELMET, MAGIC, "Test Helm", "desc", 2, 2, 0,0, emptyPool).clone());

    // --- 1. Test ItemFilter<TargetType> ---
    // gather all actual item pointers from inventory
    std::cout << "\nGathering items from inventory for ItemFilter test (get_item will print):\n";
    std::vector<Item*> allRawItemsInInventory;
    std::vector<unsigned int> processed_ids; // To handle multi-slot items correctly once
    for (unsigned int r = 0; r < 6; ++r) {
        for (unsigned int c = 0; c < 10; ++c) {
            Item* item = pInventory->get_item(r, c);
            if (item && item->get_name() != "emptySlot") {
                bool found = false;
                for(unsigned int id : processed_ids) if(id == item->get_unique_id()) found = true;
                if(!found){
                    allRawItemsInInventory.push_back(item);
                    processed_ids.push_back(item->get_unique_id());
                }
            }
        }
    }
    std::cout << "Total distinct items gathered: " << allRawItemsInInventory.size() << std::endl;


    // Instantiate ItemFilter for Currency
    std::vector<Currency*> currencyItems = ItemFilter<Currency>::filter(allRawItemsInInventory);
    std::cout << "ItemFilter<Currency> found: " << currencyItems.size() << " items.\n";
    for(const auto* curr : currencyItems) std::cout << "  - " << curr->get_name() << std::endl;

    // Instantiate ItemFilter for Equipment
    std::vector<Equipment*> equipmentItems = ItemFilter<Equipment>::filter(allRawItemsInInventory);
    std::cout << "ItemFilter<Equipment> found: " << equipmentItems.size() << " items.\n";
    for(const auto* eq : equipmentItems) std::cout << "  - " << eq->get_name() << std::endl;

    // --- 2. Test applyToAllOfTypeInInventory<TargetItemType, Action> ---
    std::cout << "\nApplying action to increase quality of all Equipment:\n";
    // Instantiate for Equipment
    applyToAllOfTypeInInventory<Equipment>(*pInventory, [](Equipment& eq) {
        // we might get duplicates, but it is a problem for another time
        // for this demo, we'll just see the print
        std::cout << "-Processing Equipment: " << eq.get_name() << std::endl;
        // eq.setQuality(eq.getQuality() + 1); // exemplu
    });

    std::cout << "\nApplying action to log stack size of all Currency:\n";
    // Instantiate for Currency
    applyToAllOfTypeInInventory<Currency>(*pInventory, [](const Currency& curr) {
        std::cout << "-Currency: " << curr.get_name() << ", stack size: " << curr.get_current_stack_size() << std::endl;
    });

    std::cout << "\n--- Testing Template Features END ---\n";
}

int main() {
    ErrorHandler::initLog("PoeTools.log");
    try {
        // NU mai este nevoie de nicio linie aici pentru ResourceManager
        // Instanța ResourceManager va fi creata
        Player::get_instance();
        //work();
        test_domain_specific_templates();
    }
    catch (const std::exception& e) {
        ErrorHandler::handle(e, "main");
        return EXIT_FAILURE;
    }
    ErrorHandler::shutdown();
    return EXIT_SUCCESS;
}
