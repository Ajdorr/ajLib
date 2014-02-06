#include <iostream>
#include <string>
#include "ajmath.h"
#include "sequence.h"

using namespace std;

/*
 *
 *
 *
 * Sequence Class
 *
 *
 *
 */

/*
 *
 * Private Function
 *
 */

int sequence::next_str() {
    int ret=1;
    unsigned int i=k-1;
    W[i]++;
    while ((W[i] >= n)) {
        W[i] = 0;
        if (--i < k) {
            W[i]++;
        }
        else {
            ret = 0;
            break;
        }
    }

    return ret;
}

int sequence::next_perm() {
    int ret = 1, t;
    unsigned int i, lswap, grt;

    if (it == n) {
        ret = 0;
        it = 1;
    }
    if (k == 1) {
        ret = 0;
    }
    else {
        t = D[it];
        lswap = W[it];
        SWAP(W[it],W[it + t]);
        SWAP(D[it],D[it + t]);
    }

    if (ret == 0) {
        ret = next_comb();
        lswap = n; // dont swap anything
        it = k-1; // combination are always least to greatest
        for (i = 0; i < k; i++)
            D[i] = -1;// reset all directions
        return ret;
    }
    // preemptively find the next number to move and reverse directions
    for (it=n, i=0, grt=0; i < k; i++) {
        if (W[i] > lswap) {
            D[i] *= -1;
        }
        t = i + D[i];
        // find the highest mobile number
        if  ((W[i] >= grt) && (t >= 0) && ((unsigned int)t < k) && (W[i] > W[t])) {
            grt = W[i];
            it = i;
        }
    }
    return ret;
}

int sequence::next_comb() {
    int ret = 1;
    unsigned int i;

    if (++W[k-1] < n) {
        return ret;
    }
    for (i=k-2; i < k; i--) {
        if (++W[i] < n-k+i+1)
            break;
    }
    // reset condition
    if (i > k) {
        i = 0;
        W[i] = 0;
        ret = 0;
    }
    for (++i; i < k; i++)
        W[i] = W[i-1]+1;

    return ret;
}

int sequence::next_part() {
    int ret = 1;
    unsigned int i;

    if ( ++W[k-1] < n) {
        return ret;
    }
    for (i=k-2; i < k; i--) {
        if (++W[i] < n) {
            break;
        }
    }
    if (i>k){
        i = k-1;
        W[i] = 0;
        ret = 0;
    }
    for (i++; i<k; i++){
        W[i] = W[i-1];
    }

    return ret;
}

void sequence::clear() {
    if (P) {
        delete P;
        P = NULL;
    }
    if (W) {
        delete W;
        W = NULL;
    }
    if (D) {
        delete[] D;
        D = NULL;
    }
    n = k = 0;
}



/*
 *
 * Constructors and Destructors
 *
 */

sequence::sequence() {
    P = NULL;
    W = NULL;
    D = NULL;
    n = 0;
    k = 0;
}

sequence::sequence(int _type, int* p, unsigned int _n, unsigned int _k) {
    P = NULL;
    W = NULL;
    D = NULL;
    this->init(_type, p, _n, _k);

}

sequence::~sequence() {
    if (P)
        delete[] P;
    if (W)
        delete[] W;
    if (D)
        delete[] D;
}

