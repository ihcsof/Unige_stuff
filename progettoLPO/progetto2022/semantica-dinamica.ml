(* dynamic semantics of the language *)

type variable = SimpleVariable of string;;

(* AST of expressions *)
type
  exp = Add of exp * exp | Mul of exp * exp | And of exp * exp | Eq of exp * exp | PairLit of exp * exp | Fst of exp | Snd of exp | Sign of exp | Not of exp | IntLiteral of int | BoolLiteral of bool | Var of variable | ArrayLiteral of exp_seq | ArrayAccess of exp * exp | Length of exp 
and
  exp_seq = SingleExp of exp | MoreExp of exp * exp_seq;;

(* AST of statements and sequence of statements, mutually recursive *)
type
  stmt = AssignStmt of variable * exp | VarStmt of variable * exp | PrintStmt of exp | IfStmt of exp * block * block | WhileStmt of exp * block
and
  block = NoBlock | Block of stmt_seq
and
  stmt_seq = SingleStmt of stmt | MoreStmt of stmt * stmt_seq;;

(* AST of programs *)
type prog = SimpleProg of stmt_seq;;

(* values *)

(* examples
    PairLit(IntLiteral 2,BoolLiteral false) is  (2,false)
    PairLit(IntLiteral 2,PairLit(IntLiteral 3,BoolLiteral true)) is (2,(3,true)) 
*)

type value = IntValue of int | BoolValue of bool | PairValue of value*value | ArrayValue of value list;;

(* dynamic environments *)

type scope = (variable * value) list;;
type dynamic_env = scope list;;

exception UndeclaredVariable of variable;;

exception AlreadyDeclaredVariable of variable;;

let empty_scope:scope = [];; 

let starting_env:dynamic_env = [empty_scope];; (* just the empty top-level scope *)

let enter_scope : dynamic_env -> dynamic_env = fun env -> empty_scope::env;; (* enters a new nested scope *)

let exit_scope : dynamic_env -> dynamic_env = function (* removes the innermost scope, only needed for the dynamic semantics *)
    _::env -> env
  | [] -> failwith "assertion error";; (* should never happen *)

(* variable lookup *)

(* resolve uses List.mem_assoc 
   examples:
   List.mem_assoc (SimpleVariable "x") [(SimpleVariable "x",IntValue 3);(SimpleVariable "y",BoolValue false)]=true;;
   List.mem_assoc (SimpleVariable "y") [(SimpleVariable "x",IntValue 3);(SimpleVariable "y",BoolValue false)]=true;;
   List.mem_assoc (SimpleVariable "z") [(SimpleVariable "x",IntValue 3);(SimpleVariable "y",BoolValue false)]=false;;
*)

(* resolve : variable -> dynamic_env -> scope *)

let rec resolve : variable -> dynamic_env -> scope = fun var -> function
    scope::(env:dynamic_env) -> if(List.mem_assoc var scope) then scope else resolve var env
  | [] -> raise (UndeclaredVariable var);;

(* lookup uses List.assoc 
   examples:
   List.assoc (SimpleVariable "x") [(SimpleVariable "x",IntValue 3);(SimpleVariable "y",BoolValue false)]=IntValue 3;;
   List.assoc (SimpleVariable "y") [(SimpleVariable "x",IntValue 3);(SimpleVariable "y",BoolValue false)]=BoolValue false;;
   List.assoc (SimpleVariable "z") [(SimpleVariable "x",IntValue 3);(SimpleVariable "y",BoolValue false)];; raises exception Not_found
*)

let lookup : variable -> dynamic_env -> value = fun variable env -> List.assoc variable (resolve variable env);;

(* variable declaration *)

(* example: dec x value env1 = env2 means that 'env2' is the new environment after declaring variable 'x' initialized with value 'value' in the environment 'env1' *)  
(* dec uses List.mem_assoc, see the examples above *)

