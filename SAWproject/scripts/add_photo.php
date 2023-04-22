<?php
    session_start();
    require_once("errorRep.php");

    if(!isset($_SESSION["user"])) {
        if (!isset($_COOKIE["login"]))
            exit(header('Location: ../index.php'));
        if(!handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }

    // Undefined | Multiple files (> 1 files --> $_FILES['fname']['error'] is an array)
    // If this request falls under any of them, treat it invalid.
    if (!isset($_FILES['profile']['error']) || is_array($_FILES['profile']['error']))
        die(json_encode(array("msg" => "call_err")));

    // Check $_FILES['upfile']['error'] value.
    switch ($_FILES['profile']['error']) {
        case UPLOAD_ERR_NO_FILE:
            die(json_encode(array("msg" => "no_file")));
        case UPLOAD_ERR_INI_SIZE:
            die(json_encode(array("msg" => "file_size")));
    }
    // You should also check filesize here.
    if ($_FILES['profile']['size'] > 0xA00000)
        die(json_encode(array("msg" => "file_size")));

    // DO NOT TRUST $_FILES['upfile']['mime'] VALUE !!
    // Check MIME Type by yourself.
    $finfo_op = finfo_open(FILEINFO_MIME_TYPE);
    $finfo = finfo_file($finfo_op, $_FILES['profile']['tmp_name']);
    $ext = array(
                'jpg' => 'image/jpeg',
                'png' => 'image/png',
                'webp' => 'image/webp'
             );
    if (!array_search($finfo, $ext, true))
        die(json_encode(array("msg" => "ext_err")));

    // DO NOT USE $_FILES['upfile']['name'] WITHOUT ANY VALIDATION !!
    if (!move_uploaded_file($_FILES['profile']['tmp_name'], "../../../users/".$_SESSION["user"]."/icon"))
       die(json_encode(array("msg" => "call_err")));

    echo json_encode(array("msg" => "OK"));
?>
