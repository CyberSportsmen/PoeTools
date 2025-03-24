#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <map>

#include <SFML/Graphics.hpp>
#include <utility>

#include <Helper.h>

#include "ResourceManager.hpp"

enum itemTypes
{
    EQUIPMENT,
    CURRENCY,
    MAP,
    SPECIAL, //quest items, sunt cu text verde
};

const std::map<itemTypes, std::string> itemTypesToString;

enum itemRarities
{
    NORMAL,
    MAGIC, // blue
    RARE,
    UNIQUE,
    UNIQUE_FOIL, // la fel ca unique doar ca e shiny
};

const std::map<itemRarities, std::string> itemRaritiesToString;

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

const std::map<equipmentTypes, std::string> equipmentTypesToString;

class Mod
{
    std::string shortName;
    std::string longName; // in joc cand apesi alt iti desface mod-ul si iti spune ce tier este,
                          // si o descriere mai lunga, cu range-urile valorilor
    unsigned int tier{};
    public:
    Mod(std::string  short_name, std::string  long_name, const unsigned int tier)
        : shortName(std::move(short_name)),
          longName(std::move(long_name)),
          tier(tier)
    {
    }
};

class ModPool
{
    std::vector<std::string> prefixes;
    std::vector<std::string> suffixes;
    std::vector<std::string> affixes; // prefixe si sufixe insumate
};

class Item
{
    std::string name{"genericItem"};
    std::string description{"This item has no description"};
    itemTypes type;
    // in functie de tip vom aprinde niste flag-uri, cu ce poate sa interactioneze item-ul, unde poate fi pus etc.
    // nu vom face un caracter, vom face doar inventar, intrucat acest tool tot ce face este sa emuleze crafting-ul fara sa folosim
    // banii (currency-ul) muncit in joc, pentru a il putea folosi eficient. Pe site-ul craftofexile.com lucrul asta este facut de
    // 1000x de ori mai bine, dar pentru acest proiect va fi doar un tech demo pentru clase. Sunt zeci/sute de contribuitori la acel proiect
    // si este extrem de folositor. Sugerez cu caldura o vizita pentru o mica comparatie cand este gata proiectul meu.
    sf::Texture texture; // imagine item
    std::string rarity; // in functie de raritate este afectata dimensiunea maxima de afixe (excludem deocamdata implicitele care schimba asta)
    std::string quality;
    std::vector<Mod> affixes; //
    std::vector<Mod> implicit;
public:
    Item(const std::string& name, const std::string& description, const itemTypes type, const sf::Texture& texture)
    {
        this->name = name;
        this->description = description;
        this->type = type;
        // pentru texturi, numele texturii va fi chiar numele item-ului, intrucat un item cu acelasi nume va avea mereu aceeasi poza
        this->texture = texture;
    }
};





void PersonalizeazaAvion(sf::Sprite& avion)
{
    avion.setScale({0.3f, 0.3f});
    avion.setPosition({400, 350});

    sf::FloatRect bounds = avion.getGlobalBounds();
    avion.setOrigin({
        bounds.position.x + bounds.size.x / 2,
        bounds.position.y + bounds.size.y / 2
    });
}

int main() {
    ///////////////////////////////////////////////////////////////////////////
    ///                Exemplu de utilizare cod generat                     ///
    ///////////////////////////////////////////////////////////////////////////
    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////

    SomeClass *c = getC();
    std::cout << c << "\n";
    delete c;  // comentarea acestui rând ar trebui să ducă la semnalarea unui mem leak

    sf::RenderWindow window;
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    ///////////////////////////////////////////////////////////////////////////
    std::cout << "Fereastra a fost creată\n";
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
    // window.setVerticalSyncEnabled(true);                                 ///
    window.setFramerateLimit(60);                                           ///
    ///////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////
    /// Pentru a putea folosi resurse locale în cadrul programului trebuie modificat `CMakeLists.txt`.
    /// Deschide `CMakeLists.txt` și dă scroll la final, unde sunt apelurile la funcția `copy_files()`.
    ///
    /// După pasul anterior, putem folosi resursele locale folosind sintaxa `ResourceManager::Instance().get*`, unde
    /// * poate fi Texture, Font, Sound sau orice alt tip de resursă de care avem nevoie.
    ////////////////////////////////////////////////////////

    // Decomentează liniile marcate cu `@` de mai jos pentru a vedea ce se întâmplă atunci când încerci să primești o textură inexistentă.

    sf::Font font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");

    sf::Texture avion_texture;
    sf::Text tip_avion(font);
    // sf::Texture dummyTexture; // @

    try {
        avion_texture = ResourceManager::Instance().getTexture("airplane.png");
        // dummyTexture = ResourceManager::Instance().getTexture("fizzbuzz.png"); // @
    } catch(std::exception& exp) {
        std::cout << exp.what() << std::endl;
        return 0;
    }

    sf::Sprite avion(avion_texture);

    PersonalizeazaAvion(avion); // Este o funcție care modifică dimensiunea avionului și îi pune originea în centru.

    tip_avion.setString("An airplane");

    while(window.isOpen()) {
        bool shouldExit = false;

        while(const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                std::cout << "Fereastra a fost închisă\n";
            }
            else if (event->is<sf::Event::Resized>()) {
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                std::cout << "Received key " << (keyPressed->scancode == sf::Keyboard::Scancode::X ? "X" : "(other)") << "\n";
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    shouldExit = true;
                }
            }
        }

        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(150ms);


        float new_angle = avion.getRotation().asDegrees() + 1;
        sf::Angle angle = sf::degrees(new_angle);
        avion.setRotation(angle);

        window.clear();

        window.draw(avion); // Afișăm avionul încărcat pe ecran
        window.draw(tip_avion); // Afișăm tipul avionului

        window.display();
    }

    std::cout << "Programul a terminat execuția\n";
    return 0;
}
