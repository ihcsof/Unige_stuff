package progetto2022.parser.ast;

import static java.util.Objects.requireNonNull;

import progetto2022.visitors.Visitor;

public class WhileStmt implements Stmt {
	private final Exp exp; // non-optional field
	private final Block block; // non-optional field

	public WhileStmt(Exp exp, Block block) {
		this.exp = requireNonNull(exp);
		this.block = requireNonNull(block);
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + exp + "," + block + ")";
	}

	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitWhileStmt(exp, block);
	}
}
