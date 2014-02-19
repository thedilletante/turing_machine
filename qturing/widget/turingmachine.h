#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QMainWindow>

namespace Ui {
class TuringMachine;
}

class TuringMachine : public QMainWindow
{
    Q_OBJECT

public:
    explicit TuringMachine(QWidget *parent = 0);
    ~TuringMachine();

private:
    Ui::TuringMachine *ui;
};

#endif // TURINGMACHINE_H