let dec : variable -> value -> dynamic_env -> dynamic_env = fun var value -> function
    scope::env -> if(List.mem_assoc var scope) then raise (AlreadyDeclaredVariable var) else ((var,value)::scope)::env
  | [] -> failwith "assertion error";; (* should never happen *)

(* variable update, only needed for the dynamic semantics *)
(* update uses List.mem_assoc, see the examples above *) 

let rec update : variable -> value -> dynamic_env -> dynamic_env = fun var value -> function
    scope::env -> if(List.mem_assoc var scope) then ((var,value)::scope)::env else scope::update var value env
  | [] -> raise (UndeclaredVariable var);;

(* dynamic errors *)

exception ExpectingTypeError of string;; (* dynamic conversion error *) 

(* auxiliary functions *)

(* dynamic conversion to int type *)
(* toInt : value -> int *)

let toInt = function
    IntValue i -> i |
    _ -> raise (ExpectingTypeError "int")

(* dynamic conversion to bool type *)
(* toBool : value -> bool *)

let toBool = function
    BoolValue b -> b |
    _ -> raise (ExpectingTypeError "bool")

(* toPair : value -> value * value *)
(* dynamic conversion to product  type *)

let toPair = function
    PairValue (e1,e2) -> e1,e2 |
    _ -> raise (ExpectingTypeError "pair");;

(* toArrayValue : value -> value list *)
(* dynamic conversion to product  type *)

let toArrayValue = function
    ArrayValue l -> l |
    _ -> raise (ExpectingTypeError "array");;

(* conversion to string *)

(* to_string : value -> string *)

let rec to_string = function
    IntValue i -> string_of_int(i) 
  | BoolValue b -> string_of_bool(b) 
  | PairValue(v1,v2) -> "(" ^ to_string v1 ^ "," ^ to_string v2 ^ ")"
  | ArrayValue l -> String.concat ";" (List.map to_string l);;

(* auxiliary printing function *)

(* println : value -> unit *)

let println value = print_string (to_string value ^ "\n");;

(* mutually recursive
    evalExp : dynamic_env -> exp -> value 
    evalExpSeq : dynamic_env -> exp_seq -> value list 
*)

(* 
   evalExp env exp = val means that expressions 'exp' successfully evaluates to 'val' in the environment 'env'
   evalExpSeq env expSeq = valSeq means that expressions 'expSeq' successfully evaluates to 'valSeq' in the environment 'env' 
*)

let rec evalExp env=function 
    Add(exp1,exp2) -> IntValue(toInt(evalExp env exp1)+toInt(evalExp env exp2))
  | Mul(exp1,exp2) -> IntValue(toInt(evalExp env exp1)*toInt(evalExp env exp2))
  | And(exp1,exp2) -> BoolValue(toBool(evalExp env exp1)&&toBool(evalExp env exp2))
  | Eq(exp1,exp2) -> BoolValue(evalExp env exp1=evalExp env exp2)
  | PairLit(exp1,exp2) -> PairValue(evalExp env exp1,evalExp env exp2)
  | Fst exp -> fst (toPair(evalExp env exp))
  | Snd exp -> snd (toPair(evalExp env exp))
  | Sign exp -> IntValue(-toInt(evalExp env exp))
  | Not exp -> BoolValue(not (toBool(evalExp env exp)))
  | IntLiteral i -> IntValue i
  | BoolLiteral b -> BoolValue b
  | Var var -> lookup var env
  | ArrayLiteral exp_seq -> ArrayValue (evalExpSeq env exp_seq)
  | ArrayAccess (array_exp,index_exp) -> List.nth (toArrayValue (evalExp env array_exp)) (toInt (evalExp env index_exp))
  | Length exp -> IntValue(List.length (toArrayValue (evalExp env exp)))

and
  
  evalExpSeq env=function 
    SingleExp exp -> [evalExp env exp]
  | MoreExp(exp,exp_seq) -> evalExp env exp::evalExpSeq env exp_seq;;

