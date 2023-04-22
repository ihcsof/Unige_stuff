package progetto2022.parser.ast;

import progetto2022.visitors.Visitor;

public class Length extends UnaryOp {

	public Length(Exp exp) {
		super(exp);
	}
	
	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitLength(exp);
	}
}
