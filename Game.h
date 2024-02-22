#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include "Player.h"
#include "Croupier.h"
#include "Participant.h"
#include <vector>
#include <QDialog>
#include <QString>
#include <iostream>

/**
 * @brief Class representing the main game window/dialog.
 *
 * The Game class manages the game flow, player interactions, and GUI elements.
 */
class Game : public QDialog
{
    Q_OBJECT

    QString playerName; ///< String representing the player's name.
    QString moneyChange; ///< String representing the change in player's money.
    std::string moneyChangeToString; ///< String representation of moneyChange.
    std::string prefix = ":/img/img/"; ///< String representing the prefix for image paths.
    std::string splitCard; ///< String representing the path to the split card image.
    std::vector<Participant*> participant; ///< Vector to store pointers to Participant objects.
    std::vector<QPixmap> croupierPix; ///< Vector to store QPixmap objects for Croupier images.
    Player* player; ///< Pointer to the main player object.
    Player* playerPtr; ///< Pointer to the main player object.
    Croupier* croupier; ///< Pointer to the Croupier object.
    Croupier* croupierPtr; ///< Pointer to the Croupier object.
    int cardNumP = 0; ///< Number of cards held by the player.
    int croupierCard = 0; ///< Number of cards held by the Croupier.
    int cardNumPSplit = 1; ///< Number of cards held by the player in split mode.
    int timesDouble = 1; ///< Number of times the player has doubled down.
    int timesSplitDouble = 1; ///< Number of times the player has doubled down in split mode.
    bool splitAce = false; ///< Flag indicating whether the player has split an Ace.

public:
    /**
     * @brief Constructor for the Game class.
     * @param name Player's name.
     * @param parent Parent widget.
     */
    explicit Game(QString name = "", QWidget* parent = nullptr);

    /**
     * @brief Function to create participants for the game.
     */
    void participantCreator();

    /**
     * @brief Function to update player's money.
     */
    void moneyUpdate();

    /**
     * @brief Function to update the sum of card values for the player and croupier.
     */
    void sumUpdate();

    /**
     * @brief Function to update the value of money which player stored in the game.
     * @param input String representing the input value.
     */
    void upValue(std::string input);

    /**
     * @brief Function to add a card pictures to the Croupier's hand.
     */
    void croupierAdd();

    /**
     * @brief Function to check and validate the input.
     * @param a QString representing the input.
     */
    void inputCheck(QString a);

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

private slots:
    /**
     * @brief Slot for handling the start button click event.
     */
    void on_start_clicked();

    /**
     * @brief Slot for handling the add card button click event.
     */
    void on_addCard_clicked();

    /**
     * @brief Slot for handling the double down button click event.
     */
    void on_double_2_clicked();

    /**
     * @brief Slot for handling the split button click event.
     */
    void on_split_clicked();

    /**
     * @brief Slot for handling the stand button click event in split mode.
     */
    void on_standsplit_clicked();

    /**
     * @brief Slot for handling the hit button click event in split mode.
     */
    void on_hitsplit_clicked();

    /**
     * @brief Slot for handling the double down button click event in split mode.
     */
    void on_doublesplit_clicked();

    /**
     * @brief Slot for handling the stand button click event.
     */
    void on_stand_clicked();

private:
    Ui::Game *ui; ///< User interface object for the Game class.
};

#endif // GAME_H
