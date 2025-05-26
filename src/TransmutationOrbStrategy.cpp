//
// Created by Alex on 27/05/2025.
//

#include "../include/TransmutationOrbStrategy.h"
#include <iostream>

bool TransmutationOrbStrategy::applyEffect(Equipment* target, Currency* currency) {
    if (!target || !currency) {
        // std::cerr << "Target or currency is null." << std::endl; // Sau logare eroare
        return false;
    }
    if (target->get_current_rarity() != NORMAL) {
        // std::cout << "Transmutation Orb can only be used on NORMAL rarity items." << std::endl;
        return false;
    }

    // Logica specifică pentru Transmutation Orb:
    // - Schimbă raritatea itemului în MAGIC.
    //   (Conform Path of Exile, un Orb of Transmutation adaugă întotdeauna 1-2 proprietăți magice)

    target->set_rarity(MAGIC); // Setează raritatea la MAGIC

    // Adaugă un numar aleatoriu de moduri (1 sau 2)
    bool mod1_added = CraftingBench::addRandomModToEquipment(*target);

    if (mod1_added) { // Adaugă al doilea doar dacă primul a reușit și există spațiu.
        // dacă mai e loc conform regulilor de MAGIC (1 prefix, 1 sufix)
        // addRandomModToEquipment ar trebui sa gestioneze asta deja.
        if (rand() % 2 == 0) { // 50% șansă pentru al doilea mod
             CraftingBench::addRandomModToEquipment(*target);
        }
    } else {
        // Primul mod nu a putut fi adăugat, ceea ce e ciudat pentru un item proaspăt făcut MAGIC.
        // Poate însemna că nu există moduri disponibile în pool.
        // std::cerr << "Failed to add the first mod with Transmutation Orb." << std::endl;
        // Poate vrei să revii la raritatea NORMALĂ dacă nu s-au putut adăuga moduri.
        // Sau să consideri operațiunea eșuată.
        return false;
    }

    // std::cout << currency->get_name() << " applied to " << target->get_name() << ". It is now MAGIC." << std::endl;
    return true;
}