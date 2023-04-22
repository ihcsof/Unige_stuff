<?php
    session_start();
    require_once("errorRep.php");

    if(!isset($_SESSION["user"])) {
        if (!isset($_COOKIE["login"]))
            exit(header('Location: ../index.php'));
        if(!handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }

    if(!isset($_POST["del"]) || $_POST["del"] != "GO")
        exit(header('Location: ../show_profile.php'));

    if(!unlink("../../../users/".$_SESSION["user"]."/icon"))
        die("call_err");

    echo "OK";
?>
