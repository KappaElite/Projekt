#ifndef BADINPUT_H
#define BADINPUT_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class BadInput;
}

class BadInput : public QDialog
{
    Q_OBJECT

public:
    explicit BadInput(QWidget *parent = nullptr);
    ~BadInput();

private:
    Ui::BadInput *ui;
};

#endif // BADINPUT_H
