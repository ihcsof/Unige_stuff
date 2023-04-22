<?php
    session_start();
    require_once("scripts/errorRep.php");
    require_once("scripts/utilities.php");
    require_once("scripts/connect.php");

    if (!isset($_SESSION["user"]) && isset($_COOKIE["login"]))
        handle_login_cookie($conn);
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
        <h1 class='ms-2'>Searched stuff</h1><br>
        <main>
            <?php
                require_once("scripts/search.php");
            ?>
        </main>
        <?php require_once("footer.html") ?>
    </body>
</html>
