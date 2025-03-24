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
#include "ResourceManager.hpp"  // Assumes a singleton resource manager for textures

enum itemTypes
{
    EQUIPMENT,
    CURRENCY,
    MAP,
    GEM,      // socketable
    SPECIAL,  // quest items, shown in green text
};

const std::map<itemTypes, std::string> itemTypesToString = {
    {EQUIPMENT, "EQUIPMENT"},
    {CURRENCY, "CURRENCY"},
    {MAP, "MAP"},
    {GEM, "GEM"},
    {SPECIAL, "SPECIAL"}
};

enum itemRarities
{
    NORMAL,
    MAGIC,       // blue
    RARE,
    UNIQUE,
    UNIQUE_FOIL, // shiny unique
    NO_RARITY,
};

const std::map<itemRarities, std::string> itemRaritiesToString = {
    {NORMAL, "NORMAL"},
    {MAGIC, "MAGIC"},
    {RARE, "RARE"},
    {UNIQUE, "UNIQUE"},
    {UNIQUE_FOIL, "UNIQUE_FOIL"},
    {NO_RARITY, "NO_RARITY"}
};

enum equipmentTypes
{
    WEAPON,
    BODYARMOR,
    BOOTS,
    GLOVES,
    HELMET,
    RING,
    AMULET,
    JEWEL,
    BELT,
    FLASK,
};

const std::map<equipmentTypes, std::string> equipmentTypesToString = {
    {WEAPON, "WEAPON"},
    {BODYARMOR, "BODYARMOR"},
    {BOOTS, "BOOTS"},
    {GLOVES, "GLOVES"},
    {HELMET, "HELMET"},
    {RING, "RING"},
    {AMULET, "AMULET"},
    {JEWEL, "JEWEL"},
    {BELT, "BELT"},
    {FLASK, "FLASK"}
};

class Mod
{
    std::string shortName{"GenericShortModName"};
    std::string longName{"GenericLongModName"};
    unsigned int tier{1};
public:
    Mod(std::string short_name, std::string long_name, const unsigned int tier)
        : shortName(std::move(short_name)),
          longName(std::move(long_name)),
          tier(tier)
    {
    }
    Mod() = default;

    friend bool operator==(const Mod& lhs, const Mod& rhs)
    {
        return lhs.shortName == rhs.shortName &&
               lhs.longName  == rhs.longName &&
               lhs.tier      == rhs.tier;
    }
    friend bool operator!=(const Mod& lhs, const Mod& rhs)
    {
        return !(lhs == rhs);
    }
    friend std::ostream& operator<<(std::ostream& os, const Mod& mod)
    {
        os << "Short Name: " << mod.shortName << std::endl;
        os << "Long Name: " << mod.longName << std::endl;
        os << "Tier: " << mod.tier << std::endl;
        return os;
    }
    [[nodiscard]] const std::string& getShortName() const { return shortName; }
    [[nodiscard]] const std::string& getLongName()  const { return longName; }
    [[nodiscard]] unsigned int getTier()     const { return tier; }
};

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

class Item
{
    static unsigned int item_count;
    std::string name{"genericItem"};
    std::string description{"This item has no description"};
    itemTypes type{EQUIPMENT}; // default is generic equipment (2x2, no mods)
    unsigned int unique_id{};
    unsigned int width{2};
    unsigned int height{2};
    unsigned int maxStackSize{1};
    unsigned int minStackSize{1};
    unsigned int currentStackSize{1}; // for inventory management
    unsigned int maxSockets{4};
    unsigned int sockets{1};
    unsigned int itemLevel{100}; // default maximum (de obicei 85-86 e maximul pentru orice T1)
    sf::Texture texture; // item image
    itemRarities rarity{NORMAL};
    unsigned int maxPrefixes{0};
    unsigned int maxSuffixes{0};
    unsigned int quality{0};
    std::vector<Mod> affixes{}; // mods applied to the item
    std::vector<Mod> implicit{}; // implicit mods
public:
    Item()
    {
        unique_id = ++item_count;
    }
    Item(const std::string& name, const std::string& description, itemTypes type, itemRarities rarity,
         unsigned int quality, unsigned int itemLevel, unsigned int width, unsigned int height,
         unsigned int maxStackSize, unsigned int minStackSize, unsigned int maxSockets, unsigned int sockets)
    {
        unique_id = ++item_count;
        this->name = name;
        this->texture = ResourceManager::Instance().getTexture(name + ".png");
        this->quality = quality;
        this->itemLevel = itemLevel;
        this->description = description;
        this->type = type;
        this->width = width;
        this->height = height;
        this->maxStackSize = maxStackSize;
        this->minStackSize = minStackSize;
        this->maxSockets = maxSockets;
        this->sockets = sockets;
        switch (rarity)
        {
            case NORMAL:
                this->rarity = NORMAL;
                maxPrefixes = 0;
                maxSuffixes = 0;
                break;
            case MAGIC:
                this->rarity = MAGIC;
                maxPrefixes = 1;
                maxSuffixes = 1;
                break;
            case RARE:
                this->rarity = RARE;
                maxPrefixes = 3;
                maxSuffixes = 3;
                break;
            default:
                this->rarity = NORMAL;
                maxPrefixes = 0;
                maxSuffixes = 0;
                break;
        }
    }
    Item(const Item& other) = default;
    Item(Item&& other) noexcept = default;
    Item& operator=(const Item& other) = default;
    Item& operator=(Item&& other) noexcept = default;