int sequence::init(int _type, int* p, unsigned int _n, unsigned int _k) {
    unsigned int i;
    if (P) {
        delete[] P;
        P = NULL;
    }
    if (W) {
        delete[] W;
        W = NULL;
    }
    if (D) {
        delete[] D;
        D = NULL;
    }
    if (_n == 0 || _k == 0) {
        this->clear();
        return -1;
    }

    n = _n;
    k = _k;

    switch (_type){
    case SEQT_STR:
        W = new unsigned int[k];
        for (i = 0; i < k; i++)
            W[i] = 0;
        fn = &sequence::next_str;
        break;
    case SEQT_PERM:
        if (k > n) {
            this->clear();
            return -1;
        }
        W = new unsigned int[n];
        D = new int[n];
        for (i = 0; i < k; i++) {
            W[i] = i;
            D[i] = -1;
        }
        it = k-1;
        fn = &sequence::next_perm;
        break;
    case SEQT_COMB:
        if (k > n) {
            this->clear();
            return -1;
        }
        W = new unsigned int[k];
        for (i = 0; i < k; i++) {
            W[i] = i;
        }
        fn = &sequence::next_comb;
        break;
    case SEQT_PART:
        it = k-1;
        W = new unsigned int[k];
        for (i = 0; i < k; i++) {
            W[i] = 0;
        }
        fn = &sequence::next_part;
        break;
    default:
        this->clear();
        return -1;
    }

    P = new int[n];
    for (i = 0; i < n; i++) // copy the list
        P[i] = p[i];

    return 0;
}


int sequence::next() {
    return (this->*fn)();
}

int sequence::sint() {
    int ret = 0;
    unsigned int i;

    for (i = 0; i < k; i++)
        ret = 10*ret + W[i];

    return ret;
}

int* sequence::get() {
    int *ret = new int[k];
    unsigned int i;

    for (i = 0; i < k; i++) {
        ret[i] = P[W[i]];
    }

    return ret;
}

int& sequence::operator[](const int i) {
    return P[W[i]];
}

std::ostream& operator<<(std::ostream& os, const sequence& s) {
    unsigned int i;

    cout << "[ ";
    for (i = 0; i < s.k; i++) {
        cout << s.P[s.W[i]] << " ";
    }
    cout << "]";
    return os;
}

/*
 *
 *
 *
 * Double Sequence Class
 *
 *
 *
 */

/*
 *
 * Private Function
 *
 */


int dsequence::next_str() {
    int ret=1;
    unsigned int i=k-1;
    W[i]++;
    while ((W[i] >= n)) {
        W[i] = 0;
        if (--i < k) {
            W[i]++;
        }
        else {
            ret = 0;
            break;
        }
    }

    return ret;
}

int dsequence::next_perm() {
    int ret = 1, t;
    unsigned int i, lswap, grt;

    if (it == n) {
        ret = 0;
        it = 1;
    }
    if (k == 1) {
        ret = 0;
    }
    else {
        t = D[it];
        lswap = W[it];
        SWAP(W[it],W[it + t]);
        SWAP(D[it],D[it + t]);
    }

    if (ret == 0) {
        ret = next_comb();
        lswap = n; // dont swap anything
        it = k-1; // combination are always least to greatest
        for (i = 0; i < k; i++)
            D[i] = -1;// reset all directions
        return ret;
    }
    // preemptively find the next number to move and reverse directions
    for (it=n, i=0, grt=0; i < k; i++) {
        if (W[i] > lswap) {
            D[i] *= -1;
        }
        t = i + D[i];
        // find the highest mobile number
        if  ((W[i] >= grt) && (t >= 0) && ((unsigned int)t < k) && (W[i] > W[t])) {
            grt = W[i];
            it = i;
        }
    }
    return ret;
}

int dsequence::next_comb() {
    int ret = 1;
    unsigned int i;

    if (++W[k-1] < n) {
        return ret;
    }
    for (i=k-2; i < k; i--) {
        if (++W[i] < n-k+i+1)
            break;
    }
    // reset condition
    if (i > k) {
        i = 0;
        W[i] = 0;
        ret = 0;
    }
    for (++i; i < k; i++)
        W[i] = W[i-1]+1;

    return ret;
}

int dsequence::next_part() {
    int ret = 1;
    unsigned int i;

    if ( ++W[k-1] < n) {
        return ret;
    }
    for (i=k-2; i < k; i--) {
        if (++W[i] < n) {
            break;
        }
    }
    if (i>k){
        i = k-1;
        W[i] = 0;
        ret = 0;
    }
    for (i++; i<k; i++){
        W[i] = W[i-1];
    }

    return ret;
}

void dsequence::clear() {
    if (P) {
        delete P;
        P = NULL;
    }
    if (W) {
        delete W;
        W = NULL;
    }
    if (D) {
        delete[] D;
        D = NULL;
    }
    n = k = 0;
}



