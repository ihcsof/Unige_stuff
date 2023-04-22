<?php
    require_once("errorRep.php");
    require_once("connect.php");
    require_once("utilities.php");

    if(isset($_SESSION["user"]))
        exit(header('Location: ../index.php'));
    if (isset($_COOKIE["login"])) {
        if(handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }

    $email = trim($_POST['email']);

    $query = "SELECT * FROM users WHERE email = ?;";
    $stmt = mysqli_stmt_init($conn);

    if(exec_query($stmt, $res, $query, "s", $email)) die(0);

    echo mysqli_num_rows($res) == 1;

    mysqli_stmt_close($stmt);
    mysqli_close($conn);
?>
