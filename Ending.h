#ifndef ENDING_H
#define ENDING_H

#include <QDialog>
#include "Game.h"
#include <QString>
#include "Card.h"
#include <iostream>

using namespace std;

namespace Ui {
class Ending;
}

/**
 * @class Ending
 * @brief Represents the ending dialog for a card game.
 *
 * This class provides the user with options to start a new game or close the application
 * after the current game has ended. It displays relevant information about the player's
 * cards and the game outcome.
 */
class Ending : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Ending class.
     * @param cards The vector of cards in the player's hand.
     * @param game A pointer to the Game object.
     * @param name The name of the player.
     * @param flag An integer flag indicating the outcome of the game.
     * @param parent The parent widget (default is nullptr).
     */
    explicit Ending(vector<Card> cards, Game* game, QString name, int flag, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Ending class.
     */
    ~Ending();

private slots:
    /**
     * @brief Slot for the "Next Game" button click event.
     */
    void on_nextGame_clicked();

    /**
     * @brief Slot for the "Close" button click event.
     */
    void on_close_clicked();

private:
    int numCards = 0; /**< The number of cards in the croupier's hand. */
    string prefix = ":/img/img/"; /**< Prefix for image resources. */
    Ui::Ending *ui; /**< Pointer to the UI components of the ending dialog. */
    Game* gamePtr; /**< Pointer to the Game object. */
    QString nextGameName; /**< The name of the next game. */
};

#endif // ENDING_H
