//
// Created by Alex on 3 Apr 2025.
//

#ifndef MOD_H
#define MOD_H
#include <string>


class Mod
{
    std::string shortName{"GenericShortModName"};
    std::string longName{"GenericLongModName"};
    unsigned int tier{1};
public:
    Mod(const std::string& short_name, const std::string& long_name, unsigned int tier);
    Mod() = default;
    friend bool operator==(const Mod& lhs, const Mod& rhs);
    friend bool operator!=(const Mod& lhs, const Mod& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Mod& mod);
    [[nodiscard]] const std::string& getShortName() const;
    [[nodiscard]] const std::string& getLongName() const;
    [[nodiscard]] unsigned int getTier() const;
};

#endif //MOD_H
