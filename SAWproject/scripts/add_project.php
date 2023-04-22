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

  	if(!isset($_POST['submit']) || !isset($_POST["proj_name"]))
    	exit(header('Location: ../show_projects.php'));

    // no htmlentities because of next regex control
    $proj_name = trim($_POST["proj_name"]);

    define("PROJREG", "/^[a-zA-Z_0-9]{1,52}$/");
    if(!preg_match(PROJREG, $proj_name))
      	exit(header('Location: ../show_projects.php?error=invalid_name'));

    if(is_dir("../../../users/".$_SESSION["user"]."/".$proj_name))
        exit(header('Location: ../show_projects.php?error=projdup'));
    if (!mkdir("../../../users/".$_SESSION["user"]."/".$proj_name))
	    exit(header('Location: ../error_pages/500.php'));

    $query = "INSERT INTO projects (user_id, name) VALUES (?, ?);";
    $stmt = mysqli_stmt_init($conn);

    // if query fails, rm dir created before for consistency
    if(exec_query($stmt, $res, $query, "is", $_SESSION["user"], $proj_name)) {
        rmdir("../../../users/".$_SESSION["user"]."/".$proj_name);
        exit(header('Location: ../error_pages/500.php'));
    }

    mysqli_stmt_close($stmt);
    mysqli_close($conn);
    header('Location: ../show_projects.php?error=addok');
?>
