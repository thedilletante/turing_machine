#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QLabel>
#include <string>
#include <sstream>
#include <vector>
#include "../../core/parser.h"
#include "../../core/program.h"
#include "../../core/command.h"
#include "../../core/tape.h"

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
    bool load();

public slots:
    void run();
    void next();
    void back();
    void pause();
    void reset();
    void refresh();

signals:
    void stop();

private:
    Turing::Parser* parser;
    Turing::Program* program;
    Turing::Tape::Head* head;
    Turing::Tape* tape;

    std::vector< QLabel* > lenta;

};

#endif // TURINGMACHINE_H
