package progetto2022.environments;

public class EnvironmentException extends RuntimeException {

	public EnvironmentException() {
	}

	public EnvironmentException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

	public EnvironmentException(String message, Throwable cause) {
		super(message, cause);
	}

	public EnvironmentException(String message) {
		super(message);
	}

	public EnvironmentException(Throwable cause) {
		super(cause);
	}
}
