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

  	// Controllo di essere entrato nella pagina premendo il form
  	if(!isset($_POST['submit']))
    	exit(header('Location: ../update_pwd_form.php'));

	// check for isset of form
    if (!isset($_POST["old"]) || !isset($_POST["new"]) || !isset($_POST["confirm"]))
        exit(header('Location: ../update_pwd_form.php?error=no_pwd'));

	// get variables
    $old = trim($_POST["old"]);
    $new = trim($_POST["new"]);
    $confirm = trim($_POST["confirm"]);

    // Validazione pwd
    if(strlen($new) < 8)
      	exit(header('Location: ../update_pwd_form.php?error=invalid_pwd'));
    // PASSWORD NON MATCHATE
    if($new != $confirm)
        exit(header('Location: ../update_pwd_form.php?error=diff_pwd'));

    $query = "SELECT pass FROM users WHERE id=?;";
    $stmt = mysqli_stmt_init($conn);

    if(exec_query($stmt, $res, $query, "i", $_SESSION["user"]))
        exit(header('Location: ../error_pages/500.php'));

    if(!($user = mysqli_fetch_assoc($res)))
        exit(header('Location: ../error_pages/500.php'));
    if(!password_verify($old, $user["pass"]))
        exit(header('Location: ../update_pwd_form?error=wrongold'));

    // Registrazione su DB
    $query = "UPDATE users SET pass = ? WHERE id = ?;";
    $hashed = password_hash($new, PASSWORD_DEFAULT);
    if(exec_query($stmt, $res, $query, "si", $hashed, $_SESSION["user"]))
        exit(header('Location: ../error_pages/500.php'));

    mysqli_stmt_close($stmt);
    mysqli_close($conn);
    header('Location: ../show_profile.php?error=updatepwdok');
?>
