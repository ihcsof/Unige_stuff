(* lpo21#6# *)

(* PROD *)
(* val prod : int list -> int = <fun> *)
(* 1 elem neutro prodotto *)
let rec prod = function
	x::t -> x * prod t
	| _ -> 1;;
	
(* ottimizzazione con 0 *)
(* con #trace prod si nota che si blocca al primo 0 *)

let rec prod = function
	x::t -> if(x = 0) then 0 else (x * prod t)
	| _ -> 1;;
	
(* MEMBER *)
(* val member : 'a -> 'a list -> bool = <fun> *)
(* (x = el) per primo per short-circuit eval *)
let rec member el = function
	x::t -> (x = el) || member el t 
	| _ -> false;;
	
(* versione con aux *)
let member el =
	let rec aux = function
		x::t -> (x = el) || aux t
		| _ -> false
in aux;;

(* INSERT *)

(* versione 1 *)
let insert el l = if (member el l) then l else l @ [el];;

(* versione 2 (aux) per non passare il param nelle chiamate ric. (el e' nello scope) *)
let insert el =
	let rec aux = function
		x::t -> x::(if(x = el) then t else (aux t))
		| _ -> [el];;
in aux;;
	
(* ODD *)
(* val odd : 'a list -> 'a list = <fun> *)
let rec odd = function
	x::_::t -> x::odd t
	| other -> other;;
	
(* ORD INSERT (aux) per non passare il param nelle chiamate ric. (el e' nello scope) *)
(* val insert : 'a -> 'a list -> 'a list = <fun> *)
let ord_insert el =
	let rec aux = function
		x::t as l -> if x < el then x::aux t else if x = el then l else el::l
		| _ -> [el];;
in aux;;

(* MERGE *)
(* val merge : 'a list * 'a list -> 'a list = <fun> *)
let rec merge = function
	x::t1, y::t2 -> if x<y then x::merge(t1, y::t2) 
			else if y<x then y::merge(t2, x::t1) 
			else x::merge(t1, t2) 
	| [], l2 -> l2
	| l1, _ -> l1;;
	
(* MERGE CURRIED *)
(* val curried_merge : 'a list -> 'a list -> 'a list = <fun> *)
let rec curried_merge l1 l2 = match l1, l2 with
	x::t1, y::t2 -> if x<y then x::curried_merge t1 (y::t2)
			else if y<x then y::curried_merge t2 (x::t1)
			else x::curried_merge t1 t2 
	| [], l2 -> l2
	| l1, _ -> l1;;
