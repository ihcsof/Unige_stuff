<?php
    session_start();
    require_once("errorRep.php");
  	require_once("connect.php");
    require_once("utilities.php");

    if(!isset($_SESSION["user"])) {
        if (!isset($_COOKIE["login"]))
            exit(header('Location: ../index.php'));
        if(!handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }

  	// 1: Controllo di essere entrato nella pagina premendo il form
  	if(!isset($_POST['submit']))
    	exit(header('Location: ../show_profile.php'));

	// check for isset of form
    if (!isset($_POST["firstname"]) || !isset($_POST["lastname"]))
        err_handling("no_name", "../show_profile.php");
    if (!isset($_POST["email"])) err_handling("no_email", "../show_profile.php");

	// get variables
    $firstname = trim($_POST["firstname"]);
    $lastname = trim($_POST["lastname"]);
    $email = trim($_POST["email"]);
    $nwl = (isset($_POST["nwl"]) && $_POST["nwl"] == "on");

	// validazione nome
    define("NAMEREG", "/^[a-zA-Z' ]{1,52}$/");
    if(!preg_match(NAMEREG, $firstname) || !preg_match(NAMEREG, $lastname))
      	err_handling("invalid_name", "../show_profile.php");
    // Validazione mail
    if(!filter_var($email, FILTER_VALIDATE_EMAIL))
      	err_handling("invalid_email", "../show_profile.php");

    // Registrazione su DB
    $dup_errno = 1062;
    $query = "UPDATE users SET firstname = ?, lastname = ?, email = ?, nwl = ? WHERE id = ?;";
    $stmt = mysqli_stmt_init($conn);

    if($errno = exec_query($stmt, $res, $query, "sssii", $firstname, $lastname, $email, $nwl, $_SESSION["user"])) {
        if ($errno != $dup_errno)
            exit(header('Location: ../error_pages/500.php'));
        exit(header('Location: ../show_profile.php?error=maildup'));
    }

    mysqli_stmt_close($stmt);
    mysqli_close($conn);
    header('Location: ../show_profile.php?error=updateok');
?>
