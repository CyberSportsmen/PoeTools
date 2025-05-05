//
// Created by Alex on 18 Apr 2025.
//

#include "../include/Equipment.h"

#include <iostream>

#include "../utils/enumerators.h"

Equipment::Equipment() : Item()
{
    quality = 0;
    type = WEAPON;
    rarity = NORMAL;
    suffixes = std::vector<Mod>();
    prefixes = std::vector<Mod>();
    implicits = std::vector<Mod>();
}

// IMPORTANT: USE ONLY FOR TESTING
void Equipment::addPrefix(const Mod& mod) {
    auto new_prefixes = getCurrentPrefixes();
    new_prefixes.push_back(mod);
    setPrefixes(new_prefixes);
}
// IMPORTANT: USE ONLY FOR TESTING
void Equipment::addSuffix(const Mod& mod) {
    auto new_suffixes = getCurrentSuffixes();
    new_suffixes.push_back(mod);
    setSuffixes(new_suffixes);
}

bool Equipment::alreadyContainsMod(const Mod& mod) {
    const auto pref = getCurrentPrefixes();
    const auto suff = getCurrentSuffixes();

    //std::cout << "Looking for mod: " << mod << std::endl;

    for (const auto& pr : pref) {
        //std::cout << "Checking prefix: " << pr << std::endl;
        if (pr == mod) {
            //std::cout << "Match found in prefixes." << std::endl;
            return true;
        }
    }

    for (const auto& sf : suff) {
        //std::cout << "Checking suffix: " << sf << std::endl;
        if (sf == mod) {
            //std::cout << "Match found in suffixes." << std::endl;
            return true;
        }
    }
    //std::cout << "No match found." << std::endl;
    return false;
}

std::ostream& operator<<(std::ostream& os, Equipment& equipment) {
    const auto currentPrefixes = equipment.getCurrentPrefixes();
    const auto currentSuffixes = equipment.getCurrentSuffixes();
    os << "Prefixes:\n";
    for (const auto & pref : currentPrefixes) {
        os << pref << "\n";
    }
    os << "Suffixes:\n";
    for (const auto & suff : currentSuffixes) {
        os << suff << "\n";
    }
    return os;
}

[[nodiscard]] itemRarities Equipment::get_current_rarity() const {return rarity;}

void Equipment::set_rarity(itemRarities rarity) {this->rarity = rarity;}

void Equipment::setQuality(unsigned int new_quality)
{
    this->quality = new_quality;
}

void Equipment::setImplicits(const std::vector<Mod>& new_implicits)
{
    this->implicits = new_implicits;
}

void Equipment::setPrefixes(const std::vector<Mod>& new_prefixes)
{
    this->prefixes = new_prefixes;
}
void Equipment::setSuffixes(const std::vector<Mod>& new_suffixes)
{
    this->suffixes = new_suffixes;
}




