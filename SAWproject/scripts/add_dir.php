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

    if(!isset($_POST["path"]) || !isset($_POST["folder"]))
        exit(header('Location: ../index.php'));

    $path = trim($_POST['path']);
    $folder = trim($_POST['folder']);

    $who = explode("/", $path)[0];
    if($_SESSION["user"] != $who)
        exit(header('Location: ../index.php'));

    // path validation
    if(!preg_match(PATH, $path))
        exit(header('Location: ../error_pages/404.php'));

    // proj name validation
    define("NAMEFOLD", "/^[a-zA-Z0-9_]{1,52}$/");
    if(!preg_match(NAMEFOLD, $folder))
        exit(header('Location: ../show_project_folder.php?path='.$path.'&error=invalid_name'));

    if(is_dir("../../../users/".$path."/".$folder))
        exit(header('Location: ../show_project_folder.php?path='.$path.'&error=duplicat'));

    if (!mkdir("../../../users/".$path."/".$folder))
		exit(header('Location: ../error_pages/500.php'));

    header('Location: ../show_project_folder.php?path='.$path.'&error=dir_added');
?>
