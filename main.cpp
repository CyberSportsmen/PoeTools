#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <utility>

//#include <Helper.h>
#include "ResourceManager.hpp"

enum itemTypes
{
    EQUIPMENT,
    CURRENCY,
    MAP,
    GEM, //socketable
    SPECIAL, // quest items, sunt cu text verde
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
    MAGIC, // blue
    RARE,
    UNIQUE,
    UNIQUE_FOIL, // la fel ca unique doar ca e shiny
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
    std::string longName{"GenericLongModName"}; // în joc, când apeși Alt, ți se dezvăluie mod-ul și ți se spune ce tier este, plus o descriere mai lungă, cu range-urile valorilor
    // TO BE IMPLEMENTED, ALONG WITH TIERS AND A LIST OF MODS FOR MODPOOL!! (depends on iLvl)
    // unsigned int nrOfNumericValues{0};
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
        return lhs.shortName == rhs.shortName
            && lhs.longName == rhs.longName
            && lhs.tier == rhs.tier;
    }

    friend bool operator!=(const Mod& lhs, const Mod& rhs)
    {
        return !(lhs == rhs);
    }
};

class ModPool
{
    std::vector<Mod> prefixes;
    std::vector<Mod> suffixes;
    std::vector<Mod> affixes; // prefixe și sufixe însumate
    std::map<unsigned int, Mod> Weights; // fiecare mod are un weight pentru a fi ales
};

