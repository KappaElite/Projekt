#include "BadInput.h"
#include "ui_badinput.h"

BadInput::BadInput(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BadInput)
{
    ui->setupUi(this);
    setFixedSize(585,422);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    ui->label->setStyleSheet("QLabel {font-size: 22px }");
}

BadInput::~BadInput()
{
    delete ui;
}
