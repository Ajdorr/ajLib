#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <iostream>
#include <string>

/*
 *
 * Combinatorics
 *
 */

using namespace std;

#define SEQT_NDEF -1
#define SEQT_STR 0
#define SEQT_PERM 1
#define SEQT_COMB 2
#define SEQT_PART 3

// Only "understands" integers
class sequence {
private:
    int *P;// set of Possibilities
    int *D;// direction
    unsigned int *W; // Working set
    unsigned int n, k, it;
    int (sequence::*fn)();

    int next_str();
    int next_perm();
    int next_comb();
    int next_part();

    void clear();
public:
    // n is the number of possible numbers
    // k is the number of numbers that can be selected from the set of possible numbers
    sequence();
    // if k > n for a permuatation or combination the set wont be created and
    // creation is non destructive, the parameter passed in through T is copied, not used
    sequence(int _type, int* p, unsigned int _n, unsigned int _k);
    ~sequence();

    // just like the constructor, but allows for class conversion
    // type, n, k
    // returns 0 on success, and -1 if parameters are incorrect
    int init(int, int*, unsigned int, unsigned int);

    // both next and prev return 1 until a full loop is made
    // when 0 is returned, the array is reset
    int next();// iterates W through all possibilities
    int sint();// prints the sequence as an integer
    int* get();// returns a newed array that contains the current sequence

    // Get the element in the current state
    // indexed with 0 being the first element
    int& operator[](const int);

    // Print the current state
    friend std::ostream& operator<<(std::ostream&, const sequence&);
};

// sequence class that stores doubles
class dsequence {
private:
    int *D; // direction
    unsigned int *W; // Working set
    unsigned int n, k, it;
    double *P;// set of Possibilities
    int (dsequence::*fn)();

    int next_str();
    int next_perm();
    int next_comb();
    int next_part();

    void clear();
public:
    // n is the number of possible numbers
    // k is the number of numbers that can be selected from the set of possible numbers
    dsequence();
    // if k > n for a permuatation or combination the set wont be created and
    // creation is non destructive, the parameter passed in through T is copied, not used
    dsequence(int _type, double* p, unsigned int _n, unsigned int _k);
    ~dsequence();

    // just like the constructor, but allows for class conversion
    // type, n, k
    // returns 0 on success, and -1 if parameters are incorrect
    int init(int, double*, unsigned int, unsigned int);

    // both next and prev return 1 until a full loop is made
    // when 0 is returned, the array is reset
    int next();// iterates W through all possibilities
    double* get();

    // Get the element in the current state
    // indexed with 0 being the first element
    double& operator[](const int);

    // Print the current state
    friend std::ostream& operator<<(std::ostream&, const dsequence&);
};

// used for characters
class csequence {
private:
    char *P;// set of Possibilities
    int *D;
    unsigned int *W; // Working set and Direction Set
    unsigned int n, k, it;
    int (csequence::*fn)();

    int next_str();
    int next_perm();
    int next_comb();
    int next_part();

    void clear();
public:
    // n is the number of possible numbers
    // k is the number of numbers that can be selected from the set of possible numbers
    csequence();
    // if k > n for a permuatation or combination the set wont be created and
    // creation is non destructive, the parameter passed in through T is copied, not used
    csequence(int _type, char* p, unsigned int _n, unsigned int _k);
    ~csequence();

    // just like the constructor, but allows for class conversion
    // type, n, k
    // returns 0 on success, and -1 if parameters are incorrect
    int init(int, char*, unsigned int, unsigned int);

    // both next and prev return 1 until a full loop is made
    // when 0 is returned, the array is reset
    int next();// iterates W through all possibilities
    char* getchar(); // returns a dynamically allocated array of characters that represent the sequence, not null terminated
    string getstr();// same as above only a string class

    // Get the element in the current state
    // indexed with 0 being the first element
    char& operator[](const int);

    // Print the current state
    friend std::ostream& operator<<(std::ostream&, const csequence&);
};

#endif // SEQUENCE_H
