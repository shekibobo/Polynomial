/*
 * polynomial.c
 *
 *  Created on: Feb 22, 2010
 *      Author: Joshua Kovach
 *      Submission Date: 05 March 2010
 *      Description: a program which performs addition, subtraction, multiplication,
 *      			 and evaluation operations on user specified polynomials. Users
 *      			 may enter the number of terms in the polynomial, and then will
 *      			 specify the values of the coefficient and exponent of each term.
 *      			 Terms may be entered without respect to order of exponents, e.g.
 *      			 5x^3 + 5x^4 + 3x^2 will display as 5x^4 + 5x^3 + 3x^2. Furthermore,
 *      			 like terms will automatically be combined.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Polynomial.h"

#define polysize 2

void displayMenu(); // function prototype
Polynomial insertTerm(Polynomial poly, int coef, int exp);
void freePoly(Polynomial p);
char *get_line(FILE *f);

typedef enum { op_null, op_add, op_subtract, op_multiply, op_evaluate, op_quit } option_t;

int main() {

	while(true) displayMenu();

	return 0;
}

void displayMenu() {
	option_t option = op_null;
	int xVal = 0;
	Polynomial p[polysize];
	Polynomial result = NULL;
	char *op_input = NULL;

	printf("\n******Operations on Polynomials******\n");
	printf("1. Add polynomials\n");
	printf("2. Subtract polynomials\n");
	printf("3. Multiply polynomials\n");
	printf("4. Evaluate polynomial\n");
	printf("5. Quit\n");
	printf("Your selection (1, 2, 3, 4, 5)? ");

	op_input = get_line(stdin);
	option = atoi(op_input);
	free(op_input);

	switch(option) {
		case op_null:
			break;
		case op_add:
			for (int i = 0; i < polysize; i++) {
				printf("\n******Data for Polynomial %d******\n", i+1);
				p[i] = create();
				printf("Polynomial %d: ", i+1);
				display(p[i]);
			}
			printf("Result of Addition: ");
			result = add(p[0], p[1]);
			display(result);
			break;
		case op_subtract:
			for (int i = 0; i < polysize; i++) {
				printf("\n******Data for Polynomial %d******\n", i+1);
				p[i] = create();
				printf("Polynomial %d: ", i+1);
				display(p[i]);
			}
			printf("Result of Subtraction: ");
			result = subtract(p[0], p[1]);
			display(result);
			break;
		case op_multiply:
			for (int i = 0; i < polysize; i++) {
				printf("\n******Data for Polynomial %d******\n", i+1);
				p[i] = create();
				printf("Polynomial %d: ", i+1);
				display(p[i]);
			}
			printf("Result of Multiplication: ");
			result = multiply(p[0], p[1]);
			display(result);
			break;
		case op_evaluate:
			p[0] = create();
			p[1] = NULL;		//saves freePoly(p[1]) from breaking
			display(p[0]);
			printf("Value to evaluate: ");
			op_input = get_line(stdin);
			xVal = atoi(op_input);
			free(op_input);
			printf("Solution for f(%d): %d\n", xVal, evaluate(p[0], xVal));
			break;
		case op_quit:
			exit(0);
		default:
			printf("Invalid option\n");
			break;
	}
	for (int i = 0; i < polysize; i++) freePoly(p[i]);
	freePoly(result);
}

Polynomial create() {
	int termCount = 0;
	int newCoef = 0;
	int newExp = 0;
	char *op_input = NULL;

	printf("Enter number of terms in the polynomial: ");

	op_input = get_line(stdin);
	termCount = atoi(op_input);
	free(op_input);

	if (termCount <= 0) return NULL;	//quick break out if empty polynomial
	Polynomial poly = NULL;

	for (int i = 1; i <= termCount; i++) {
		printf("Enter coefficient and exponent of term %d: ", i);

		op_input = get_line(stdin);
		newCoef = atoi(op_input);
		free(op_input);

		op_input = get_line(stdin);
		newExp = atoi(op_input);
		free(op_input);

		poly = insertTerm(poly, newCoef, newExp);
	}

	return poly;
}

void display(Polynomial p) {
	Polynomial current = p;

	while (current != NULL) {
		if (current != p && current->coef >= 0) printf(" + ");
		else if (current->coef < 0) printf(" - ");

		//print the coefficient and the term x if applicable
		if (current->coef > 1) printf("%d", current->coef);
		else if (current->coef == 1 && current->exp  == 0) printf("%d", current->coef);
		else if (current->coef < 0) printf("%d", -current->coef);

		if (current->coef != 0 && current->exp != 0) printf("x");

		if (current->coef != 0 && (current->exp > 1 || current->exp < 0)) printf("^%d", current->exp);

		if (current->next != NULL) current = current->next;
		else current = NULL;
	}
	printf("\n");
}

Polynomial add(Polynomial p1, Polynomial p2) {
	//verify the inputs
	if (p1 == NULL && p2 != NULL) return p2;
	if (p1 != NULL && p2 == NULL) return p1;
	if (p1 == NULL && p2 == NULL) return NULL;

	Polynomial polySum, c1, c2, cSum;

	polySum = NULL;
	cSum = polySum;		//pointers for incrementation
	c1 = p1;
	c2 = p2;

	while (c1 != NULL || c2 != NULL) {	//while there are still terms to add
		int newCoef = 0;
		int newExp = 0;

		if (c1 != NULL && c2 != NULL) {	//if both terms exist
			if (c1->exp == c2->exp) {	//add like terms
				newCoef = c1->coef + c2->coef;
				newExp = c1->exp;

				c1 = c1->next;	//next terms in both polynomials
				c2 = c2->next;
			}
			else if (c1->exp > c2->exp) {	//add the larger term
				newCoef = c1->coef;
				newExp = c1->exp;

				c1 = c1->next;	//next term in polynomial addition source
			}
			else {			//add the larger term (c2 > c1)
				newCoef = c2->coef;
				newExp = c2->exp;

				c2 = c2->next;	//next term in polynomial source
			}
		}
		else if (c2 == NULL) {	//if either term is null, add the other one
			newCoef = c1->coef;
			newExp = c1->exp;

			c1 = c1->next;
		}
		else {
			newCoef = c2->coef;
			newExp = c2->exp;

			c2 = c2->next;
		}

		polySum = insertTerm(polySum, newCoef, newExp);
	}

	return polySum;
}

Polynomial subtract(Polynomial p1, Polynomial p2) {
	Polynomial difference;
	Polynomial c2 = p2;

	//negate p2
	while (c2 != NULL) {
		c2->coef *= -1;
		c2 = c2->next;
	}

	difference = add(p1, p2);

	//put p2 back to normal
	c2 = p2;
	while (c2 != NULL) {
		c2->coef *= -1;
		c2 = c2->next;
	}
	return difference;
}

Polynomial multiply(Polynomial p1, Polynomial p2) {
	if (p1 == NULL && p2 != NULL) return p2;
	if (p1 != NULL && p2 == NULL) return p1;
	if (p1 == NULL && p2 == NULL) return NULL;

	Polynomial polyProd, c1, c2;
	int newCoef = 0;
	int newExp = 0;

	polyProd = NULL;
	c1 = p1;
	c2 = p2;

	while (c1 != NULL) {
		c2 = p2;
		while (c2 != NULL) {

			//use create methods
			newCoef = c1->coef * c2->coef;
			newExp = c1->exp + c2->exp;

			polyProd = insertTerm(polyProd, newCoef, newExp);
			c2 = c2->next;
		}
		c1 = c1->next;
	}

	return polyProd;
}

int evaluate(Polynomial p, int value) {
	Polynomial current = p;
	double solution = 0;
	while (current != NULL) {
		solution += current->coef * pow(value, current->exp);
		current = current->next;
	}
	return solution;
}

Polynomial insertTerm(Polynomial poly, int coef, int exp) {
	/** The following function does the following:
	 *  1. creates a new term if poly is empty
	 *  2. if the polynomial is empty, it makes it the first term
	 *  3. if the new has a higher exponent than the first term,
	 *     it is the new first term
	 *  4. it combines like terms
	 *  5. it orders the terms in descending order according to exponent
	 */
	if (coef == 0) return poly;
	Polynomial current = poly;

	if (poly == NULL) {		//create the head of the polynomial
		poly = (Polynomial) malloc (sizeof(Term));
		poly->coef = coef;
		poly->exp = exp;
		poly->next = NULL;
	}
	else if (poly->exp < exp) {	//replace the head of the polynomial
		Polynomial new = (Polynomial) malloc (sizeof(Term));
		new->coef = coef;
		new->exp = exp;
		new->next = poly;
		poly = new;
	}
	else if (poly->exp == exp) {	//add like terms in the head
		poly->coef += coef;
	}
	else {	//adding terms anywhere after the head

		while (current->next != NULL && exp < current->next->exp) {
			current = current->next;
		}	//done traversing the list
		if (current->next == NULL) {	//add term to end of the list
			current->next = (Polynomial) malloc (sizeof(Term));
			current= current->next;

			current->next = NULL;
			current->coef = coef;
			current->exp = exp;
		}
		else if (current->next->exp == exp) {	//combine like terms
			current->next->coef += coef;
		}
		else {	//add the new term in the middle of the list
			Polynomial new = (Polynomial) malloc (sizeof(Term));
			new->coef = coef;
			new->exp = exp;
			//TODO: use get_line() to read input from the command line
			new->next = current->next;
			current->next = new;
		}
	}

	return poly;
}

void freePoly(Polynomial p) {
	if (p == NULL) return;
	Polynomial garbage;
	while (p != NULL) {
		garbage = p;
		p = p->next;
		free(garbage);
	}
}

char *get_line(FILE *f) {
	int size = 80; // initial size of memory block allocated

	char *linePtr = malloc(size);  // allocate memory block

	if (linePtr != NULL) { // if allocation successful
		int c = EOF;

		// read a line of text and replace newline character
		// with a string terminator character
		int i = 0;
		while ((c = getc(f)) != '\n' && c != EOF && c != ' ') {
			linePtr[i++] = (char) c;
			if (i == size) {
				size *= 2;
				linePtr = realloc(linePtr, size);
			}
		}
		linePtr[i] = '\0';

		// if end-of-file before any characters were read,
		// release the whole buffer
		if (c == EOF && i == 0) {
			free(linePtr);
			linePtr = NULL;
		} else {
			// release unused portion of memory
			linePtr = realloc(linePtr, i+1);
		}
	}

	return linePtr;
}
