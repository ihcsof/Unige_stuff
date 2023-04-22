package progetto2022.parser;

public class TokenizerException extends Exception {

	public TokenizerException() {
	}

	public TokenizerException(String message) {
		super(message);
	}

	public TokenizerException(Throwable cause) {
		super(cause);
	}

	public TokenizerException(String message, Throwable cause) {
		super(message, cause);
	}

	public TokenizerException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

}