/*
 *
 * Constructors and Destructors
 *
 */

dsequence::dsequence() {
    P = NULL;
    W = NULL;
    D = NULL;
    n = 0;
    k = 0;
}

dsequence::dsequence(int _type, double* p, unsigned int _n, unsigned int _k) {
    P = NULL;
    W = NULL;
    D = NULL;
    this->init(_type, p, _n, _k);

}

dsequence::~dsequence() {
    if (P)
        delete[] P;
    if (W)
        delete[] W;
    if (D)
        delete[] D;
}

int dsequence::init(int _type, double* p, unsigned int _n, unsigned int _k) {
    unsigned int i;
    if (P) {
        delete[] P;
        P = NULL;
    }
    if (W) {
        delete[] W;
        W = NULL;
    }
    if (D) {
        delete[] D;
        D = NULL;
    }
    if (_n == 0 || _k == 0) {
        this->clear();
        return -1;
    }

    n = _n;
    k = _k;

    switch (_type){
    case SEQT_STR:
        W = new unsigned int[k];
        for (i = 0; i < k; i++)
            W[i] = 0;
        fn = &dsequence::next_str;
        break;
    case SEQT_PERM:
        if (k > n) {
            this->clear();
            return -1;
        }
        W = new unsigned int[n];
        D = new int[n];
        for (i = 0; i < k; i++) {
            W[i] = i;
            D[i] = -1;
        }
        it = k-1;
        fn = &dsequence::next_perm;
        break;
    case SEQT_COMB:
        if (k > n) {
            this->clear();
            return -1;
        }
        W = new unsigned int[k];
        for (i = 0; i < k; i++) {
            W[i] = i;
        }
        fn = &dsequence::next_comb;
        break;
    case SEQT_PART:
        it = k-1;
        W = new unsigned int[k];
        for (i = 0; i < k; i++) {
            W[i] = 0;
        }
        fn = &dsequence::next_part;
        break;
    default:
        this->clear();
        return -1;
    }

    P = new double[n];
    for (i = 0; i < n; i++) // copy the list
        P[i] = p[i];

    return 0;
}


int dsequence::next() {
    return (this->*fn)();
}

double* dsequence::get() {
    double *ret = new double[k];
    unsigned int i;

    for (i = 0; i < k; i++) {
        ret[i] = P[W[i]];
    }

    return ret;
}


double& dsequence::operator[](const int i) {
    return P[W[i]];
}

std::ostream& operator<<(std::ostream& os, const dsequence& s) {
    unsigned int i;

    cout << "[ ";
    for (i = 0; i < s.k; i++) {
        cout << s.P[s.W[i]] << " ";
    }
    cout << "]";
    return os;
}

/*
 *
 *
 *
 * Character Sequence Class
 *
 *
 *
 */

/*
 *
 * Private Function
 *
 */


int csequence::next_str() {
    int ret=1;
    unsigned int i=k-1;
    W[i]++;
    while ((W[i] >= n)) {
        W[i] = 0;
        if (--i < k) {
            W[i]++;
        }
        else {
            ret = 0;
            break;
        }
    }

    return ret;
}

int csequence::next_perm() {
    int ret = 1, t;
    unsigned int i, lswap, grt;

    if (it == n) {
        ret = 0;
        it = 1;
    }
    if (k == 1) {
        ret = 0;
    }
    else {
        t = D[it];
        lswap = W[it];
        SWAP(W[it],W[it + t]);
        SWAP(D[it],D[it + t]);
    }

    if (ret == 0) {
        ret = next_comb();
        lswap = n; // dont swap anything
        it = k-1; // combination are always least to greatest
        for (i = 0; i < k; i++)
            D[i] = -1;// reset all directions
        return ret;
    }
    // preemptively find the next number to move and reverse directions
    for (it=n, i=0, grt=0; i < k; i++) {
        if (W[i] > lswap) {
            D[i] *= -1;
        }
        t = i + D[i];
        // find the highest mobile number
        if  ((W[i] >= grt) && (t >= 0) && ((unsigned int)t < k) && (W[i] > W[t])) {
            grt = W[i];
            it = i;
        }
    }
    return ret;
}

