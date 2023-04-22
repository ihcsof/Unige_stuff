<?php
    require_once("errorRep.php");
    require_once("connect.php");
    require_once("utilities.php");
    require_once("mail_init.php");
    session_start();

    if(!isset($_SESSION["user"])) {
        if (!isset($_COOKIE["login"]))
            exit(header('Location: ../index.php'));
        if(!handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }
    if(!isset($_SESSION["admin"]))
        exit(header('Location: index.php'));

    $query = "SELECT * FROM users WHERE nwl = true;";
    if(($res = mysqli_query($conn, $query)) === false)
        exit(header('Location: ../error_pages/500.php'));

    if(!isset($_POST["content"]) || $_POST["content"] == "")
        exit(header('Location: ../write_newsletter.php?error=nwl_empty'));
    $body = trim($_POST["content"]);

    // Sender info
    $mail->setFrom('dummylorenzo4@gmail.com', 'GitSAW Newsletter');
    $mail->Subject = 'Gitsletter';
    $mail->Body = $body;
    // Default (admin)
    $mail->addAddress('dummylorenzo4@gmail.com');
    // Send mails
    while($user = mysqli_fetch_assoc($res))
        $mail->addAddress($user["email"]);

    if (!$mail->send())
        exit(header('Location: ../write_newsletter.php?error=call_err'));

    mysqli_close($conn);
    $mail->smtpClose();

    header('Location: ../write_newsletter.php?error=nwl_ok');
?>
