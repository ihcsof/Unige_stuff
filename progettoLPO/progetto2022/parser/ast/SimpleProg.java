package progetto2022.parser.ast;

import static java.util.Objects.requireNonNull;

import progetto2022.visitors.Visitor;

public class SimpleProg implements Prog {
	private final StmtSeq stmtSeq;

	public SimpleProg(StmtSeq stmtSeq) {
		this.stmtSeq = requireNonNull(stmtSeq);
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + stmtSeq + ")";
	}
	
	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitSimpleProg(stmtSeq);
	}
}
