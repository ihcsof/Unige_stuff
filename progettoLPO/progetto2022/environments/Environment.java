package progetto2022.environments;

import progetto2022.parser.ast.Variable;

public interface Environment<T> {

	/* adds a new nested scope */

	void enterScope();

	/* removes the most nested scope */

	void exitScope();

	/*
	 * looks up the value associated with 'var' starting from the innermost scope;
	 * throws an 'EnvironmentException' if 'var' could not be found in any scope
	 */

	T lookup(Variable var);

	/*
	 * updates the innermost scope by associating 'var' with 'payload'; 'var' is not allowed
	 * to be already defined, 'var' and 'payload' must be non-null
	 */

	T dec(Variable var, T payload);

	/*
	 * updates the innermost scope which defines 'var' by associating 'var' with
	 * 'payload'; throws an 'EnvironmentException' if 'var' could not be found in any
	 * scope; 'var' and 'payload' must be non-null
	 */

	T update(Variable var, T payload);

}
