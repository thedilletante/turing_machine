#include "turingmachine.h"
#include "ui_turingmachine.h"

TuringMachine::TuringMachine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TuringMachine)
{
    ui->setupUi(this);
}

TuringMachine::~TuringMachine()
{
    delete ui;
}
