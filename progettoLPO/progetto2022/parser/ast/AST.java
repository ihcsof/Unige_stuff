package progetto2022.parser.ast;

import progetto2022.visitors.Visitor;

public interface AST {
	<T> T accept(Visitor<T> visitor);
}
