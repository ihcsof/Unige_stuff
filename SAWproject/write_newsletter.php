<?php
    session_start();
    require_once("scripts/errorRep.php");
    require_once("scripts/utilities.php");
    require_once("scripts/connect.php");

    if(!isset($_SESSION["user"])) {
        if (!isset($_COOKIE["login"]))
            exit(header('Location: index.php'));
        if(!handle_login_cookie($conn))
            exit(header('Location: index.php'));
    }
    if(!isset($_SESSION["admin"]))
        exit(header('Location: index.php'));
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
        <h1 class="mt-4 text-center">Newsletter space</h1><br>
        <main class="d-flex justify-content-center">
            <form class="col-8" action="scripts/send_newsletter.php" method="post">
                <div class="mb-3">
                    <label for="newsletterTextarea" class="form-label">
                        Newsletter
                    </label>
                    <textarea required name="content" class="form-control" id="newsletterTextarea" rows="3"></textarea>
                </div>
                <div class="mb-3">
                    <input class="btn btn-primary" type="submit" name="submit" value="Send!">
                </div>
            </form>
        </main>
        <?php require_once("footer.html") ?>
    </body>
</html>
