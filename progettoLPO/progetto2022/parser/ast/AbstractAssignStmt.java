package progetto2022.parser.ast;

import static java.util.Objects.requireNonNull;

public abstract class AbstractAssignStmt implements Stmt {
	protected final Variable var;
	protected final Exp exp;

	protected AbstractAssignStmt(Variable var, Exp exp) {
		this.var = requireNonNull(var);
		this.exp = requireNonNull(exp);
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + var + "," + exp + ")";
	}
}
