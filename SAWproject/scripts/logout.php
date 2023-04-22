<?php
    require_once("connect.php");
    require_once("utilities.php");

    if(!isset($_GET["logout"]))
        exit(header('Location: ../index.php'));
    session_start();

    if(!isset($_SESSION["user"]))
        exit(header('Location: ../index.php'));

    if(isset($_COOKIE["login"])) {
        destroy_cookie("login");

        $query = "DELETE FROM login_cookies WHERE userid = ?;";
        $stmt = mysqli_stmt_init($conn);

        if(exec_query($stmt, $res, $query, "i", $_SESSION["user"]))
            exit(header('Location: ../error_pages/500.php'));
    }

    $_SESSION = array();
    session_destroy();
    header('Location: ../index.php');
?>
