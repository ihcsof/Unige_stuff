package progetto2022.visitors.typechecking;

import static java.util.Objects.requireNonNull;
import static java.util.Objects.hash;

public class PairType implements Type {

	private final Type fstType;
	private final Type sndType;

	public static final String TYPE_NAME = "PAIR";

	public PairType(Type fstType, Type sndType) {
		this.fstType = requireNonNull(fstType);
		this.sndType = requireNonNull(sndType);
	}

	public Type getFstType() {
		return fstType;
	}

	public Type getSndType() {
		return sndType;
	}

	@Override
	public final boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj instanceof PairType pt)
		return fstType.equals(pt.fstType) && sndType.equals(pt.sndType);
		return false;
	}

	@Override
	public int hashCode() {
		return hash(fstType,sndType);
	}

	@Override
	public String toString() {
		return "(" + fstType + "*" + sndType + ")";
	}

}
