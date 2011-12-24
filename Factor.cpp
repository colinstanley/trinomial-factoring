#include "Factor.h"

using namespace std;

////   ONLY USED IN COMMAND LINE PROGRAM   ////
class split_badInput: public exception {
    virtual const char* what() const throw() {
        return "Invalid input.";
    }
}badInput;



// To throw if there is no solution
class pair_sumCheckFailed: public exception {
    virtual const char* what() const throw() {
        return "No integer solution";
    }
}sumCheckFailed;


////   ONLY USED IN COMMAND LINE PROGRAM   ////
bool Factor::is_numeric(const string& check) {
    for (unsigned int i = 0; i < check.length(); i++) {
        if (!isdigit(check[i]) && check[i] != '-' && check[i] != ' ')
            return false;
    }
    return true;
}

////   ONLY USED IN COMMAND LINE PROGRAM   ////
boost::array<long int,2> Factor::split_input (const string& to_split) {
    long int marker, found = -1;
    boost::array<string,2> str_array;
    for (long int i = 1; i < 3; i++) {
        found = to_split.find(' ',found+1);
        if (i == 1 && found != (long int)string::npos) {
            marker = found;
            str_array[0] = to_split.substr(0,found);
            continue;
        }
        else if (i == 2 && found == (long int)string::npos) {
            str_array[1] = to_split.substr(marker+1,(to_split.length()-marker)-1);
            if (is_numeric(to_split)) {
                boost::array<long int,2> int_array;
                int_array[0] = boost::lexical_cast<long int>(str_array[0]);
                int_array[1] = boost::lexical_cast<long int>(str_array[1]);
                return int_array;
            }
        }
        else
            break;
    }
    throw(badInput);
}

long int Factor::str2long (const string& lex) {
    return boost::lexical_cast<long int>(lex);
}


Factor::Factor (long int inProduct, long int inSum) {
    m_product = inProduct;
    m_sum = inSum;
}

Factor::Factor() {}


///////////////////////////////////////
//               4 cases:            //
// 1. F && S (all factors positive)  //
// 2. F && -S (all factors negative) //
// 3. -F && -S (half negative)       //
// 4. -F && S (half negative)        //
///////////////////////////////////////

// Called in factorClass::compute().
list<pair<long int, long int> > Factor::factor() {
    long int abs_product = abs(m_product); // To avoid imaginary numbers
    list<pair<long int, long int> > allFactors;
    if ((m_product == 0) && (m_sum == 0)) {
        allFactors.push_back(make_pair(0, 0));
        return allFactors;
    }
    allFactors.push_back(make_pair(1, abs_product)); //To save time. Polarity will be switched either full or half later if necessary.
    for (int factor_index = 2; factor_index <= (long int)sqrt(abs_product); factor_index++) {
        if (m_product % factor_index == 0) {
            allFactors.push_back(make_pair(factor_index, abs_product/factor_index));
        }
    }
    /*cout << "Positive:\n";
    dump_factors(allFactors);*/
    // If none of the if's run, assume it's all positive and return as such.
    if ((m_product > 0) && (m_sum < 0))
        fully_negate(allFactors);
    else if (((m_product < 0) && (m_sum < 0)) || ((m_product < 0) && (m_sum > 0)))
        half_negate(allFactors);
    /*cout << "Modified:\n";
    dump_factors(allFactors);*/
    return allFactors;
}

// Called in factorClass::factor().
// Negates all elements of the pairs in the list.
void Factor::fully_negate(list<pair<long int, long int> >& toNegate) {
    list<pair<long int, long int> >::iterator nIt = toNegate.begin();
    for (; nIt != toNegate.end(); nIt++) {
        nIt->first  *= -1;
        nIt->second *= -1;
    }
}

// Called in factorClass::factor().
// Negates only one element of each pair and then pushes to the list the same pair with the other element negated.
// This function doubles the length of the list.
void Factor::half_negate(list<pair<long int, long int> >& toHNegate) {
    list<pair<long int, long int> >::iterator hnIt = toHNegate.begin();
    for (; hnIt != toHNegate.end(); hnIt++) {
        hnIt->first *= -1; //switch polarity
        toHNegate.push_front(make_pair(hnIt->first * -1 /*reswitch polarity*/, (hnIt->second) * -1));
    }
}

// Called in factorClass::compute().
// Run through the list and compare the sum of all the pairs to the given sum.
pair<long int, long int> Factor::check_sum() {
    for (list<pair<long int, long int> >::iterator it = factors.begin(); it != factors.end(); it++) {
        if ((it->first) + (it->second) == m_sum) {
            //cout << "Making pair: " << it->first << "," << it->second << endl;
            return make_pair(it->first, it->second);
        }
    }
    throw(sumCheckFailed);
}

// Controlling function of the class.
void Factor::compute() {
    factors = factor();
    dump_factors(factors);
    solution = check_sum();
    /*catch(exception& e){
        return 0;
    }*/
}

pair<long int, long int> Factor::getSolution() {
    return solution;
}

// In addition to the constructor, you may use this to initialize
// factorClass::m_product and factorClass::m_sum
void Factor::setValues(long int inProduct, long int inSum) {
    m_product = inProduct;
    m_sum = inSum;
    cout << "Received: " << m_product << ' ' << m_sum << endl;
}

//Debug function to prlong int the contents of a list<pair<long int, long int> >.
void Factor::dump_factors(list<pair<long int, long int> >& toDump) {
    for (list<pair<long int, long int> >::iterator it = toDump.begin(); it != toDump.end(); it++) {
        if(it->first >= 0) {
            cout << ' ' << it->first << "\t";
        }
        else {
        cout << it->first << "\t";
        }
        if(it->second >= 0){
            cout << ' ' << it->second << endl;
        }
        else {
        cout << it->second << endl;
        }
    }
	cout << endl;
}
