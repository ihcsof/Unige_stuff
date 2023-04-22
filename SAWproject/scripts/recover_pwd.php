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

    if(!isset($_SESSION["recovery"]))
        exit(header("Location: ../index.php"));

    if(!isset($_POST["submit"]) || !isset($_POST["pass"]) || !isset($_POST["confirm"]))
        exit(header("Location: ../index.php"));

    $email = $_SESSION["recovery"];
    $_SESSION = array();
    session_destroy();

    $pwd1 = trim($_POST['pass']);
    $pwd2 = trim($_POST["confirm"]);
    // Validazione pwd
    if(strlen($pwd1) < 8)
      	exit(header("Location: ../index.php?error=recoverpwderr"));
    // PASSWORD NON MATCHATE
    if($pwd1 != $pwd2)
        exit(header("Location: ../index.php?error=recoverpwderr"));

    $stmt = mysqli_stmt_init($conn);
    $query = "UPDATE users SET pass = ? WHERE email = ?;";
    $hashed = password_hash($pwd1, PASSWORD_DEFAULT);

    if(exec_query($stmt, $res, $query, "ss", $hashed, $email))
        exit(header('Location: ../error_pages/500.php'));

    header("Location: ../index.php?error=recoverpwdok");

    mysqli_stmt_close($stmt);
    mysqli_close($conn);
?>
