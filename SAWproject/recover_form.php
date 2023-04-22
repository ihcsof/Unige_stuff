<?php
    require_once("scripts/errorRep.php");
	require_once("scripts/connect.php");
	require_once("scripts/utilities.php");
	session_start();

    if(isset($_SESSION["user"]))
        exit(header('Location: index.php'));
    if(isset($_COOKIE["login"])) {
        if(handle_login_cookie($conn))
            exit(header('Location: index.php'));
    }

    if(!isset($_SESSION["recovery"]))
        exit(header("Location: index.php"));
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <?php require_once("head.html"); ?>
        <script src="js/equal_pwd.js"></script>
    </head>
    <body>
        <?php
            require_once("nav.php");
        ?>
        <h1 class="text-center mt-4">Recover form</h1><br>
        <main class="d-flex justify-content-center">
            <form class="col-8" action="scripts/recover_pwd.php" method="POST">
                <div class="mb-3">
                    <label for="pass" class="form-label">
                        Password
                    </label>
                    <input type="password" required minlength="8" class="form-control pwd_in" name="pass" id="pass">
                    <div class='form-text'>min 8 chars</div>
                </div>
                <div class="mb-3">
                    <label for="confirm" class="form-label">
                        Confirm Password
                    </label>
                    <input type="password" required minlength="8" class="form-control pwd_in" name="confirm" id="confirm">
                </div>
                <div class="mb-3">
                    <button class="btn btn-primary" type="submit" name="submit">Submit</button>
                </div>
            </form>
        </main>
        <?php require_once("footer.html") ?>
    </body>
</html>
