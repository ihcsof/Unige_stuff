package progetto2022.parser.ast;

import progetto2022.visitors.Visitor;

public class BoolLiteral extends SimpleLiteral<Boolean> {

	public BoolLiteral(boolean b) {
		super(b);
	}
	
	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitBoolLiteral(value);
	}
}
