#include "EndingSplit.h"
#include "ui_endingsplit.h"

EndingSplit::EndingSplit(int flag, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EndingSplit)
{
    ui->setupUi(this);
    setFixedSize(912,650);
    this->setStyleSheet("QDialog { border-image: url(:/background/background/lose.png) 0 0 0 0 stretch stretch; }");
    ui->info->setText("Przegrłeś grę na drugiej ręce, zamknij okno i kontynuuj grę");
    ui->info->setStyleSheet("QLabel { color: red; font-size: 22px }");
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
}

EndingSplit::~EndingSplit()
{
    delete ui;
}