    const std::string& get_name() const { return name; }
    // [[maybe_unused]]void set_name(const std::string& newName) { name = newName; } //nu redenumim item-ul inca (la crafting se va redenumi)
    // [[maybe_unused]]void set_description(const std::string& newDescription) { this->description = newDescription; }
    // [[maybe_unused]]itemTypes get_type() const { return type; }
    // [[maybe_unused]]void set_type(itemTypes type) { this->type = type; }
    // [[maybe_unused]]unsigned int get_item_level() const { return itemLevel; } //util mai tarz
    // [[maybe_unused]]void set_item_level(unsigned int item_level) { itemLevel = item_level; }
    // [[maybe_unused]]sf::Texture get_texture() const { return texture; }
    // [[maybe_unused]]void set_texture(const sf::Texture& texture) { this->texture = texture; }
    // [[maybe_unused]]itemRarities get_rarity() const { return rarity; }
    // [[maybe_unused]]void set_rarity(itemRarities const rarity) { this->rarity = rarity; } // va fi folosit la alchemy, regal, transmutation, scour orb
    // [[maybe_unused]]unsigned int get_quality() const { return quality; }
    // [[maybe_unused]]void set_quality(unsigned int quality) { this->quality = quality; }
    const std::vector<Mod>& get_affixes() const { return this->affixes; }
    void set_affixes(const std::vector<Mod>& newAffixes) { this->affixes = newAffixes; }
    // [[maybe_unused]]std::vector<Mod> get_implicit() const { return implicit; }
    // [[maybe_unused]]void set_implicit(const std::vector<Mod>& implicit) { this->implicit = implicit; }
    unsigned int get_current_stack_size() const { return currentStackSize; }
    void set_current_stack_size(unsigned int current_stack_size) { this->currentStackSize = current_stack_size; }
    unsigned int get_maxStackSize() const { return maxStackSize; }
    unsigned int get_width() const { return width; }
    unsigned int get_height() const { return height; }
    unsigned int get_maxPrefixes() const { return maxPrefixes; }
    unsigned int get_maxSuffixes() const { return maxSuffixes; }
    unsigned int get_unique_id() const { return unique_id; }

    // [[maybe_unused]]void print_quality() const { std::cout << "Quality: " << quality << std::endl; }
    // [[maybe_unused]]void print_item_level() const { std::cout << "Item Level: " << itemLevel << std::endl; }
    // [[maybe_unused]]void print_size() const { std::cout << "Width: " << width << " Height: " << height << std::endl; }
    // [[maybe_unused]]void print_unique_id() const { std::cout << "Unique ID: " << unique_id << std::endl; }
    friend std::ostream& operator<<(std::ostream& os, const Item& item)
    {
        os << "Name: " << item.name << std::endl;
        os << "Description: " << item.description << std::endl;
        os << "Type: " << item.type << std::endl;
        os << "Item Level: " << item.itemLevel << std::endl;
        os << "Quality: " << item.quality << std::endl;
        os << "Max Stack Size: " << item.maxStackSize << std::endl;
        os << "Max Prefixes: " << item.maxPrefixes << std::endl;
        os << "Max Suffixes: " << item.maxSuffixes << std::endl;
        os << "Max Sockets: " << item.maxSockets << std::endl;
        os << "Sockets: " << item.sockets << std::endl;
        os << "Width: " << item.width << std::endl;
        os << "Height: " << item.height << std::endl;
        os << "Current Stack Size: " << item.currentStackSize << std::endl;
        os << "Rarity: " << item.rarity << std::endl;
        os << "Affixes: " << std::endl;
        for (const auto& mod : item.affixes)
        {
            os << mod << std::endl;
        }
        return os;
    }
    friend bool operator==(const Item& lhs, const Item& rhs)
    {
        return lhs.name == rhs.name &&
               lhs.description == rhs.description &&
               lhs.type == rhs.type &&
               lhs.width == rhs.width &&
               lhs.height == rhs.height &&
               lhs.maxStackSize == rhs.maxStackSize &&
               lhs.minStackSize == rhs.minStackSize &&
               lhs.maxSockets == rhs.maxSockets &&
               lhs.sockets == rhs.sockets &&
               lhs.itemLevel == rhs.itemLevel &&
               lhs.rarity == rhs.rarity &&
               lhs.maxPrefixes == rhs.maxPrefixes &&
               lhs.maxSuffixes == rhs.maxSuffixes &&
               lhs.quality == rhs.quality &&
               lhs.affixes == rhs.affixes &&
               lhs.implicit == rhs.implicit;
    }
    friend bool operator!=(const Item& lhs, const Item& rhs)
    {
        return !(lhs == rhs);
    }
    friend bool operator<(const Item& lhs, const Item& rhs)
    {
        return lhs.unique_id < rhs.unique_id;
    }

