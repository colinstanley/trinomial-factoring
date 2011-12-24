#include <QtGui>
#include "MathApp.h"

MathApp::MathApp(QWidget *parent) {
    factorController_.control(new Factor());
    ui.setupUi(this);

    QIntValidator *validator = new QIntValidator(-2147483647, 2147483646, this);
    ui.productLineEdit->setValidator(validator);
    ui.sumLineEdit->setValidator(validator);
    /*ui.aLineEdit->setValidator(validator);
    ui.bLineEdit->setValidator(validator);
    ui.cLineEdit->setValidator(validator);*/

	ui.factorSolveButton->setEnabled(false);
    //ui.rootsSolveButton->setEnabled(false);

    connect(ui.factorSolveButton, SIGNAL(clicked()), this, SLOT(factorSolveClicked()));
    connect(ui.productLineEdit, SIGNAL(returnPressed()), this, SLOT(factorSolveClicked()));
    connect(ui.sumLineEdit, SIGNAL(returnPressed()), this, SLOT(factorSolveClicked()));

    connect(this, SIGNAL(factorGiveNumbers(QString, QString)), &factorController_, SLOT(setValues(QString, QString)));

    connect(ui.productLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkFactorLineEditEmpty()));
    connect(ui.sumLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkFactorLineEditEmpty()));

    /*connect(ui.aLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkRootsLineEditEmpty()));
    connect(ui.bLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkRootsLineEditEmpty()));
    connect(ui.cLineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkRootsLineEditEmpty()));*/

    //connect(ui.rootsSolveButton, SIGNAL(clicked()), this, SLOT(rootsSolveClicked()));


    connect(&factorController_, SIGNAL(solution(QString)), this, SLOT(factorPrintText(QString)));
}
void MathApp::factorPrintText(QString toPrint) {
	ui.factorAnswerLineEdit->setText(toPrint);
}

/*void MathApp::rootsPrintText(QString toPrint) {
    ui.rootsAnswerTextEdit->setText(toPrint);
}*/

void MathApp::factorSolveClicked() {
    if((factorInputCache[0] == ui.productLineEdit->text())
       && (factorInputCache[1] == ui.sumLineEdit->text())) {
        return;
    }
    factorInputCache[0] = ui.productLineEdit->text();
    factorInputCache[1] = ui.sumLineEdit->text();
        emit(factorGiveNumbers(ui.productLineEdit->text().replace(",",""),
                  ui.sumLineEdit->text().replace(",","")));
}

/*void MathApp::rootsSolveClicked() {
    cout << "Roots Solved was clicked!\n" << flush;
    emit(rootsGiveNumbers(ui.aLineEdit->text(), ui.bLineEdit->text(), ui.cLineEdit->text()));
}*/

void MathApp::checkFactorLineEditEmpty() {
	if ((ui.productLineEdit->text() == "") || (ui.sumLineEdit->text() == "")){
		ui.factorSolveButton->setEnabled(false);
	}
	else{
		ui.factorSolveButton->setEnabled(true);
	}
}

/*void MathApp::checkRootsLineEditEmpty() {
        if ((ui.aLineEdit->text() == "") || (ui.bLineEdit->text() == "") || (ui.cLineEdit->text() == "")){
                ui.rootsSolveButton->setEnabled(false);
        }
        else{
                ui.rootsSolveButton->setEnabled(true);
        }
}*/
