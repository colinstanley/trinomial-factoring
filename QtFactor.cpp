#include "QtFactor.h"

void QtFactor::control(Factor *toControl) {
	facc = toControl;
}
void QtFactor::setValues(QString QS_p, QString QS_s) {
    long int p, s;
    bool b_toInt;
    p = QS_p.toInt(&b_toInt, 10);
    s = QS_s.toInt(&b_toInt, 10);
    cout << "Integer values: " << p << " " << s << endl;

    if((productCache == p) && (sumCache == s))
        emit(solution(QStringulize(solutionCache)));

    facc->setValues(p, s);

    try {
            facc->compute();
            solutionCache = facc->getSolution();
            emit(solution(QStringulize(solutionCache)));
    }
    catch(exception &e) {
            emit(solution(QString(e.what())));
    }
}

QString QtFactor::QStringulize(pair<long int, long int> &p2QS) {
	QString out;
	out = "(";
	out += out.number(p2QS.first, 10);
	out += ",";
	out += out.number(p2QS.second, 10);
	out += ")";
   return out;
}

QtFactor::QtFactor() {
        facc = NULL;
}
