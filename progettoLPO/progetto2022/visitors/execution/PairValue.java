package progetto2022.visitors.execution;

import static java.util.Objects.requireNonNull;
import static java.util.Objects.hash;

public class PairValue implements Value {

	private final Value fstVal;
	private final Value sndVal;

	public PairValue(Value fstVal, Value sndVal) {
		this.fstVal = requireNonNull(fstVal);
		this.sndVal = requireNonNull(sndVal);
	}

	public Value getFstVal() {
		return fstVal;
	}

	public Value getSndVal() {
		return sndVal;
	}

	@Override
	public PairValue toPair() {
		return this;
	}

	@Override
	public String toString() {
		return "(" + fstVal + "," + sndVal + ")";
	}

	@Override
	public int hashCode() {
		return hash(fstVal, sndVal);
	}

	@Override
	public final boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj instanceof PairValue pv)
			return fstVal.equals(pv.fstVal) && sndVal.equals(pv.sndVal);
		return false;
	}
}
