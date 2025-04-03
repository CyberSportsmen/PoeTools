#include <iostream>
#include <array>
#include <chrono>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>
//#include <utility>
#include "include/Inventory.h"
#include "include/Item.h"
#include "utils/enumerators.h"
#include "include/Mod.h"
#include "ResourceManager.hpp"  // Assumes a singleton resource manager for textures


// Represents a collection of mods (a mod pool) divided into different categories.
class ModPool
{
    std::vector<Mod> prefixes;
    std::vector<Mod> suffixes;
    std::vector<Mod> affixes; // suffix + prefix
    std::map<unsigned int, Mod> weights; // Each mod has a weight for selection
public:
    // addauga mod-uri
    void addPrefix(const Mod& mod) { prefixes.push_back(mod); }
    void addSuffix(const Mod& mod) { suffixes.push_back(mod); }
    void addAffix(const Mod& mod)  { affixes.push_back(mod); }
    void addWeightedMod(unsigned int weight, const Mod& mod) { weights[weight] = mod; }

    //sterge un prefix
    // [[maybe_unused]]bool removePrefix(const Mod& mod) {
    //     auto it = std::ranges::find(prefixes, mod);
    //     if(it != prefixes.end()){
    //         prefixes.erase(it);
    //         return true;
    //     }
    //     return false;
    // }
    // //sterge un sufix
    // [[maybe_unused]]bool removeSuffix(const Mod& mod) {
    //     auto it = std::ranges::find(suffixes, mod);
    //     if(it != suffixes.end()){
    //         suffixes.erase(it);
    //         return true;
    //     }
    //     return false;
    // }
    // // sterge afix
    // [[maybe_unused]] bool removeAffix(const Mod& mod) {
    //     auto it = std::ranges::find(affixes, mod);
    //     if(it != affixes.end()){
    //         affixes.erase(it);
    //         return true;
    //     }
    //     return false;
    // }

    [[nodiscard]] const std::vector<Mod>& getPrefixes() const { return prefixes; }
    [[nodiscard]] const std::vector<Mod>& getSuffixes() const { return suffixes; }
    [[nodiscard]] const std::vector<Mod>& getAffixes()  const { return affixes; }
    [[nodiscard]] const std::map<unsigned int, Mod>& getWeights() const { return weights; }
};


//-----------------------------------------------------------------
// Inventory Class (6x10 grid)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// CraftingBench Class
// This class simulates a bench that can add or remove mods from a weapon's mod pool.
//-----------------------------------------------------------------
class CraftingBench
{
    ModPool benchPool;  // Internal mod pool available on the bench.
public:
    CraftingBench() = default;

    // Add a mod to the bench's pool.
    void addModToBenchPool(const Mod& mod)
    {
        benchPool.addAffix(mod);
    }

    explicit CraftingBench(ModPool  bench_pool)
        : benchPool(std::move(bench_pool))
    {
    }

    // Remove a mod from the bench's pool.
    // [[maybe_unused]]bool removeModFromBenchPool(const Mod& mod)
    // {
    //     return benchPool.removeAffix(mod);
    // }

    // Adauga un mod, daca are loc
    static bool addModToWeapon(Item& weapon, const Mod& mod)
    {
        std::vector<Mod> mods = weapon.get_affixes();
        // TODO: DE VERIFICAT CU MAXIM SI MINIM, NU ARE VOIE SA TREACA DE LIMITA
        unsigned int allowed = weapon.get_maxPrefixes() + weapon.get_maxSuffixes();
        if (mods.size() < allowed)
        {
            mods.push_back(mod);
            weapon.set_affixes(mods);
            std::cout << "Added mod " << mod.getShortName() << " to weapon " << weapon.get_name() << std::endl;
            return true;
        }
        std::cout << "Cannot add more mods to " << weapon.get_name() << std::endl;
        return false;
    }

    bool removeModFromWeapon(Item& weapon, const Mod& mod)
    {
        std::vector<Mod> mods = weapon.get_affixes();
        auto it = std::ranges::find(mods, mod);
        if (it != mods.end())
        {
            mods.erase(it);
            weapon.set_affixes(mods);
            std::cout << "Removed mod " << mod.getShortName() << " from weapon " << weapon.get_name() << std::endl;
            // adauga inapoi in benchPool (optional)
            benchPool.addAffix(mod);
            return true;
        }
        std::cout << "Mod " << mod.getShortName() << " not found on weapon " << weapon.get_name() << std::endl;
        return false;
    }

    void listBenchMods() const
    {
        std::cout << "Bench Affix Mods:" << std::endl;
        for (const auto& mod : benchPool.getAffixes())
        {
            std::cout << " - " << mod.getShortName() << ": " << mod.getLongName()
                      << " (Tier " << mod.getTier() << ")" << std::endl;
        }
    }
};

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

    // ModPool showcase
    std::cout << "\nPrefix Mods:" << std::endl;
    for (const auto& mod : modPool.getPrefixes())
    {
        std::cout << " - " << mod.getShortName() << ": " << mod.getLongName()
                  << " (Tier " << mod.getTier() << ")" << std::endl;
    }

    std::cout << "\nSuffix Mods:" << std::endl;
    for (const auto& mod : modPool.getSuffixes())
    {
        std::cout << " - " << mod.getShortName() << ": " << mod.getLongName()
                  << " (Tier " << mod.getTier() << ")" << std::endl;
    }

    std::cout << "\nWeighted Mods:" << std::endl;
    for (const auto& entry : modPool.getWeights())
    {
        const auto& mod = entry.second;
        std::cout << "Weight " << entry.first << " -> " << mod.getShortName() << ": "
                  << mod.getLongName() << " (Tier " << mod.getTier() << ")" << std::endl;
    }

    // Cream un craftingbench
    CraftingBench bench;
    bench.addModToBenchPool(Mod("ExtraCrit", "Extra Critical Strike Chance", 2));
    bench.listBenchMods();

    // Adaugam un mod pe o arma
    CraftingBench::addModToWeapon(sword, Mod("IncPhyDmg", "Increased Physical Damage", 1));
    // Stergem un mod de pe o arma
    bench.removeModFromWeapon(sword, Mod("IncPhyDmg", "Increased Physical Damage", 1));
    std::cout << inventory << std::endl;
    std::cout << sword << std::endl;
    std::cout << "\nProgram execution finished.\n";
    return 0;
}
