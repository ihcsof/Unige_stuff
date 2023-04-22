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

    if(!isset($_POST['submit']) || !isset($_POST['email']) || !isset($_POST['pass']))
        exit(header('Location: ../index.php'));

    define("SECRET_KEY", "please_dont_steal_this_key_:(");

    $email = trim($_POST['email']);
    $pwd = trim($_POST['pass']);

    $query = "SELECT * FROM users WHERE email = ?;";
    $stmt = mysqli_stmt_init($conn);

    if(exec_query($stmt, $res, $query, "s", $email))
        exit(header('Location: ../error_pages/500.php'));

    if(!($user = mysqli_fetch_assoc($res)))
        exit(header('Location: ../login_form.php?error=loginfailed'));
    if(!password_verify($pwd, $user["pass"]))
        exit(header('Location: ../login_form.php?error=loginfailed'));

    $_SESSION["user"] = $user['id'];
    if($user['admin']) $_SESSION["admin"] = "xD";

    if(!isset($_POST["rememberme"]) || $_POST["rememberme"] != "on") {
        mysqli_stmt_close($stmt);
        mysqli_close($conn);

        exit(header('Location: ../index.php?error=logok'));
    }

    try {
        $token = openssl_random_pseudo_bytes(16, $is_secure);
    } catch (Exception $e) {
        exit(header('Location: ../error_pages/500.php'));
    }

    $cookie = $_SESSION["user"].':'.$token;
    $mac = hash_hmac('sha256', $cookie, SECRET_KEY, true);
    $cookie .= ':'.$mac;
    $expires = time() + 2592000;

	$dup_errno = 1062;
    $query = "INSERT INTO login_cookies VALUES(?, ?, ?);";

    if($errno = exec_query($stmt, $res, $query, "isi", $_SESSION["user"], $cookie, $expires)) {
        if ($errno != $dup_errno)
            exit(header('Location: ../error_pages/500.php'));
    	$query = "UPDATE login_cookies SET cookieid = ?, expires = ?;";

        if(exec_query($stmt, $res, $query, "si", $cookie, $expires))
            exit(header('Location: ../error_pages/500.php'));
    }

    mysqli_stmt_close($stmt);
    mysqli_close($conn);

    header('Location: ../index.php?error=logok');
    setcookie('login', $cookie, $expires, "/");
?>
