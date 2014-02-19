#include "turingmachine.h"
#include "ui_turingmachine.h"

TuringMachine::TuringMachine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TuringMachine),
    program(0), head(0)
{
    ui->setupUi(this);
    parser = new Turing::Parser(';');
    tape = new Turing::Tape('_');

    lenta.push_back(ui->cell1);
    lenta.push_back(ui->cell2);
    lenta.push_back(ui->cell3);
    lenta.push_back(ui->cell4);
    lenta.push_back(ui->cell5);
    lenta.push_back(ui->cell6);
    lenta.push_back(ui->cell7);
    lenta.push_back(ui->cell8);
    lenta.push_back(ui->cell9);

    connect(ui->next_step_button, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->latency_slider, SIGNAL(valueChanged(int)), ui->latency_spin, SLOT(setValue(int)));
    connect(ui->latency_spin, SIGNAL(valueChanged(int)), ui->latency_slider, SLOT(setValue(int)));
}

TuringMachine::~TuringMachine()
{
    delete parser;
    delete ui;
}

bool TuringMachine::load()
{
    if (program && tape && head) return true;
    qDebug() << "here";
    QString program_text = ui->command_editor->toPlainText();
    if (program_text.isEmpty()) {
        qDebug() << "program text empty";
        return false;
    }
    std::stringstream text(program_text.toStdString());
    try {
        program = new Turing::Program(parser->parse(&text));
    }
    catch ( ... ) {
        qDebug() << "program bug";
        return false;
    }

    tape->load('(').load(')').load('(').load(')');
    head = new Turing::Tape::Head(tape->setHead(0, Turing::State("q0")));
    return true;
}

void TuringMachine::run()
{
    // block all ui
}

void TuringMachine::next()
{
    refresh();
    if (load()) {
        try {
            Turing::Command cmd = program->command( head->state(), head->observable() );
            head->execute(cmd);
            refresh();
            if (cmd == Turing::Command::STOP) emit stop();
        }
        catch (Turing::Program::Command_not_found&) {
            qDebug() << "huevo";
        }
    }
}

void TuringMachine::back()
{

}

void TuringMachine::pause()
{

}

void TuringMachine::reset()
{

}

void TuringMachine::refresh()
{
    if (load()) {
        Turing::Tape::Head iter(*head - 4);
        QString sym;
        for (int i = 0; i < 9; ++i) {
            sym.clear();
            sym.push_back(iter.observable());
            lenta[i]->setText( sym );
            iter = iter + 1;
        }
        ui->head->setText(QString::fromStdString(head->state().n()));
    }
}
