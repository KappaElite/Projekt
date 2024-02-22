#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Card.h"
#include <cstdlib>
#include <ctime>
#include "Participant.h"
#include <QPixmap>
#include "ui_game.h"

using namespace std;

/**
 * @class Player
 * @brief Represents a player in a card game.
 *
 * This class inherits from the Participant class and includes functionalities
 * specific to a player, such as managing cards, sums, money, and game flags.
 */
class Player : public Participant {
    QString username; /**< The username of the player. */
    int sum = 0; /**< The total sum of card values in the player's hand. */
    int cardNumP = 0; /**< The number of cards in the player's hand. */
    int arraySize = 1; /**< Initial size of the dynamic array storing cards. */
    int splitSum = 0; /**< The sum of card values in the split hand. */
    Card* objects = static_cast<Card*>(malloc(arraySize * sizeof(Card))); /**< Dynamic array of Card objects for the player's hand. */
    vector<Card> splitCards; /**< Vector of Card objects for the split hand. */
    double money = 0; /**< The amount of money the player currently has. */
    bool splitHitFlag = false; /**< Flag indicating if the player has hit in the split hand. */
    bool splitFlag = false; /**< Flag indicating if the player has split their hand. */

public:
    /**
     * @brief Default constructor for the Player class.
     */
    Player();

    /**
     * @brief Destructor for the Player class.
     */
    ~Player();

    /**
     * @brief Get the total sum of card values in the player's hand.
     * @return The sum of card values.
     */
    int getSum();

    /**
     * @brief Get the sum of card values in the split hand.
     * @return The sum of card values in the split hand.
     */
    int getSplitSum();

    /**
     * @brief Get the number of cards in the player's hand.
     * @return The number of cards.
     */
    int getCardNum();

    /**
     * @brief Get the amount of money the player currently has.
     * @return The amount of money.
     */
    double getMoney();

    /**
     * @brief Get the flag indicating if the player has split their hand.
     * @return True if the player has split, false otherwise.
     */
    bool getSplitFlag();

    /**
     * @brief Load the player's money from a file.
     */
    void getMoneyFromFile();

    /**
     * @brief Set the flag indicating if the player has split their hand.
     * @param a The value to set the flag.
     */
    void setSplitFlag(int a);

    /**
     * @brief Set the amount of money for the player.
     */
    void setMoney();

    /**
     * @brief Set the flag indicating if the player has hit in the split hand.
     * @param a The value to set the flag.
     */
    void setSplitHitFlag(int a);

    /**
     * @brief Set the username for the player.
     * @param a The username to set.
     */
    void setUsername(QString a);

    /**
     * @brief Correct the split hand value if necessary.
     */
    void correctSplitValue();

    /**
     * @brief Handle the case of ending the game.
     * @param a The value.
     * @param b The string.
     * @param timesDouble Number of times doubled.
     * @param timesSplitDouble Number of times doubled in the split hand.
     */
    void blackJack(int a, string b, int timesDouble, int timesSplitDouble);

    /**
     * @brief Handle the choice of Ace value (1 or 11).
     */
    void aceChoice() override;

    /**
     * @brief Save the player's money to a file.
     */
    void saveMoneyToFile();

    /**
     * @brief Create a string representation of the split hand for display.
     * @return A string representation of the split hand.
     */
    string splitCardCreator();

    /**
     * @brief Create a string representation of a hit card in the split hand for display.
     * @return A string representation of the hit card in the split hand.
     */
    string splitHitCardCreator();

    /**
     * @brief Create a string representation of a card.
     * @return A string representation of the card.
     */
    string cardCreator() override;

    /**
     * @brief Check if the player has access to split their hand.
     * @return True if the player can split, false otherwise.
     */
    bool splitAcces();

    /**
     * @brief Overloaded addition assignment operator for adding money to the player.
     * @tparam T The type of the value to add.
     * @param rhs The value to add.
     * @return Reference to the modified Player object.
     */
    template <typename T>
    Player& operator+=(const T& rhs){
        money += rhs;
        return *this;
    }

    /**
     * @brief Overloaded subtraction assignment operator for subtracting money from the player.
     * @tparam T The type of the value to subtract.
     * @param rhs The value to subtract.
     * @return Reference to the modified Player object.
     */
    template <typename T>
    Player& operator-=(const T& rhs){
        money -= rhs;
        return *this;
    }
};

#endif // PLAYER_H
