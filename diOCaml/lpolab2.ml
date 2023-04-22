(* ES 1 i *)

let cat =
	let rec aux acc = function
		x :: t -> aux(acc ^ x) t
		| _ -> acc
	in aux "";;

let cat = List.fold_left (^) "";;

(* ES 1 ii *)

let filter p l =
	let rec aux acc = function
		x :: t -> aux(if p x then x :: acc else acc) t
		| _ -> List.rev acc
	in aux [] l;;

let filter p l = List.rev(List.fold_left(fun acc x -> if p x then x :: acc else acc) [] l);;

(* ES 2 i *)

let init n f =
	let rec aux acc i =
		if i >= 0 then aux ((f i) :: acc) (i - 1)
		else acc
	in if n >= 0 then aux [] (n - 1) else raise (Invalid_argument "init");;

(* ES 2 ii *)

let combine l1 l2 =
	let rec aux acc l1 l2 = match l1, l2 with
		x :: t1, y :: t2 -> aux((x, y) :: acc) t1 t2
		| [], [] -> List.rev acc
		| _ -> raise (Invalid_argument "combine")
	in aux [] l1 l2;;

(* ES 3 i *)

let min_el =
	let rec aux x = function
		y :: t2 -> aux (min x y) t2
		| _ -> x
	in function x :: t1 -> Some (aux x t1) | _ -> None;;

(* ES 3 ii *)

type direction = North | East | South | West;;

(* ES 3 iii *)

let versor = function
	North -> (0, 1)
	| East -> (1, 0)
	| South -> (0, -1)
	| _ -> (-1, 0);;

(* ES 3 iv *)

type action = Turn of direction | Step of int;;

(* ES 3 v *)

let scalar s (x, y) = (s * x, s * y);;

let add (x1, y1) (x2, y2) = (x1 + x2, y1 + y2);;

let move (d, xy) = function
	Turn t -> (t, xy) 
	| Step s -> (d, add xy (scalar s (versor d)));;

(* ES 3 vi *)

let do_all ((d, (x, y)) as dir) = List.fold_left move dir;;
(* oppure *)
let do_all = List.fold_left move;;

(* ES 3 vii *)

type 'a list_exp_ast = 
	Empty 
	| Single of 'a
	| Concat of 'a list_exp_ast * 'a list_exp_ast;;

(* ES 3 viii *)

let rec eval = function
	Empty -> []
	| Single a -> [a]
	| Concat (a1, a2) -> eval a1 @ eval a2;;
