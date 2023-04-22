<?php
  	require_once("errorRep.php");
  	require_once("connect.php");
    require_once("utilities.php");
    session_start();

    if(isset($_SESSION["user"]))
        exit(header('Location: ../index.php'));
    if(isset($_COOKIE["login"])) {
        if(handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }

  	// Controllo di essere entrato nella pagina premendo il form
  	if(!isset($_POST['submit']))
    	exit(header('Location: ../index.php'));

	// check for isset of form
    if (!isset($_POST["pass"]) || !isset($_POST["confirm"]))
        err_handling("no_pwd", "../registration_form.php");
    if (!isset($_POST["firstname"]) || !isset($_POST["lastname"]))
        err_handling("no_name", "../registration_form.php");
    if (!isset($_POST["email"])) err_handling("no_email", "../index.php");

	// get variables
    $firstname = trim($_POST["firstname"]);
    $lastname = trim($_POST["lastname"]);
    $email = trim($_POST["email"]);
    $pwd1 = trim($_POST["pass"]);
    $pwd2 = trim($_POST["confirm"]);
    $nwl = (isset($_POST["nwl"]) && $_POST["nwl"] == "on");

    // pwd validation
    if(strlen($pwd1) < 8)
      	err_handling("invalid_pwd", "../registration_form.php");
    // PASSWORD non matching
    if($pwd1 != $pwd2)
        err_handling("diff_pwd", "../registration_form.php");

	// name validation
    define("NAMEREG", "/^[a-zA-Z' ]{1,52}$/");
    if(!preg_match(NAMEREG, $firstname) || !preg_match(NAMEREG, $lastname))
      	err_handling("invalid_name", "../registration_form.php");
    // mail validation
    if(!filter_var($email, FILTER_VALIDATE_EMAIL))
      	err_handling("invalid_email", "../registration_form.php");

    $dup_errno = 1062;
    $query = "INSERT INTO users (firstname, lastname, email, pass, nwl) VALUES(?, ?, ?, ?, ?);";
    $stmt = mysqli_stmt_init($conn);
    $hashed = password_hash($pwd1, PASSWORD_DEFAULT);
    if($errno = exec_query($stmt, $res, $query, "ssssi", $firstname, $lastname, $email, $hashed, $nwl)) {
        if ($errno != $dup_errno)
            exit(header('Location: ../error_pages/500.php'));
        err_handling("maildup", "../registration_form.php");
    }

    // dir for user files (if fail, delete from db for consistency)
    if (!mkdir("../../../users/".mysqli_insert_id($conn), 0777, true)) {
        $query = "DELETE FROM users WHERE id = ?;";
        exec_query($stmt, $res, $query, "i", mysqli_insert_id($conn));
        exit(header('Location: ../error_pages/500.php'));
    }

    mysqli_stmt_close($stmt);
    mysqli_close($conn);

    header('Location: ../index.php?error=regok');
?>
