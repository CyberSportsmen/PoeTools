#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "Item.h"


// SINGLETON CLASS
class Player {
private:
    Item* selected_item;
    Inventory* inventory;

    // Singleton support
    Player();                         // Private constructor
    ~Player() = default;                        // Private destructor
    Player(const Player&) = delete;   // Prevent copy
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;        // Prevent move
    Player& operator=(Player&&) = delete;

public:
    static Player& get_instance();    // Access singleton
    Item* get_selected_item();
    void select_item(Item* item);
    Inventory* get_inventory();
    void set_inventory(Inventory* inventory);
};

#endif // PLAYER_H
