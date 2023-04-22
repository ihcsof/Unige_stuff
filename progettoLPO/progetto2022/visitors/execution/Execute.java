package progetto2022.visitors.execution;

import java.io.PrintWriter;

import progetto2022.environments.EnvironmentException;
import progetto2022.environments.GenEnvironment;
import progetto2022.parser.ast.Block;
import progetto2022.parser.ast.Exp;
import progetto2022.parser.ast.Stmt;
import progetto2022.parser.ast.StmtSeq;
import progetto2022.parser.ast.Variable;
import progetto2022.visitors.Visitor;
import progetto2022.parser.ast.ExpSeq;

import static java.util.Objects.requireNonNull;

public class Execute implements Visitor<Value> {

	private final GenEnvironment<Value> env = new GenEnvironment<>();
	private final PrintWriter printWriter; // output stream used to print values

	public Execute() {
		printWriter = new PrintWriter(System.out, true);
	}

	public Execute(PrintWriter printWriter) {
		this.printWriter = requireNonNull(printWriter);
	}

	// dynamic semantics for programs; no value returned by the visitor

	@Override
	public Value visitSimpleProg(StmtSeq stmtSeq) {
		try {
			stmtSeq.accept(this);
			// possible runtime errors
			// EnvironmentException: undefined variable
		} catch (EnvironmentException e) {
			throw new InterpreterException(e);
		}
		return null;
	}

	// dynamic semantics for statements; no value returned by the visitor

	@Override
	public Value visitAssignStmt(Variable var, Exp exp) {
		env.update(var, exp.accept(this));
		return null;
	}

	@Override
	public Value visitPrintStmt(Exp exp) {
		printWriter.println(exp.accept(this));
		return null;
	}

	@Override
	public Value visitVarStmt(Variable var, Exp exp) {
		env.dec(var, exp.accept(this));
		return null;
	}

	@Override
	public Value visitIfStmt(Exp exp, Block thenBlock, Block elseBlock) {
		if (exp.accept(this).toBool())
			thenBlock.accept(this);
		else if (elseBlock != null)
			elseBlock.accept(this);
		return null;
	}

	@Override
	public Value visitWhileStmt(Exp exp, Block block) {
		while (exp.accept(this).toBool())
			block.accept(this);
		return null;
	}

	@Override
	public Value visitBlock(StmtSeq stmtSeq) {
		env.enterScope();
		stmtSeq.accept(this);
		env.exitScope();
		return null;
	}

	// dynamic semantics for sequences of statements
	// no value returned by the visitor

	@Override
	public Value visitSingleStmt(Stmt stmt) {
		stmt.accept(this);
		return null;
	}

	@Override
	public Value visitMoreStmt(Stmt first, StmtSeq rest) {
		first.accept(this);
		rest.accept(this);
		return null;
	}

	// dynamic semantics of expressions; a value is returned by the visitor

	@Override
	public IntValue visitAdd(Exp left, Exp right) {
		return new IntValue(left.accept(this).toInt() + right.accept(this).toInt());
	}

	@Override
	public IntValue visitIntLiteral(int value) {
		return new IntValue(value);
	}

	@Override
	public IntValue visitMul(Exp left, Exp right) {
		return new IntValue(left.accept(this).toInt() * right.accept(this).toInt());
	}

	@Override
	public IntValue visitSign(Exp exp) {
		return new IntValue(-exp.accept(this).toInt());
	}

	@Override
	public Value visitSimpleVariable(Variable var) {
		return env.lookup(var);
	}

	@Override
	public BoolValue visitNot(Exp exp) {
		return new BoolValue(!exp.accept(this).toBool());
	}

	@Override
	public BoolValue visitAnd(Exp left, Exp right) {
		return new BoolValue(left.accept(this).toBool() && right.accept(this).toBool());
	}

	@Override
	public BoolValue visitBoolLiteral(boolean value) {
		return new BoolValue(value);
	}

	@Override
	public BoolValue visitEq(Exp left, Exp right) {
		return new BoolValue(left.accept(this).equals(right.accept(this)));
	}

	@Override
	public PairValue visitPairLit(Exp left, Exp right) {
		return new PairValue(left.accept(this), right.accept(this));
	}

	@Override
	public Value visitFst(Exp exp) {
		return exp.accept(this).toPair().getFstVal();
	}

	@Override
	public Value visitSnd(Exp exp) {
		return exp.accept(this).toPair().getSndVal();
	}

	@Override
	public ArrayValue visitArrayLiteral(ExpSeq es) {
		return new ArrayValue(es.accept(this).toExpSeq());
	}

	@Override
	public ExpSeqValues visitSingleExp(Exp exp) {
		ExpSeqValues list = new ExpSeqValues();
		list.push(exp.accept(this));
 		return list;
	}

	@Override
	public ExpSeqValues visitMoreExp(Exp first, ExpSeq rest) {
		ExpSeqValues list = rest.accept(this).toExpSeq();
		list.push(first.accept(this));
		return list;
	}

	@Override
	public IntValue visitLength(Exp exp) {
		return new IntValue(exp.accept(this).toArrayValue().length);
	}

	 @Override
    public Value visitArrayAcc(Exp left, Exp right) {
       try {
           return left.accept(this).toArrayValue()[right.accept(this).toInt()];
       } catch (ArrayIndexOutOfBoundsException e) {
           throw new InterpreterException(e);
       }
    }
}

