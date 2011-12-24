#ifndef FACTOR_H
#define FACTOR_H

#include <iostream>
#include <exception>
#include <string>
#include <utility>
#include <list>
#include <cmath>
#include <utility>
#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>

using namespace std;

/* ONLY USED IN COMMAND LINE VERSION */
//class split_badInput;

class pair_sumCheckFailed;

class Factor {
private:

    long int m_product, m_sum;
    pair<long int, long int> solution;
    list<pair<long int, long int> > factors;

    //  SERVES NO PURPOSE IN QT  //
    bool is_numeric(const string& check);
    boost::array<long int,2> split_input (const string& to_split);
    int str2int (const string& lex);
    long int str2long (const string& lex);

    void fully_negate(list<pair<long int, long int> >& toNegate);
    void half_negate(list<pair<long int, long int> >& toHNegate);
    list<pair<long int, long int> > factor();
    pair<long int, long int> check_sum ();

public:
    Factor(long int inProduct, long int inSum);
    Factor();
    void compute();
    void setValues(long int inProduct, long int inSum);
    pair<long int, long int> getSolution();

    //  DEBUG  //
    void dump_factors(list<pair<long int, long int> >& toDump);
};
#endif /*FACTOR_H*/
