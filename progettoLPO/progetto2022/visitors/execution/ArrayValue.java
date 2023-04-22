package progetto2022.visitors.execution;
import java.util.Arrays;

public class ArrayValue implements Value {
	private Value[] v;

	public ArrayValue(ExpSeqValues list) {
		v = new Value[list.size()];
		v = list.toArray(v);
	}

	@Override
	public final boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj instanceof ArrayValue av)
			return Arrays.equals(v, av.v);
		return false;
	}
	
	@Override
	public int hashCode() {
		return Arrays.hashCode(v);
	}

	@Override
	public String toString() {
		int i = 0;
		StringBuilder str = new StringBuilder();

		str.append("[");
		for(; i < v.length - 1; ++i)
			str.append(v[i]).append(";");
		str.append(v[i]).append("]");

		return str.toString();
	}

	@Override
	public Value[] toArrayValue() {
		return v;
	}
}
