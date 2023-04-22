<?php
    session_start();
    require_once("scripts/errorRep.php");
    require_once("scripts/utilities.php");
    require_once("scripts/connect.php");

    if(!isset($_SESSION["user"])) {
        if(!isset($_COOKIE["login"]))
            exit(header('Location: index.php'));
        if(!handle_login_cookie($conn))
            exit(header('Location: index.php'));
    }
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

            if(isset($_GET["error"]))
				require_once("error_bar.php");
        ?>
        <h1 class="text-center mt-4">Update password</h1><br>

        <main class="d-flex justify-content-center">
            <form action="scripts/update_pwd.php" method="POST">
                <div class="mb-3">
                    <label for="old" class="form-label">
                        Old Password
                    </label>
                    <input type="password" name="old" id="old" class="form-control">
                </div>
                <div class="mb-3">
                    <label for="pass" class="form-label">
                        New Password
                    </label>
                    <input type="password" name="new" id="pass" class="form-control pwd_in">
                    <div class='form-text'>min 8 chars</div>
                </div>
                <div class="mb-3">
                    <label for="confirm" class="form-label">
                        Confirm Password
                    </label>
                    <input type="password" name="confirm" id="confirm" class="form-control pwd_in">
                </div>
                <div class="mb-3">
                    <input class="btn btn-primary" type="submit" id="button" name="submit" value="Change">
                </div>
            </form>
        </main>
        <?php require_once("footer.html") ?>
    </body>
</html>
