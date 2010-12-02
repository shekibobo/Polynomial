#ifndef POLYNOMIALHEADER
#define	POLYNOMIALHEADER

struct term {
	int coef;
	int exp;
	struct term  *next;
};

typedef struct term Term;

typedef Term *Polynomial;

/*
	Function that obtains required data for a polynomial from
	the user, constructs a polynomial (linked list of terms)
	and returns a pointer to the first (head) term.
*/
Polynomial create();

/*
	Function that takes two polynomials, constructs and returns
	a new polynomial that is the result of adding polynomials p1 and p2

	return NULL if either p1 or p2 is NULL
*/
Polynomial add(Polynomial p1, Polynomial p2);

/*
	Function that takes two polynomials, constructs and returns
	a new polynomial that is the result of subtracting polynomial p2 from p1

	return NULL if either p1 or p2 is NULL
*/
Polynomial subtract(Polynomial p1, Polynomial p2);

/*
	Function that takes two polynomials, constructs and returns
	a new polynomial that is the result of multiplying polynomials p1 and p2

	return NULL if either p1 or p2 is NULL
*/
Polynomial multiply(Polynomial p1, Polynomial p2);

/*
	Function that takes a polynomial, evaluates that polynomial at
	a given value and returns the result of evaluation

	return 0 if p is NULL
*/
int evaluate(Polynomial p, int value);

/*
	Function that displays the polynomial to the standard output
	in the traditional mathematical form
*/
void display(Polynomial p);

#endif /* POLYNOMIALHEADER */

