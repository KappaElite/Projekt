#ifndef CROUPIER_H
#define CROUPIER_H

#include "Card.h"
#include "Player.h"
#include "Participant.h"
#include <iostream>
#include <vector>

/**
 * @brief Class representing the Croupier in a card game.
 *
 * The Croupier class inherits from the Participant class and implements specific
 * functionality for managing the Croupier's actions in the game.
 */
class Croupier : public Participant
{
    int sum = 0; ///< Sum of card values held by the Croupier.
    int cardNumP = 0; ///< Number of cards held by the Croupier.
    std::vector<Card> objects; ///< Vector to store Card objects held by the Croupier.


public:
    /**
     * @brief Default constructor for the Croupier class.
     */
    Croupier();

    /**
     * @brief Getter function to retrieve the sum of card values held by the Croupier.
     * @return Integer representing the sum of card values.
     */
    int getSum();

    /**
     * @brief Getter function to retrieve the vector of Card objects held by the Croupier.
     * @return Vector of Card objects.
     */
    std::vector<Card> getVector();

    /**
     * @brief Override function to create a string representation of a card.
     * @return String representing the created card.
     */
    std::string cardCreator() override;

    /**
     * @brief Override function to handle the choice of Ace cards value (1 or 11) in the Croupier's hand.
     */
    void aceChoice() override;
};

#endif // CROUPIER_H
