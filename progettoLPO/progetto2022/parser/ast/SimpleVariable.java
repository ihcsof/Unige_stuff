package progetto2022.parser.ast;

import static java.util.Objects.requireNonNull;

import progetto2022.visitors.Visitor;

public class SimpleVariable implements Variable {
	private final String name;

	public SimpleVariable(String name) {
		this.name = requireNonNull(name);
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public final boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj instanceof SimpleVariable sv)
			return name.equals(sv.name);
		return false;
	}

	@Override
	public int hashCode() {
		return name.hashCode();
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + name + ")";
	}
	
	@Override
	public <T> T accept(Visitor<T> visitor) {
		return visitor.visitSimpleVariable(this);
	}
}
