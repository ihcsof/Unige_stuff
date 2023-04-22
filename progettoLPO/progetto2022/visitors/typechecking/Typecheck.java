package progetto2022.visitors.typechecking;

import static progetto2022.visitors.typechecking.SimpleType.*;

import progetto2022.environments.EnvironmentException;
import progetto2022.environments.GenEnvironment;
import progetto2022.parser.ast.Block;
import progetto2022.parser.ast.Exp;
import progetto2022.parser.ast.Stmt;
import progetto2022.parser.ast.StmtSeq;
import progetto2022.parser.ast.Variable;
import progetto2022.visitors.Visitor;
import progetto2022.parser.ast.ExpSeq;

public class Typecheck implements Visitor<Type> {

	private final GenEnvironment<Type> env = new GenEnvironment<>();

	// useful to typecheck binary operations where operands must have the same type
	private void checkBinOp(Exp left, Exp right, Type type) {
		type.checkEqual(left.accept(this));
		type.checkEqual(right.accept(this));
	}

	// static semantics for programs; no value returned by the visitor

	@Override
	public Type visitSimpleProg(StmtSeq stmtSeq) {
		try {
			stmtSeq.accept(this);
		} catch (EnvironmentException e) { // undeclared variable
			throw new TypecheckerException(e);
		}
		return null;
	}

	// static semantics for statements; no value returned by the visitor

	@Override
	public Type visitAssignStmt(Variable v, Exp exp) {
		var found = env.lookup(v);
		found.checkEqual(exp.accept(this));
		return null;
	}

	@Override
	public Type visitPrintStmt(Exp exp) {
		exp.accept(this);
		return null;
	}

	@Override
	public Type visitVarStmt(Variable v, Exp exp) {
		env.dec(v, exp.accept(this));
		return null;
	}

	@Override
	public Type visitIfStmt(Exp exp, Block thenBlock, Block elseBlock) {
		BOOL.checkEqual(exp.accept(this));
		thenBlock.accept(this);
		if (elseBlock != null)
			elseBlock.accept(this);
		return null;
	}

	@Override
	public Type visitWhileStmt(Exp exp, Block block) {
		BOOL.checkEqual(exp.accept(this));
		block.accept(this);
		return null;
	}

	@Override
	public Type visitBlock(StmtSeq stmtSeq) {
		env.enterScope();
		stmtSeq.accept(this);
		env.exitScope();
		return null;
	}

	// static semantics for sequences of statements
	// no value returned by the visitor

	@Override
	public Type visitSingleStmt(Stmt stmt) {
		stmt.accept(this);
		return null;
	}

	@Override
	public Type visitMoreStmt(Stmt first, StmtSeq rest) {
		first.accept(this);
		rest.accept(this);
		return null;
	}

	// static semantics of expressions; a type is returned by the visitor

	@Override
	public SimpleType visitAdd(Exp left, Exp right) {
		checkBinOp(left, right, INT);
		return INT;
	}

	@Override
	public SimpleType visitIntLiteral(int value) {
		return INT;
	}

	@Override
	public SimpleType visitMul(Exp left, Exp right) {
		checkBinOp(left, right, INT);
		return INT;
	}

	@Override
	public SimpleType visitSign(Exp exp) {
		INT.checkEqual(exp.accept(this));
		return INT;
	}

	@Override
	public Type visitSimpleVariable(Variable var) {
		return env.lookup(var);
	}

	@Override
	public SimpleType visitNot(Exp exp) {
		BOOL.checkEqual(exp.accept(this));
		return BOOL;
	}

	@Override
	public SimpleType visitAnd(Exp left, Exp right) {
		checkBinOp(left, right, BOOL);
		return BOOL;
	}

	@Override
	public SimpleType visitBoolLiteral(boolean value) {
		return BOOL;
	}

	@Override
	public SimpleType visitEq(Exp left, Exp right) {
		left.accept(this).checkEqual(right.accept(this));
		return BOOL;
	}

	@Override
	public PairType visitPairLit(Exp left, Exp right) {
		return new PairType(left.accept(this), right.accept(this));
	}

	@Override
	public Type visitFst(Exp exp) {
		return exp.accept(this).getFstPairType();
	}

	@Override
	public Type visitSnd(Exp exp) {
		return exp.accept(this).getSndPairType();
	}

	@Override
	public SimpleType visitArrayLiteral(ExpSeq es) {
		es.accept(this);
		return ARRAY;
	}

	@Override
	public SimpleType visitSingleExp(Exp exp) {
 		INT.checkEqual(exp.accept(this));
		return ARRAY;
	}

	@Override
	public SimpleType visitMoreExp(Exp first, ExpSeq rest) {
		INT.checkEqual(first.accept(this));
		rest.accept(this);
		return ARRAY;
	}
	
	@Override
	public SimpleType visitLength(Exp exp) {
		ARRAY.checkEqual(exp.accept(this));
		return INT;
	}

	@Override
	public SimpleType visitArrayAcc(Exp left, Exp right) {
		ARRAY.checkEqual(left.accept(this));
      INT.checkEqual(right.accept(this));
      return INT;
	}
}
