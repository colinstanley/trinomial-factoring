#ifndef QtFactor_H
#define QtFactor_H

#include <QObject>
#include <utility>
#include <exception>
#include "Factor.h"

class QtFactor: public QObject {

	Q_OBJECT

private:
        Factor *facc;
	QString QStringulize(pair<long int, long int> &p2QS);
	long int productCache, sumCache;
	pair<long int, long int> solutionCache;

public:
	QtFactor();
        void control(Factor *toControl);

public slots:
	void setValues(QString QS_p, QString QS_s);

signals:
	void solution(QString give);

};
#endif /*QtFactor_H*/