(* mutually recursive
   executeStmt : dynamic_env -> stmt -> dynamic_env
   executeBlock : dynamic_env -> block -> dynamic_env
   executeStmtSeq : dynamic_env -> stmt_seq -> dynamic_env
*)

(* executeStmt env1 'stmt' = env2 means that the execution of statement 'stmt' in environment 'env1' successfully returns the new environment 'env2' *)
(* executeBlock env1 block = env2 means that the execution of block 'block' in environment 'env1' successfully returns the new environment 'env2' *)
(* executeStmtSeq env1 stmt_seq = env2 means that the execution of sequence 'stmt_seq' in environment 'env1' successfully returns the new environment 'env2' *)
(* executeStmt, executeBlock and executeStmtSeq write on the standard output if some 'print' statement is executed *)

let rec executeStmt env=function
    AssignStmt(var,exp) -> update var (evalExp env exp) env
  | VarStmt(var,exp) -> dec var (evalExp env exp) env
  | PrintStmt exp -> let _=println (evalExp env exp) in env
  | IfStmt(exp,thenBlock,elseBlock) ->
        if toBool(evalExp env exp) then  
          executeBlock env thenBlock  
        else 
          executeBlock env elseBlock
  | WhileStmt(exp,block) as whileStmt ->
    if toBool(evalExp env exp) then
      let env2=executeBlock env block in executeStmt env2 whileStmt
    else env
            
and
  
  executeBlock env=function (* note the differences with the static semantics *)
    NoBlock -> env
  | Block stmt_seq -> exit_scope (executeStmtSeq (enter_scope env) stmt_seq)

and 

  executeStmtSeq env=function 
    SingleStmt stmt -> executeStmt env stmt
  | MoreStmt(stmt,stmt_seq) -> executeStmtSeq (executeStmt env stmt) stmt_seq;;

(* executeProg : prog -> unit *)
(* executeProg prog = () means that program 'prog' has been executed successfully, by possibly writing on the standard output *)

let executeProg = function SimpleProg stmt_seq -> let _=executeStmtSeq starting_env stmt_seq in ();;

(* some simple tests with the dynamic semantics *)

let stmt1=VarStmt(SimpleVariable "x",IntLiteral 0);;

let stmt2_1=PrintStmt(Var(SimpleVariable "x"));;

let stmt2_2=AssignStmt(SimpleVariable "x",Add(Var(SimpleVariable "x"),IntLiteral 1));;

let stmt2=WhileStmt(Not(Eq(Var(SimpleVariable "x"),IntLiteral 10)),Block(MoreStmt(stmt2_1,SingleStmt stmt2_2)));;
  
let prog1=SimpleProg(MoreStmt(stmt1,SingleStmt stmt2));;

executeProg prog1;; (* 'var x=0; while(!(x==10)){print x;x=x+1}' prints 0 1 2 3 4 5 6 7 8 9 *)

let arrayLit=ArrayLiteral(MoreExp(IntLiteral 0,SingleExp (IntLiteral 1)));;

let stmt1=VarStmt(SimpleVariable "a",arrayLit);;

let stmt2=VarStmt(SimpleVariable "ln",Length(Var(SimpleVariable "a")));;

let stmt3=VarStmt(SimpleVariable "i",IntLiteral 0);;

let stmt4_1=PrintStmt(ArrayAccess(Var(SimpleVariable "a"),Var(SimpleVariable "i")));;

let stmt4_2=AssignStmt(SimpleVariable "i",Add(Var(SimpleVariable "i"),IntLiteral 1));;

let stmt4=WhileStmt(Not(Eq(Var(SimpleVariable "i"),Var(SimpleVariable "ln"))),Block(MoreStmt(stmt4_1,SingleStmt stmt4_2)));;

let prog2=SimpleProg(MoreStmt(stmt1,MoreStmt(stmt2,MoreStmt(stmt3,SingleStmt stmt4))));;

executeProg prog2;; (* 'var a=[0;1]; var ln=length a; var i=0;while(!(i==ln)){print a[i]; i=i+1}' prints 0 1 *)
