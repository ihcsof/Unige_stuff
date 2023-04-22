<?php
    require_once("errorRep.php");
    require_once("connect.php");
    require_once("utilities.php");
    require_once("mail_init.php");
    session_start();

    if(isset($_SESSION["user"]))
        exit(header('Location: ../index.php'));
    if(isset($_COOKIE["login"])) {
        if(handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }

    if(!isset($_POST['submit']) || !isset($_POST['email']))
        exit(header('Location: ../index.php'));

    // Validate input mail
    $email = trim($_POST["email"]);
    if(!filter_var($email, FILTER_VALIDATE_EMAIL))
        exit(header('Location: ../reset_pwd.php?error=invalid_email'));

    // Check email existence
    $query = "SELECT * FROM users WHERE email = ?;";
    $stmt = mysqli_stmt_init($conn);

    if(exec_query($stmt, $res, $query, "s", $email))
        exit(header('Location: ../error_pages/500.php'));

    if(!($user = mysqli_fetch_assoc($res)))
        exit(header('Location: ../reset_pwd.php?error=no_email'));

    // Sender info
    $mail->setFrom('dummylorenzo4@gmail.com', 'GitSAW Password Recovery');
    // Receiver email address and name
    $mail->addAddress($email, $email);

    $mail->Subject = 'GitSAW Password Recovery';

    try {
        $token = openssl_random_pseudo_bytes(16, $is_secure);
    } catch (Exception $e) {
        exit(header('Location: ../error_pages/500.php'));
    }

    $token = hash("sha256", $token);
    $expires = time() + 720; // 12 min

	$dup_errno = 1062;
    $query = "INSERT INTO pwd_tokens VALUES(?, ?, ?);";

    if($errno = exec_query($stmt, $res, $query, "ssi", $email, $token, $expires)) {
        if ($errno != $dup_errno)
            exit(header('Location: ../error_pages/500.php'));
    	$query = "UPDATE pwd_tokens SET token = ?, expires = ? WHERE email = ?;";

        if(exec_query($stmt, $res, $query, "sis", $token, $expires, $email))
            exit(header('Location: ../error_pages/500.php'));
    }

    mysqli_stmt_close($stmt);
    mysqli_close($conn);

	$token = "To recover click here: https://saw21.dibris.unige.it/~S4989646/new/scripts/check_token.php?hash=".$token;
    $mail->Body = $token;

    if (!$mail->send())
        exit(header('Location: ../reset_pwd.php?error=call_err'));

    $mail->smtpClose();

    header('Location: ../login_form.php?error=recovery');
?>
