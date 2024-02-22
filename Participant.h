#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>

/**
 * @brief Abstract base class representing a participant in a card game.
 *
 * The Participant class serves as an interface for classes representing game participants,
 * enforcing the implementation of specific functions for card creation and handling Aces.
 */
class Participant {
public:
    /**
     * @brief Pure virtual function to create a string representation of a card.
     * @return String representing the created card.
     */
    virtual std::string cardCreator() = 0;

    /**
     * @brief Pure virtual function to handle the choice of Ace card values (1 or 11).
     */
    virtual void aceChoice() = 0;

    /**
     * @brief Virtual destructor for the Participant class.
     * Provides a default implementation for the destructor.
     */
    virtual ~Participant() = default;
};

#endif // PARTICIPANT_H