class Item
{
    static unsigned int item_count;
    std::string name{"genericItem"};
    std::string description{"This item has no description"};
    itemTypes type{EQUIPMENT}; // daca nu specificam, va fi un equipment generic, alb, fara mod-uri, de dimensiuni 2x2
    unsigned int unique_id{};
    unsigned int width{2};
    unsigned int height{2};
    unsigned int value{1}; // market value in chaos orb-uri, poate fac ceva cu asta mai incolo
    unsigned int maxStackSize{1};
    unsigned int minStackSize{1};
    unsigned int currentStackSize{1};
    unsigned int maxSockets{4};
    unsigned int sockets{1};
    unsigned int itemLevel{100}; // default maxim, de obicei 85-86 e maximul necesar pentru orice mod T1
    // în funcție de tip, vom seta niște flag-uri pentru a indica cu ce poate interacționa item-ul, unde poate fi pus etc.
    // nu vom crea un caracter, vom face doar inventar, deoarece acest tool tot ce face este să emuleze crafting-ul fără să folosească
    // banii (currency-ul) câștigați în joc, pentru a fi folosiți eficient.
    sf::Texture texture; // imaginea item-ului
    // raritatea afectează numărul maxim de afixe ce pot fi aplicate (excludem pentru moment implicitele care schimbă acest lucru)
    itemRarities rarity{NORMAL};
    unsigned int maxPrefixes{0};
    unsigned int maxSuffixes{0};
    unsigned int quality{0};
    std::vector<Mod> affixes{}; // empty by default
    std::vector<Mod> implicit{}; // empty by default
public:
    Item()
    {
        unique_id = ++item_count;
    }
    Item(const std::string& name, const std::string& description, const itemTypes type, const itemRarities rarity, const unsigned int quality, const unsigned int itemLevel, const unsigned int width, const unsigned int height, const unsigned int maxStackSize, const unsigned int minStackSize, const unsigned int maxSockets, const unsigned int sockets)
    {
        unique_id = ++item_count;
        this->name = name;
        // pentru texturi, numele texturii va fi chiar numele item-ului, deci un item cu același nume va avea mereu aceeași imagine
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
        // REDUNDANT SI GRESIT!!!
        //if (type == EQUIPMENT)
        //{
        //    this->maxSockets = std::min<unsigned int>({width * height, 6u});
        //    this->minStackSize = 1;
        //    this->maxStackSize = 1;
        //}
        //else if (type == CURRENCY)
        //{
        //    this->width = 1;
        //    this->height = 1;
        //}
        //else if (type == MAP)
        //{
        //    this->width = 1;
        //    this->height = 1;
        //    this->maxStackSize = 1;
        //    this->minStackSize = 1;
        //    this->maxSockets = 0;
        //    this->sockets = 0;
        //}
        //else if (type == GEM)
        //{
        //    this->width = 1;
        //    this->height = 1;
        //    this->maxStackSize = 1;
        //    this->minStackSize = 1;
        //    this->maxSockets = 0;
        //    this->sockets = 0;
        //}
        //else if (type == SPECIAL)
        //{
        //    this->maxStackSize = 1;
        //    this->minStackSize = 1;
        //    this->maxSockets = 0;
        //    this->sockets = 0;
        //}
        //else // eroare, tipul de item introdus gresit
        //{
        //    throw std::invalid_argument("Invalid item type");
        //}
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
    // nu schimbam id-ul unic, il copiem pentru ca ar trebui sa devina unul si acelasi daca le egalam.
    Item(const Item& other) = default;
    Item(Item&& other) noexcept = default;
    Item& operator=(const Item& other) = default;
    Item& operator=(Item&& other) noexcept = default;

    [[nodiscard]] std::string get_name() const
    {
        return name;
    }

    void set_name(const std::string& name)
    {
        this->name = name;
    }

    [[nodiscard]] std::string get_description() const
    {
        return description;
    }

    void set_description(const std::string& description)
    {
        this->description = description;
    }

    [[nodiscard]] itemTypes get_type() const
    {
        return type;
    }

    void set_type(itemTypes type)
    {
        this->type = type;
    }

    [[nodiscard]] unsigned int get_item_level() const
    {
        return itemLevel;
    }

    void set_item_level(unsigned int item_level)
    {
        itemLevel = item_level;
    }

    [[nodiscard]] sf::Texture get_texture() const
    {
        return texture;
    }

    void set_texture(const sf::Texture& texture)
    {
        this->texture = texture;
    }

    [[nodiscard]] itemRarities get_rarity() const
    {
        return rarity;
    }

    void set_rarity(itemRarities const rarity)
    {
        this->rarity = rarity;
    }

    [[nodiscard]] unsigned int get_quality() const
    {
        return quality;
    }

    void set_quality(unsigned int quality)
    {
        this->quality = quality;
    }

    [[nodiscard]] std::vector<Mod> get_affixes() const
    {
        return affixes;
    }

    void set_affixes(const std::vector<Mod>& affixes)
    {
        this->affixes = affixes;
    }

    [[nodiscard]] std::vector<Mod> get_implicit() const
    {
        return implicit;
    }

    void set_implicit(const std::vector<Mod>& implicit)
    {
        this->implicit = implicit;
    }
    void print_quality() const
    {
        std::cout << "Quality: " << quality << std::endl;
    }
    void print_item_level() const
    {
        std::cout << "Item Level: " << itemLevel << std::endl;
    }
    void print_size() const
    {
        std::cout << "Width: " << width << " Height: " << height << std::endl;
    }
    [[nodiscard]] unsigned int get_width() const
    {
        return width;
    }

    [[nodiscard]] unsigned int get_height() const
    {
        return height;
    }

    void print_unique_id() const
    {
        std::cout << "Unique ID: " << unique_id << std::endl;
    }
    [[nodiscard]] unsigned int get_unique_id() const
    {
        return unique_id;
    }
    friend bool operator==(const Item& lhs, const Item& rhs)
    {
        return lhs.name == rhs.name
            && lhs.description == rhs.description
            && lhs.type == rhs.type
            && lhs.width == rhs.width
            && lhs.height == rhs.height
            // && lhs.value == rhs.value
            && lhs.maxStackSize == rhs.maxStackSize
            && lhs.minStackSize == rhs.minStackSize
            && lhs.maxSockets == rhs.maxSockets
            && lhs.sockets == rhs.sockets
            && lhs.itemLevel == rhs.itemLevel
            //&& lhs.texture == rhs.texture texturile pot fi diferite, putem avea mtx-uri :)
            && lhs.rarity == rhs.rarity
            && lhs.maxPrefixes == rhs.maxPrefixes
            && lhs.maxSuffixes == rhs.maxSuffixes
            && lhs.quality == rhs.quality
            && lhs.affixes == rhs.affixes
            && lhs.implicit == rhs.implicit;
    }

    friend bool operator!=(const Item& lhs, const Item& rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const Item& lhs, const Item& rhs)
    {
        return lhs.unique_id < rhs.unique_id;
    }

    friend auto operator<=(const Item& lhs, const Item& rhs) -> bool
    {
        return rhs >= lhs;
    }

    friend bool operator>(const Item& lhs, const Item& rhs)
    {
        return rhs < lhs;
    }

    friend bool operator>=(const Item& lhs, const Item& rhs)
    {
        return !(lhs < rhs);
    }

    friend std::size_t hash_value(const Item& obj)
    {
        std::size_t seed = 0x5D5782BC;
        seed ^= (seed << 6) + (seed >> 2) + 0x5A1DF970 + static_cast<std::size_t>(obj.unique_id);
        return seed;
    }
};
unsigned int Item::item_count = 0;

class Inventory // 6x10
{
    std::array<std::array<std::unique_ptr<Item>, 10>, 6> inventory{}; // 6x10
    std::map<Item, std::pair<unsigned int, unsigned int>> item_positions{};
    // mapez fiecare item la coltul stanga sus de unde a fost gasit un loc valid
    static bool inside(unsigned int x, unsigned int y)
    {
        if (x < 6 && y < 10)
            return true;
        return false;
    }

