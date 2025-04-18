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

void Equipment::setQuality(unsigned int quality)
{
    this->quality = quality;
}

void Equipment::setImplicits(const std::vector<Mod>& implicits)
{
    this->implicits = implicits;
}

void Equipment::setPrefixes(const std::vector<Mod>& prefixes)
{
    this->prefixes = prefixes;
}
void Equipment::setSuffixes(const std::vector<Mod>& suffixes)
{
    this->suffixes = suffixes;
}

Equipment::Equipment(unsigned int quality, itemTypes type, itemRarities rarity)
{
    this->quality = quality;
    this->type = type;
    this->rarity = rarity;
}



