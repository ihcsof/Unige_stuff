package progetto2022.parser;


public enum TokenType { 
	// symbols
	ASSIGN, MINUS, PLUS, TIMES, NOT, AND, EQ, STMT_SEP, PAIR_OP, OPEN_PAR, CLOSE_PAR, OPEN_BLOCK, CLOSE_BLOCK, OPEN_ARRAY, CLOSE_ARRAY,
	// keywords
	PRINT, VAR, BOOL, IF, ELSE, FST, SND, WHILE, LENGTH,
	// non singleton categories
	SKIP, IDENT, NUM,   
	// end-of-file
	EOF, 	
}
