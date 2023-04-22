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

    if(!isset($_POST["path"]))
        exit(header('Location: ../index.php'));

    $path = trim($_POST['path']);
    $fname = trim($_FILES['fname']['name']);

    $who = explode("/", $path)[0];
    if($_SESSION["user"] != $who)
        exit(header('Location: ../index.php'));

    // path validation
    if(!preg_match(PATH, $path))
        exit(header('Location: ../error_pages/404.php'));

    // proj name validation
    if(!preg_match(NAMEFILE, $fname))
        exit(header('Location: ../show_project_folder.php?path='.$path.'&error=invalid_fname'));

    // Undefined | Multiple files (> 1 files --> $_FILES['fname']['error'] is an array)
    // If this request falls under any of them, treat it invalid.
    if (!isset($_FILES['fname']['error']) || is_array($_FILES['fname']['error']))
        exit(header('Location: ../show_project_folder.php?path='.$path.'&error=call_err'));

    // Check $_FILES['upfile']['error'] value.
    switch ($_FILES['fname']['error']) {
        case UPLOAD_ERR_NO_FILE:
            exit(header('Location: ../show_project_folder.php?path='.$path.'&error=no_file'));
        case UPLOAD_ERR_INI_SIZE:
            exit(header('Location: ../show_project_folder.php?path='.$path.'&error=file_size'));
    }
    // You should also check filesize here (10MB)
    if ($_FILES['fname']['size'] > 0xA00000)
        exit(header('Location: ../show_project_folder.php?path='.$path.'&error=file_size'));

    // DO NOT TRUST $_FILES['upfile']['mime'] VALUE !!
    // Check MIME Type by yourself.
    $finfo_op = finfo_open(FILEINFO_MIME_TYPE);
    $finfo = finfo_file($finfo_op, $_FILES['fname']['tmp_name']);
    $ext = array("application/json", "application/javascript", "application/xml", "application/x-empty");
    if (array_search($finfo, $ext, true) === false && substr($finfo, 0, 4) != "text")
        exit(header('Location: ../show_project_folder.php?path='.$path.'&error=ext_err2'));

    // DO NOT USE $_FILES['upfile']['name'] WITHOUT ANY VALIDATION !!
    if (!move_uploaded_file($_FILES['fname']['tmp_name'], "../../../users/".$path."/".$fname))
       exit(header('Location: ../show_project_folder.php?path='.$path.'&error=call_err'));

    header('Location: ../show_project_folder.php?path='.$path.'&error=file_added');
?>
