package progetto2022.parser;

import static progetto2022.parser.TokenType.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class BufferedTokenizer implements Tokenizer {

	private static final String regEx; // the regular expression including all valid lexems
	private static final Map<String, TokenType> keywords = new HashMap<>(); // keyword table
	private static final Map<String, TokenType> symbols = new HashMap<>(); // symbol table

	// constants representing all groups in regEx 
	private static enum Group {
		WHOLE_REG_EXP, SYMBOL, KEYWORD, SKIP, IDENT, NUM, // WHOLE_REG_EXP unused, needed only for assigning the correct value to the other constants
	}
	
	private final LineNumberReader buf_reader; // the numbered buffered reader used by the buffered tokenizer
	private String line; // currently processed line
	private final Matcher matcher = Pattern.compile(regEx).matcher(""); // the matcher used by the tokenizer
	private TokenType tokenType; // the type of the currently recognized token
	private String tokenString; // the lexeme of the currently recognized token
	private int intValue; // the integer value if the currently recognized token has type NUM
	private boolean boolValue; // the boolean value if the currently recognized token has type BOOL
	
	static { // initialization of the symbol and keyword tables: symbols and keywords are singleton lexical categories 
		
		symbols.put("=", ASSIGN);
		symbols.put("-", MINUS);
		symbols.put("+", PLUS);
		symbols.put("*", TIMES);
		symbols.put("!", NOT);
		symbols.put("&&", AND);
		symbols.put("==", EQ);
		symbols.put(";", STMT_SEP);
		symbols.put(",", PAIR_OP);
		symbols.put("(", OPEN_PAR);
		symbols.put(")", CLOSE_PAR);
		symbols.put("{", OPEN_BLOCK);
		symbols.put("}", CLOSE_BLOCK);
		symbols.put("[", OPEN_ARRAY);
		symbols.put("]", CLOSE_ARRAY);
			
		keywords.put("print", PRINT);
		keywords.put("var", VAR);
		keywords.put("false", BOOL);
		keywords.put("true", BOOL);
		keywords.put("if", IF);
		keywords.put("else", ELSE);
		keywords.put("fst", FST);
		keywords.put("snd", SND);
		keywords.put("while", WHILE);
		keywords.put("length", LENGTH);
	}

	static { 
		/* definition of the regular expressions of all valid lexemes
		 * remark: groups must correspond to the ordinal of the corresponding enum Group constant */

		final var regExUnion = "|";
		/* builds the regular expression for symbols
		 * symbols must be in reversed String order because the regular expression operator '|' is left-preferential! 
		 * For instance '==' must come before '=' */
		var symbolSets = new TreeSet<>(Comparator.<String>naturalOrder().reversed()); // symbols used in the regular expression
		for (var s : symbols.keySet())
			symbolSets.add("\\" + s); // '\\' is pre-pended to avoid regular expression syntax problems
		final var symbolRegEx = "(" + String.join(regExUnion, symbolSets) + ")"; // group 1: symbols
		/* builds the regular expressions for the other groups
		 * remark: keywordRegEx uses word boundary '\b' since keywords match only if the next symbol is not a letter */
		final var keywordRegEx = "(" + String.join(regExUnion, keywords.keySet()) + "\\b)"; // group 2: keywords
		final var skipRegEx = "(\\s+|//.*)"; // group 3: white spaces or single line comments to be skipped
		final var identRegEx = "([a-zA-Z]\\w*)"; // group 4: identifiers
		final var numRegEx = "(0|[1-9][0-9]*)"; // group 5: radix 10 natural numbers
		/* builds the complete regular expression as union of the different  groups
		 * remark: keywordRegEx must come before identRegEx because the '|' operator is left-preferential
		 * example: 'if' is a keyword but not an identifier */
		regEx = String.join(regExUnion, symbolRegEx, keywordRegEx, skipRegEx, identRegEx,
				numRegEx); 
	}

	public BufferedTokenizer(BufferedReader br) {
		this.buf_reader = new LineNumberReader(br);
	}

	private boolean hasNext() throws TokenizerException { // checks whether there are still lexemes
		if (matcher.regionEnd() > matcher.regionStart()) // the matcher has still to complete the current line
			return true;
		while (true) { // reads the next non empty line, if any
			try {
				line = buf_reader.readLine();
			} catch (IOException e) {
				throw new TokenizerException(e);
			}
			if (line == null)
				return false; // EOF reached
			if (line.isEmpty()) // yep, lines can be empty!
				continue;
			matcher.reset(line); // reset the matcher with the new non empty line
			return true;
		}
	}

	private TokenType assignTokenType() { // pre-condition: matcher.lookingAt() returned true
		if (matcher.group(Group.SYMBOL.ordinal()) != null)
			return symbols.get(tokenString);
		if (matcher.group(Group.KEYWORD.ordinal()) != null)
			return keywords.get(tokenString);
		if (matcher.group(Group.SKIP.ordinal()) != null)
			return SKIP;
		if (matcher.group(Group.IDENT.ordinal()) != null)
			return IDENT;
		if (matcher.group(Group.NUM.ordinal()) != null)
			return NUM;
		throw new AssertionError("Fatal error: could not determine the token type!");
	}

	private void resetState() {
		tokenString = null;
		tokenType = null;
	}

	private void semanticAnnotation() { // required for num or bool literals
		switch (tokenType) {
		case NUM:
			intValue = Integer.decode(tokenString);
			break;
		case BOOL:
			boolValue = Boolean.parseBoolean(tokenString);
			break;
		default: // no other annotations required
			break;
		}
	}

	private void unrecognizedToken() throws TokenizerException {
		throw new TokenizerException("on line " + buf_reader.getLineNumber() + " unrecognized token starting at '"
				+ line.substring(matcher.regionStart()) + "'");
	}

	public TokenType next() throws TokenizerException {
		resetState();
		do {
			if (!hasNext())
				return tokenType = EOF;
			if (!matcher.lookingAt())
				unrecognizedToken();
			tokenString = matcher.group();
			tokenType = assignTokenType();
			semanticAnnotation();
			matcher.region(matcher.end(), matcher.regionEnd()); // advances in the matcher
		} while (tokenType == SKIP); // keeps advancing when skippable tokens are recognized
		return tokenType;
	}

	private void checkLegalState() {
		if (tokenType == null)
			throw new IllegalStateException("No token was recognized");
	}

	private void checkLegalState(TokenType tokenType) {
		if (this.tokenType != tokenType)
			throw new IllegalStateException("No token of type " + tokenType + " was recognized");
	}

	@Override
	public String tokenString() { // lexeme of the most recently recognized token, if any
		checkLegalState();
		return tokenString;
	}

	@Override
	public boolean boolValue() { // boolean value of the most recently recognized token, if of type BOOL
		checkLegalState(BOOL);
		return boolValue;
	}

	@Override
	public int intValue() { // integer value of the most recently recognized token, if of type NUM
		checkLegalState(NUM);
		return intValue;
	}

	@Override
	public TokenType tokenType() { // type of the most recently recognized token, if any
		checkLegalState();
		return tokenType;
	}

	@Override
	public int getLineNumber() {
		return buf_reader.getLineNumber();
	}

	@Override
	public void close() throws IOException { // tokenizers are auto-closeable
		if (buf_reader != null)
			buf_reader.close();
	}

}
