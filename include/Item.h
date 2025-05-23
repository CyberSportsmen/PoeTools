#ifndef ITEM_H
#define ITEM_H

#include "../utils/enumerators.h"
#include "SFML/Graphics/Texture.hpp"

class Item
{
protected:
    static unsigned int item_count;
    std::string name;
    std::string description;
    itemTypes type;
    unsigned int unique_id{}; // Make sure this can be modified by clone in derived classes if needed
    unsigned int width;
    unsigned int height;
    unsigned int maxStackSize;
    unsigned int currentStackSize; // for inventory management
    unsigned int maxSockets;
    unsigned int sockets;
    sf::Texture texture; // item image
public:
    Item();
    Item(const std::string& name, const std::string& description, itemTypes type, unsigned int width, unsigned int height,
         unsigned int maxStackSize, unsigned int maxSockets, unsigned int sockets);
    Item(const Item& other) = default;
    Item(Item&& other) noexcept = default;
    Item& operator=(const Item& other) = default;
    Item& operator=(Item&& other) noexcept = default;
    const std::string& get_name() const;
    unsigned int get_current_stack_size() const;
    void set_current_stack_size(unsigned int current_stack_size);
    unsigned int get_maxStackSize() const;
    unsigned int get_width() const;
    unsigned int get_height() const;
    unsigned int get_unique_id() const;
    std::string get_description() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
    friend bool operator==(const Item& lhs, const Item& rhs);
    friend bool operator!=(const Item& lhs, const Item& rhs);
    friend bool operator<(const Item& lhs, const Item& rhs);

    friend std::size_t hash_value(const Item &obj);

    virtual ~Item() = default; // Virtual destructor is already correctly in place
    virtual Item* clone() const; // Declare virtual clone method
};

#endif //ITEM_H