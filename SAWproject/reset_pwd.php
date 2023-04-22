<?php
    session_start();
    require_once("scripts/errorRep.php");
    require_once("scripts/utilities.php");

    if(isset($_SESSION["user"]))
        exit(header('Location: index.php'));
    if(isset($_COOKIE["login"])) {
        if(handle_login_cookie($conn))
            exit(header('Location: index.php'));
    }
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <?php require_once("head.html"); ?>
    </head>
    <body>
        <?php
            require_once("nav.php");

            if(isset($_GET["error"]))
                require_once("error_bar.php");
        ?>
        <h1 class="text-center mt-4">Reset pwd</h1><br>

        <main class="d-flex justify-content-center">
            <form class = "col-8" action="scripts/send_token.php" method="POST">
                <div class="mb-3">
                    <label for="email" class="form-label" name="email">
                        Email
                    </label>
                    <input type="email" class="form-control" id="email" name="email">
                </div>
                <div class="mb-3">
                    <input class="btn btn-primary" type="submit" name="submit" value="recover password">
                </div>
            </form>
        </main>
        <?php require_once("footer.html") ?>
    </body>
</html>
