package progetto2022.parser.ast;

import static java.util.Objects.requireNonNull;

public abstract class Single<T> {
	protected final T single;

	protected Single(T single) {
		this.single = requireNonNull(single);
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + "(" + single + ")";
	}
}
