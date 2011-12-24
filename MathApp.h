#ifndef MATHAPP_H
#define MATHAPP_H

#include <QObject>
#include <iostream>
#include "ui_factorapp.h"
#include "QtFactor.h"
#include "Factor.h"

class MathApp : public QWidget {

    Q_OBJECT

private:
    QtFactor factorController_;
    Ui::solveDialog ui;

public:
    MathApp(QWidget *parent = 0);
    QString factorInputCache[2];

public slots:
    void factorPrintText(QString toPrint);
    //void rootsPrintText(QString toPrint);

private slots:
    void factorSolveClicked();
    //void rootsSolveClicked();
    void checkFactorLineEditEmpty();
    //void checkRootsLineEditEmpty();

signals:
    void factorGiveNumbers(QString sP, QString sS);
    //void rootsGiveNumbers(QString sA, QString sB, QString sC);
};
#endif /*MATHAPP_H*/
