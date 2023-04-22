package progetto2022.visitors;

import progetto2022.parser.ast.Block;
import progetto2022.parser.ast.Exp;
import progetto2022.parser.ast.Stmt;
import progetto2022.parser.ast.StmtSeq;
import progetto2022.parser.ast.Variable;
import progetto2022.parser.ast.ExpSeq;
import progetto2022.parser.ast.ArrayLiteral;
import progetto2022.parser.ast.MoreExp;
import progetto2022.parser.ast.SingleExp;
import progetto2022.parser.ast.ArrayAcc;

public interface Visitor<T> {
	T visitAdd(Exp left, Exp right);

	T visitAssignStmt(Variable var, Exp exp);

	T visitIntLiteral(int value);

	T visitEq(Exp left, Exp right);

	T visitMoreStmt(Stmt first, StmtSeq rest);

	T visitMul(Exp left, Exp right);

	T visitPrintStmt(Exp exp);

	T visitSimpleProg(StmtSeq stmtSeq);

	T visitSign(Exp exp);

	T visitSimpleVariable(Variable var); // the only corner case ...

	T visitSingleStmt(Stmt stmt);

	T visitVarStmt(Variable var, Exp exp);

	T visitNot(Exp exp);

	T visitAnd(Exp left, Exp right);

	T visitBoolLiteral(boolean value);

	T visitIfStmt(Exp exp, Block thenBlock, Block elseBlock);

	T visitWhileStmt(Exp exp, Block block);

	T visitBlock(StmtSeq stmtSeq);

	T visitPairLit(Exp left, Exp right);

	T visitFst(Exp exp);

	T visitSnd(Exp exp);

	T visitArrayLiteral(ExpSeq es);

	T visitSingleExp(Exp exp);

	T visitMoreExp(Exp first, ExpSeq rest);

	T visitLength(Exp exp);

	T visitArrayAcc(Exp left, Exp right);
}
