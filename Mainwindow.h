#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <string>
#include <QMainWindow>
#include <QLineEdit>
using namespace std;



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the MainWindow class.
     * @param type String representing the type of the MainWindow.
     * @param parent Parent widget.
     */
    MainWindow(std::string type, QWidget* parent = nullptr);

    /**
     * @brief Destructor for the MainWindow class.
     */
    ~MainWindow();

    /**
     * @brief Function to perform binary saving to the file.
     * @param name QString representing the input value for conversion.
     */
    void binary(QString name);

    /**
     * @brief Overloaded function to perform binary reading from the file.
     */
    void binary();

    /**
     * @brief Function to check if the input value has already beed in binary file.
     * @param name QString representing the input value to check.
     * @return Boolean indicating whether the input is a valid binary representation.
     */
    bool isRep(QString name);

private slots:
    /**
     * @brief Slot for handling the button click event.
     */
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui; ///< User interface object for the MainWindow class.
};

#endif // MAINWINDOW_H
