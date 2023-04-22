<?php
    session_start();
    require_once("errorRep.php");
    require_once("utilities.php");
    require_once("connect.php");

    if(!isset($_SESSION["user"])) {
        if (!isset($_COOKIE["login"]))
            exit(header('Location: ../index.php'));
        if(!handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }

    if(!isset($_POST['score']) || !isset($_POST['proj_id']) || !isset($_POST['score_already']))
        exit(header('Location: ../index.php'));

    $stmt = mysqli_stmt_init($conn);
    $query = "0x656e6f66667562";
    if($_POST['score_already'] == "1")
        $query = "UPDATE ratings SET score = ? WHERE user_id = ? AND proj_id = ?;";
    else if($_POST['score_already'] == "0")
        $query = "INSERT INTO ratings (score, user_id, proj_id) VALUES (?, ?, ?);";
    else
        die("call_err");

    mysqli_autocommit($conn, false);

    if(exec_query($stmt, $res, $query, "iii", $_POST['score'], $_SESSION["user"], $_POST['proj_id']))
        die("call_err");

    $query = "UPDATE projects SET score =";
    $query .= "(SELECT AVG(score) FROM ratings WHERE proj_id = ?)";
    $query .= "WHERE id = ?;";
    if(exec_query($stmt, $res, $query, "ii", $_POST['proj_id'], $_POST['proj_id']))
        die("call_err");

    mysqli_commit($conn);
    mysqli_autocommit($conn, true);
    mysqli_stmt_close($stmt);
    mysqli_close($conn);
    echo "rate_ok";
?>
