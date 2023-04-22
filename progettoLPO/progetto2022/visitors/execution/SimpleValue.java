package progetto2022.visitors.execution;

import static java.util.Objects.requireNonNull;

public abstract class SimpleValue<T> implements Value {
	protected T value;

	protected SimpleValue(T value) {
		this.value = requireNonNull(value);
	}

	@Override
	public final boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj instanceof SimpleValue<?> sv)
			return value.equals(sv.value);
		return false;
	}
	
	@Override
	public int hashCode() {
		return value.hashCode();
	}

	@Override
	public String toString() {
		return value.toString();
	}
}