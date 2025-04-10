//
// Created by Alex on 3 Apr 2025.
//

#include "../include/Mod.h"

#include <ostream>

unsigned int Mod::getTier() const
{
    return tier;
}

const std::string& Mod::getLongName() const
{
    return longName;
}

const std::string& Mod::getShortName() const
{
    return shortName;
}

Mod::Mod(const std::string& short_name, const std::string& long_name, const unsigned int tier)
{
    this->shortName = short_name;
    this->longName = long_name;
    this->tier = tier;
}

bool operator==(const Mod& lhs, const Mod& rhs)
{
    return lhs.shortName == rhs.shortName &&
           lhs.longName  == rhs.longName &&
           lhs.tier      == rhs.tier;
}

bool operator!=(const Mod& lhs, const Mod& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Mod& mod)
{
    os << "Short Name: " << mod.shortName << std::endl;
    os << "Long Name: " << mod.longName << std::endl;
    os << "Tier: " << mod.tier << std::endl;
    return os;
}


