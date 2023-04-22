package progetto2022.environments;

import static java.util.Objects.requireNonNull;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

import progetto2022.parser.ast.Variable;

public class GenEnvironment<T> implements Environment<T> {

	private LinkedList<Map<Variable, T>> scopeChain = new LinkedList<>();

	/*
	 * enter a new nested scope; private method shared by 'enterScope()' and the
	 * constructor 'GenEnvironment()'
	 */
	private void addEmptyScope() {
		scopeChain.addFirst(new HashMap<>());
	}

	/* create an environment with just one empty scope */
	public GenEnvironment() {
		addEmptyScope();
	}

	@Override
	public void enterScope() {
		addEmptyScope();
	}

	@Override
	public void exitScope() {
		scopeChain.removeFirst();
	}

	/*
	 * looks up the innermost scope where 'var' is found;
	 * throws an 'EnvironmentException' if 'var' could not be found in any scope
	 */

	protected Map<Variable, T> resolve(Variable var) {
		for (var scope : scopeChain)
			if (scope.containsKey(var))
				return scope;
		throw new EnvironmentException("Undeclared variable " + var.getName());
	}

	@Override
	public T lookup(Variable var) {
		return resolve(var).get(var);
	}

	/*
	 * updates 'scope' to associate 'var' with 'payload'; 'var' and 'payload' must be non-null
	 */

	private static <T> T updateScope(Map<Variable, T> scope, Variable var, T payload) {
		return scope.put(requireNonNull(var), requireNonNull(payload));
	}

	/*
	 * updates the innermost scope by associating 'var' with 'payload'; 'var' is not allowed
	 * to be already defined, 'var' and 'payload' must be non-null
	 */

	@Override
	public T dec(Variable var, T payload) {
		var scope = scopeChain.getFirst();
		if (scope.containsKey(var))
			throw new EnvironmentException("Variable " + var.getName() + " already declared");
		return updateScope(scope, var, payload);
	}

	/*
	 * updates the 'payload' of the innermost variable 'var', throws an 'EnvironmentException' if no varibale 'var' can be
	 * found in the scope chain. Only used for the dynamic semantics
	 */

	@Override
	public T update(Variable var, T payload) {
		var scope = resolve(var);
		return updateScope(scope, var, payload);
	}

}
