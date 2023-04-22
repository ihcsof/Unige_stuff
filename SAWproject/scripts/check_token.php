<?php
	require_once("errorRep.php");
	require_once("connect.php");
	require_once("utilities.php");
	require_once("mail_init.php");
	session_start();

	if(isset($_SESSION["user"]))
        exit(header('Location: ../index.php'));
    if(isset($_COOKIE["login"])) {
        if(handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }

	if (!isset($_GET["hash"]))
		exit(header("Location: ../index.php"));

	$hash = $_GET["hash"];
	$query = "SELECT * FROM pwd_tokens WHERE token = ?";
	$stmt = mysqli_stmt_init($conn);

	if (exec_query($stmt, $res, $query, "s", $hash))
		exit(header('Location: ../error_pages/500.php'));

	if (!($token = mysqli_fetch_assoc($res)))
		exit(header("Location: ../index.php?error=tok_invalid"));

	$query = "DELETE FROM pwd_tokens WHERE token = ?";
	if (exec_query($stmt, $res, $query, "s", $hash))
		exit(header('Location: ../error_pages/500.php'));

	// If token exists & it's right, but it expired
	if (time() > $token["expires"])
		exit(header("Location: ../login_form.php?error=tok_expired"));

	// Token valid: set session
	$_SESSION["recovery"] = $token["email"];
	header("Location: ../recover_form.php");

	mysqli_stmt_close($stmt);
    mysqli_close($conn);
?>
