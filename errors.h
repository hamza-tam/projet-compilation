#ifndef ERRORS_H
#define ERRORS_H



enum error_codes {
	FIRST_ERROR,
};


// Function declaration

void raise_error(enum error_codes code);

void show_error();


#endif