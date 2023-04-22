package progetto2022.visitors.execution;

public interface Value {
	/* default conversion methods */
	default int toInt() {
		throw new InterpreterException("Expecting an integer");
	}

	default boolean toBool() {
		throw new InterpreterException("Expecting a boolean");
	}

	default PairValue toPair() {
		throw new InterpreterException("Expecting a pair");
	}

	default ExpSeqValues toExpSeq() {
		throw new InterpreterException("Expecting ExpSeqValues");
	}

	default Value[] toArrayValue() {
		throw new InterpreterException("Expecting ArrayValue");
	}
}