    [[nodiscard]] bool check_if_item_fits(const Item& item, const unsigned int row, const unsigned int column) const
    {
        unsigned int item_width = item.get_width();
        unsigned int item_height = item.get_height();
        for (unsigned int i = row; i < row + item_height; i++)
        {
            for (unsigned int j = column; j < column + item_width; j++)
            {
                if (!inside(i, j) || inventory[i][j] == nullptr || inventory[i][j]->get_name() != "genericItem")
                    return false;
            }
        }
        return true;
    }

    void set_item_in_inventory_slot(const Item& item, const unsigned int row, const unsigned int column)
    {
        inventory[row][column] = std::make_unique<Item>(item);
    }

public:
    // place item
    Inventory()
    {
        for (unsigned int i = 0; i < 6; i++)
        {
            for (unsigned int j = 0; j < 10; j++)
            {
                inventory[i][j] = std::make_unique<Item>("genericItem", "This is a generic item", EQUIPMENT, NORMAL, 0,
                                                         100, 1, 1, 1, 1, 1, 1);
            }
        }
    }

    // arata ca naiba
    void place_item(const Item& item)
    {
        unsigned int item_width = item.get_width();
        unsigned int item_height = item.get_height();
        for (unsigned int j = 0; j < 10; j++)
        {
            for (unsigned int i = 0; i < 6; i++)
            {
                if (check_if_item_fits(item, i, j) == 1)
                {
                    // coltul din stanga sus
                    item_positions[item] = {i, j};
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
        // daca a ajuns aici inseamna ca nu a putut pune itemul in inventar. Notificam user-ul
        std::cout << item.get_name() + " nu a putut fi pus(a) in inventar" << std::endl;
        // aici templar face "I am no beast of burden" =)))))))
    }

    void print_inventory() const
    {
        for (unsigned int row = 0; row < 6; row++)
        {
            for (unsigned int column = 0; column < 10; column++)
            {
                if (inventory[row][column] != nullptr)
                    std::cout << inventory[row][column]->get_name() << " ";
                else
                    std::cout << "empty ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // sf::RenderWindow window;
    // window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    // std::cout << "Fereastra a fost creată\n";
    // window.setVerticalSyncEnabled(true);

    // Pentru exemplu, încărcăm o textură dummy (în practică, ar trebui să o încarci dintr-un fișier)
    // itemLevel și alte atribute pot fi ajustate conform nevoilor tale

    Item sabiuta("Sword", "Sabie Smechera",EQUIPMENT,MAGIC,20,83,2,3,1,1,3,1);
    Item Chaos_Orb("Chaos Orb", "Reforces a rare item with new random proprieties", CURRENCY, NO_RARITY, NULL, NULL, 1, 1, 20, 1, 0, 0);
    // item.print_quality();
    // item.set_quality(28);
    // item.print_quality();
    Inventory inventory{};
    sabiuta.print_size();
    Chaos_Orb.print_size();
    inventory.place_item(Chaos_Orb);
    //Chaos_Orb.print_unique_id();
    //sabiuta.print_unique_id();
    inventory.place_item(sabiuta);
    inventory.place_item(Chaos_Orb); // ar trebui sa fie stackable
    inventory.print_inventory();

    std::cout << "Programul a terminat execuția\n";
    return 0;
}
