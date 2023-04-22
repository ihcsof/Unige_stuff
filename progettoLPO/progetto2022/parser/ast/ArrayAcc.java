package progetto2022.parser.ast;

import progetto2022.visitors.Visitor;

public class ArrayAcc extends BinaryOp {
    public ArrayAcc(Exp left, Exp right) {
        super(left, right);
    }

    @Override
    public <T> T accept(Visitor<T> visitor) {
        return visitor.visitArrayAcc(left, right);
    }
}
