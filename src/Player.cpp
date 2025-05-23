#include "../include/Player.h"

// Private constructor
Player::Player() {
    inventory = new Inventory();
    selected_item = nullptr;
}

// this shit doesn't work??
// Player::~Player() {
//     delete inventory;
// }

Player& Player::get_instance() {
    static Player instance; // Created once, reused forever
    return instance;
}

Item* Player::get_selected_item() {
    return selected_item;
}

void Player::select_item(Item* item) {
    selected_item = item;
}

Inventory* Player::get_inventory() {
    return inventory;
}

void Player::set_inventory(Inventory *inventory) {
    Player::inventory = inventory;
}

