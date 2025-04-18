//
// Created by Alex on 18 Apr 2025.
//

#include "../include/Equipment.h"

Equipment::Equipment()
{
    quality = 0;
    type = EQUIPMENT;
    rarity = NORMAL;
    suffixes = std::vector<Mod>();
    prefixes = std::vector<Mod>();
    implicits = std::vector<Mod>();
}

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

Equipment::Equipment(unsigned int quality, itemTypes type, itemRarities rarity)
{
    this->quality = quality;
    this->type = type;
    this->rarity = rarity;
}



