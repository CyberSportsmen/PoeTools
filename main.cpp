#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <utility>

#include <Helper.h>
#include "ResourceManager.hpp"

enum itemTypes
{
    EQUIPMENT,
    CURRENCY,
    MAP,
    SPECIAL, // quest items, sunt cu text verde
};

const std::map<std::string, itemTypes> itemTypesToString = {
    {"EQUIPMENT", EQUIPMENT},
    {"CURRENCY", CURRENCY},
    {"MAP", MAP},
    {"SPECIAL", SPECIAL}
};

enum itemRarities
{
    NORMAL,
    MAGIC, // blue
    RARE,
    UNIQUE,
    UNIQUE_FOIL, // la fel ca unique doar ca e shiny
};

const std::map<std::string, itemRarities> itemRaritiesToString = {
    {"NORMAL", NORMAL},
    {"MAGIC", MAGIC},
    {"RARE", RARE},
    {"UNIQUE", UNIQUE},
    {"UNIQUE_FOIL", UNIQUE_FOIL}
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

const std::map<std::string, equipmentTypes> equipmentTypesToString = {
    {"WEAPON", WEAPON},
    {"BODYARMOR", BODYARMOR},
    {"BOOTS", BOOTS},
    {"GLOVES", GLOVES},
    {"HELMET", HELMET},
    {"RING", RING},
    {"AMULET", AMULET},
    {"JEWEL", JEWEL},
    {"BELT", BELT},
    {"FLASK", FLASK}
};

class Mod
{
    std::string shortName;
    std::string longName; // în joc, când apeși Alt, ți se dezvăluie mod-ul și ți se spune ce tier este, plus o descriere mai lungă, cu range-urile valorilor
    unsigned int nrOfNumericValues{0};
    unsigned int tier{};
public:
    Mod(std::string short_name, std::string long_name, const unsigned int tier)
        : shortName(std::move(short_name)),
          longName(std::move(long_name)),
          tier(tier)
    {
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
    std::string name{"genericItem"};
    std::string description{"This item has no description"};
    itemTypes type;
    const unsigned int itemLevel{100}; // default maxim, de obicei 85-86 e maximul necesar pentru orice mod T1
    // în funcție de tip, vom seta niște flag-uri pentru a indica cu ce poate interacționa item-ul, unde poate fi pus etc.
    // nu vom crea un caracter, vom face doar inventar, deoarece acest tool tot ce face este să emuleze crafting-ul fără să folosească
    // banii (currency-ul) câștigați în joc, pentru a fi folosiți eficient.
    sf::Texture texture; // imaginea item-ului
    std::string rarity; // raritatea afectează numărul maxim de afixe ce pot fi aplicate (excludem pentru moment implicitele care schimbă acest lucru)
    std::string quality;
    std::vector<Mod> affixes;
    std::vector<Mod> implicit;
public:
    Item() = default; // valorile implicite au fost deja setate mai sus
    Item(const std::string& name, const std::string& description, const itemTypes type, const sf::Texture& texture)
    {
        this->name = name;
        this->description = description;
        this->type = type;
        // pentru texturi, numele texturii va fi chiar numele item-ului, deci un item cu același nume va avea mereu aceeași imagine
        this->texture = texture;
    }
};

int main() {
    // sf::RenderWindow window;
    // window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    // std::cout << "Fereastra a fost creată\n";
    // window.setVerticalSyncEnabled(true);

    // Pentru exemplu, încărcăm o textură dummy (în practică, ar trebui să o încarci dintr-un fișier)
    sf::Texture dummyTexture;
    // itemLevel și alte atribute pot fi ajustate conform nevoilor tale

    Item item("Nume Item", "Descriere Item", EQUIPMENT, dummyTexture);

    std::cout << "Programul a terminat execuția\n";
    return 0;
}
