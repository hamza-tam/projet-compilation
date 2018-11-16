#include "global.h"

#define ERRORS_NUMBER	3


typedef enum _error_codes {
	UNRECOGNIZED_CHARACTER_ERROR,
	SINGLE_QUOTE_EXPECTED_ERROR,
	CHARACTER_EXPECTED_ERROR,
} error_code;


void raise_error(error_code);