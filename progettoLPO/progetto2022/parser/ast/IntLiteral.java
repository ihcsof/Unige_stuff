package progetto2022.parser.ast;

import progetto2022.visitors.Visitor;

public class IntLiteral extends SimpleLiteral<Integer> {

	public IntLiteral(int n) {
		super(n);
	}
	
	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitIntLiteral(value);
	}
}
