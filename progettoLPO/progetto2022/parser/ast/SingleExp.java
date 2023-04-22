package progetto2022.parser.ast;

import progetto2022.visitors.Visitor;

public class SingleExp extends Single<Exp> implements ExpSeq {

	public SingleExp(Exp single) {
		super(single);
	}
	
	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitSingleExp(single);
	}
}
