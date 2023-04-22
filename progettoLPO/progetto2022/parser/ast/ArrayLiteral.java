package progetto2022.parser.ast;

import progetto2022.visitors.Visitor;
import static java.util.Objects.requireNonNull;

public class ArrayLiteral implements Exp {

	private final ExpSeq e; 

	public ArrayLiteral(ExpSeq e) {
		this.e = requireNonNull(e);
	}
	 
	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitArrayLiteral(e);
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + e + ")";
	}
}
