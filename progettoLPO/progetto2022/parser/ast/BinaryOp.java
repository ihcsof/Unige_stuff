package progetto2022.parser.ast;

import static java.util.Objects.requireNonNull;

public abstract class BinaryOp implements Exp {
	protected final Exp left;
	protected final Exp right;

	protected BinaryOp(Exp left, Exp right) {
		this.left = requireNonNull(left);
		this.right = requireNonNull(right);
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + left + "," + right + ")";
	}

}
