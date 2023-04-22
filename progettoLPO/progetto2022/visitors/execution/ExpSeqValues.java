package progetto2022.visitors.execution;

public class ExpSeqValues extends java.util.LinkedList<Value> implements Value {
	@Override
	public ExpSeqValues toExpSeq() {
		return this;
	}
}