    ~Item() = default;
};

unsigned int Item::item_count = 0;

//-----------------------------------------------------------------
// Inventory Class (6x10 grid)
//-----------------------------------------------------------------
class Inventory
{
    // For simplicity, an "empty" slot holds a default generic item.
    std::array<std::array<std::unique_ptr<Item>, 10>, 6> inventory{};
    // Map storing the top‐left position of a placed item.
    // (Here we use the item’s unique ID as key for clarity.)
    std::map<unsigned int, std::pair<unsigned int, unsigned int>> item_positions;

    // Check if a coordinate is within bounds.
    static bool inside(unsigned int x, unsigned int y)
    {
        return (x < 6 && y < 10);
    }

    // Check if an item fits starting at (row, column).
    [[nodiscard]] bool check_if_item_fits(const Item& item, unsigned int row, unsigned int column) const
    {
        unsigned int item_width = item.get_width();
        unsigned int item_height = item.get_height();
        for (unsigned int i = row; i < row + item_height; i++)
        {
            for (unsigned int j = column; j < column + item_width; j++)
            {
                if (!inside(i, j) ||
                    inventory[i][j] == nullptr ||
                    inventory[i][j]->get_name() != "genericItem")
                    return false;
            }
        }
        return true;
    }

    // Place item into each cell of its area.
    void set_item_in_inventory_slot(const Item& item, unsigned int row, unsigned int column)
    {
        inventory[row][column] = std::make_unique<Item>(item);
    }

    // Try to find an existing stack of the same (stackable) item.
    // If found, increase its current stack size and return true.
    [[nodiscard]] bool tryStackItem(const Item& item) const
    {
        // We assume stackable items have maxStackSize > 1.
        if (item.get_maxStackSize() <= 1)
            return false;

        for (unsigned int i = 0; i < 6; i++)
        {
            for (unsigned int j = 0; j < 10; j++)
            {
                if (inventory[i][j] != nullptr &&
                    inventory[i][j]->get_name() == item.get_name())
                {
                    if (inventory[i][j]->get_current_stack_size() < inventory[i][j]->get_maxStackSize())
                    {
                        unsigned int current = inventory[i][j]->get_current_stack_size();
                        inventory[i][j]->set_current_stack_size(current + 1);
                        return true;
                    }
                }
            }
        }
        return false;
    }
public:
    Inventory()
    {
        // Initialize each cell with a default "empty" generic item.
        for (unsigned int i = 0; i < 6; i++)
        {
            for (unsigned int j = 0; j < 10; j++)
            {
                inventory[i][j] = std::make_unique<Item>("genericItem", "This is a generic item", EQUIPMENT, NORMAL,
                                                         0, 100, 1, 1, 1, 1, 1, 1);
            }
        }
    }

    // Place an item into the inventory.
    // For stackable items, try to add to an existing stack.
    void place_item(const Item& item)
    {
        if (tryStackItem(item))
            return; // Stacked successfully.

        unsigned int item_width = item.get_width();
        unsigned int item_height = item.get_height();
        for (unsigned int j = 0; j < 10; j++)
        {
            for (unsigned int i = 0; i < 6; i++)
            {
                if (check_if_item_fits(item, i, j))
                {
                    // Record top-left position using the item's unique ID.
                    item_positions[item.get_unique_id()] = {i, j};
                    for (unsigned int k = i; k < i + item_height; k++)
                    {
                        for (unsigned int l = j; l < j + item_width; l++)
                        {
                            set_item_in_inventory_slot(item, k, l);
                        }
                    }
                    return;
                }
            }
        }
        std::cout << item.get_name() << " could not be placed in the inventory." << std::endl;
    }

    void print_inventory() const
    {
        for (unsigned int row = 0; row < 6; row++)
        {
            for (unsigned int column = 0; column < 10; column++)
            {
                if (inventory[row][column] != nullptr)
                    std::cout << inventory[row][column]->get_name() << " x"
                              << inventory[row][column]->get_current_stack_size() << "   ";
                else
                    std::cout << "empty   ";
            }
            std::cout << std::endl;
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Inventory& inventory)
    {
        for (unsigned int row = 0; row < 6; row++)
        {
            for (unsigned int column = 0; column < 10; column++)
            {
                if (inventory.inventory[row][column] != nullptr)
                    os << inventory.inventory[row][column]->get_name() << " x"
                        << inventory.inventory[row][column]->get_current_stack_size() << "   ";
                else
                    os << "empty   ";
            }
            os << std::endl;
        }
        return os;
    }
};

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
