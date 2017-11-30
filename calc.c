#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEBUG__


// Defines valid digits for integer token
const char DIGITS[] = "0123456789";
typedef enum {INTEGER, PLUS, MINUS, MUL, DIV, END} token;


/*
 * Prints an error message and exit immediately.
 */
void error()
{
	fprintf(stderr, "Error! Check your input.\n");
	exit(-1);
}

/*
 * Separates input string into tokens
 */
token get_token(char *current_pos)
{
	// Read first character, and check wether its a DIGIT or a operator
	switch (current_pos[0]) {
	case '+':
		return PLUS;
	case '-':
		return MINUS;
	case '*':
		return MUL;
	case '/':
		return DIV;
	case '\0':
		return END;
	default:
		return INTEGER;
	}

}

/*
 * Read the token type, and process the information accordingly.
 */
int expr(char *input)
{
	int result = 0;
	int op;
	int num;
	char *current_pos = input;

	// Skip whitespaces
	while (current_pos[0] == ' ')
		current_pos++;	

	// Expect an integer first
	if (get_token(current_pos) != INTEGER) {
		error();
		return 0;
	}
	
	// Set the result to the first integer value
	result = atoi(current_pos);
	
	// Advance the pointer to the next character after the INTEGER
	current_pos += strspn(current_pos, DIGITS);
	
	// Now read an operator followed by an integer until EOF
	while (get_token(current_pos) != END) {
		// Skip whitespaces
		while (current_pos[0] == ' ')
			current_pos++;	

		// Get the operator
		op = get_token(current_pos);
		current_pos++;
		
		// Skip whitespaces
		while (current_pos[0] == ' ')
			current_pos++;	

		// Get another integer
		if (get_token(current_pos) != INTEGER) {
			error();
			return 0;
		}
		
		num = atoi(current_pos);
		current_pos += strspn(current_pos, DIGITS);
		
		switch (op) {
		case PLUS:
			result += num;
			break;
		case MINUS:
			result -= num;
			break;
		case MUL:
			result *= num;
			break;
		case DIV:
			result /= num;
			break;		
		}
	}
	
	return result;
}


int main(int argc, char **argv)
{
	char input[256];
	
	printf("Calc> ");
	fgets(input, 255, stdin);

	// Strip the \n at the end
	input[strlen(input) - 1] = '\0';

#ifdef __DEBUG__
	fprintf(stderr, "Input: %s\n", input);
#endif
	
	printf("%d\n", expr(input));
	exit(0);
}
