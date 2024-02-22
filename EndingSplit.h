#ifndef ENDINGSPLIT_H
#define ENDINGSPLIT_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class EndingSplit;
}

class EndingSplit : public QDialog
{
    Q_OBJECT

public:
    explicit EndingSplit(int flag, QWidget *parent = nullptr);
    ~EndingSplit();

private:
    Ui::EndingSplit *ui;
};

#endif // ENDINGSPLIT_H
