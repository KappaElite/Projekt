#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>

/**
 * @brief Class representing a playing card.
 */
class Card
{
    int name; ///< Numerical identifier of the card.
    int symbol; ///< Numerical identifier of the card's symbol.
    int value; ///< Numerical value associated with the card.
    std::string symbolString; ///< String representation of the card's symbol.
    static std::vector<std::string> cards; ///< Static vector to store card information.

public:
    /**
     * @brief Default constructor for the Card class.
     */
    Card();

    /**
     * @brief Parameterized constructor for the Card class.
     * @param a Integer parameter used to initialize the card.
     */
    Card(int a);

    /**
     * @brief Parameterized constructor for the Card class.
     * @param a Double parameter used to initialize the card.
     */
    Card(double a);

    /**
     * @brief Getter function to retrieve the numerical identifier of the card.
     * @return Integer representing the card's name.
     */
    int getCard();

    /**
     * @brief Getter function to retrieve the string representation of the card's symbol.
     * @return String representing the card's symbol.
     */
    std::string getCardType();

    /**
     * @brief Getter function to retrieve the numerical value associated with the card.
     * @return Integer representing the card's value.
     */
    int getValue();

    /**
     * @brief Setter function to set the numerical value associated with the card.
     * @param a Integer value to set.
     */
    void setValue(int a);

    /**
     * @brief Setter function to set the numerical identifier of the card.
     * @param a Integer value to set.
     */
    void setName(int a);

    /**
     * @brief Setter function to set the numerical identifier of the card's symbol.
     * @param a Integer value to set.
     */
    void setSymbol(int a);

    /**
     * @brief Function to generate a random card.
     */
    void cardRand();

    /**
     * @brief Function to generate a random split card.
     */
    void splitCardRand();

    /**
     * @brief Function to generate a random split hit card.
     */
    void splitHitCardRand();

    /**
     * @brief Function to translate a numerical type identifier to its corresponding string representation.
     * @param a Numerical type identifier.
     * @return String representing the translated type.
     */
    std::string translateType(int a);

    /**
     * @brief Function to check whether there are duplicate cards
     * @param name Pointer to the integer representing the card's name.
     * @param symbol Pointer to the integer representing the card's symbol.
     * @param symbolString Pointer to the string representing the card's symbol.
     * @param check Pointer to the string used for validation.
     */
    void cardRep(int* name, int* symbol, std::string* symbolString, std::string* check);
};

#endif // CARD_H