int csequence::next_comb() {
    int ret = 1;
    unsigned int i;

    if (++W[k-1] < n) {
        return ret;
    }
    for (i=k-2; i < k; i--) {
        if (++W[i] < n-k+i+1)
            break;
    }
    // reset condition
    if (i > k) {
        i = 0;
        W[i] = 0;
        ret = 0;
    }
    for (++i; i < k; i++)
        W[i] = W[i-1]+1;

    return ret;
}

int csequence::next_part() {
    int ret = 1;
    unsigned int i;

    if ( ++W[k-1] < n) {
        return ret;
    }
    for (i=k-2; i < k; i--) {
        if (++W[i] < n) {
            break;
        }
    }
    if (i>k){
        i = k-1;
        W[i] = 0;
        ret = 0;
    }
    for (i++; i<k; i++){
        W[i] = W[i-1];
    }

    return ret;
}

void csequence::clear() {
    if (P) {
        delete P;
        P = NULL;
    }
    if (W) {
        delete W;
        W = NULL;
    }
    if (D) {
        delete[] D;
        D = NULL;
    }
    n = k = 0;
}



/*
 *
 * Constructors and Destructors
 *
 */

csequence::csequence() {
    P = NULL;
    W = NULL;
    D = NULL;
    n = 0;
    k = 0;
}

csequence::csequence(int _type, char* p, unsigned int _n, unsigned int _k) {
    P = NULL;
    W = NULL;
    D = NULL;
    this->init(_type, p, _n, _k);

}

csequence::~csequence() {
    if (P)
        delete[] P;
    if (W)
        delete[] W;
    if (D)
        delete[] D;
}

int csequence::init(int _type, char* p, unsigned int _n, unsigned int _k) {
    unsigned int i;
    if (P) {
        delete[] P;
        P = NULL;
    }
    if (W) {
        delete[] W;
        W = NULL;
    }
    if (D) {
        delete[] D;
        D = NULL;
    }
    if (_n == 0 || _k == 0) {
        this->clear();
        return -1;
    }

    n = _n;
    k = _k;

    switch (_type){
    case SEQT_STR:
        W = new unsigned int[k];
        for (i = 0; i < k; i++)
            W[i] = 0;
        fn = &csequence::next_str;
        break;
    case SEQT_PERM:
        if (k > n) {
            this->clear();
            return -1;
        }
        W = new unsigned int[n];
        D = new int[n];
        for (i = 0; i < k; i++) {
            W[i] = i;
            D[i] = -1;
        }
        it = k-1;
        fn = &csequence::next_perm;
        break;
    case SEQT_COMB:
        if (k > n) {
            this->clear();
            return -1;
        }
        W = new unsigned int[k];
        for (i = 0; i < k; i++) {
            W[i] = i;
        }
        fn = &csequence::next_comb;
        break;
    case SEQT_PART:
        it = k-1;
        W = new unsigned int[k];
        for (i = 0; i < k; i++) {
            W[i] = 0;
        }
        fn = &csequence::next_part;
        break;
    default:
        this->clear();
        return -1;
    }

    P = new char[n];
    for (i = 0; i < n; i++) // copy the list
        P[i] = p[i];

    return 0;
}


int csequence::next() {
    return (this->*fn)();
}

char* csequence::getchar() {
    unsigned int i;
    char *ret = new char[k];

    for (i = 0; i < k; i++)
        ret[i] = P[W[i]];

    return ret;
}

string csequence::getstr() {
    string ret(getchar(),k);

    return ret;
}

char& csequence::operator[](const int i) {
    return P[W[i]];
}

std::ostream& operator<<(std::ostream& os, const csequence& s) {
    unsigned int i;

    cout << "[ ";
    for (i = 0; i < s.k; i++) {
        cout << s.P[s.W[i]] << " ";
    }
    cout << "]";
    return os;
}
