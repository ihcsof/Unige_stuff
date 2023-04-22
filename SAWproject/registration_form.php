<?php
    session_start();
    require_once("scripts/errorRep.php");
    require_once("scripts/utilities.php");

    if(isset($_SESSION["user"]))
        exit(header('Location: index.php'));
    if (isset($_COOKIE["login"])) {
        if(handle_login_cookie($conn))
            exit(header('Location: index.php'));
    }
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <?php require_once("head.html"); ?>
        <script src="js/equal_pwd.js"></script>
        <script src="js/mail_exists.js"></script>
    </head>
    <body>
        <?php
            require_once("nav.php");

            if(isset($_GET["error"]))
				require_once("error_bar.php");
        ?>
        <h1 class="text-center mt-4">Registration form</h1>

        <main class="d-flex justify-content-center">
        <form class="col-8" action="scripts/registration.php" method="POST">
            <fieldset>
                <legend>Compila il form:</legend>
                    <?php
                        $names = ["firstname", "lastname", "email"];
                        foreach($names as $str){
                            echo "<div class='mb-3'>";
                            echo "<label for='".$str."' class='form-label'>".$str."</label>";
                            echo "<input required class='form-control' type='".(($str == "email") ? "email" : "text")."'";
                            echo " id='".$str."'";
                            echo " name='".$str."'";
                            if (isset($_GET[$str]))
                                echo " value='".htmlentities($_GET[$str], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8")."'";
                            if($str != "email") {
                                echo " pattern = \"^[a-zA-Z' ]{1,52}$\">";
                                echo "<div class='form-text'>only letters and single quotes</div";
                            }
                            else
                                echo "><div class='form-text' id='mail_warn'></div";
                                echo "></div>";
                        }
                    ?>

                    <div class="mb-3">
                        <label for="pass" class="form-label">
                            Password
                        </label>
                        <input required type="password" class="form-control pwd_in" minlength="8" type="password" id="pass" name="pass">
                        <div class='form-text'>min 8 chars</div>
    	            </div>

                    <div class="mb-3">
                        <label for="confirm" class="form-label pwd_in">
                            Confirm Password
                        </label>
                        <input type="password" class="form-control pwd_in"  required minlength="8" type="password" id="confirm" name="confirm">
                    </div>

                    <div class="form-check form-switch mb-3">
                        <input class="form-check-input" type="checkbox" name="nwl" value="on" id="checkNews">
                        <label class="form-check-label" for="checkNews">
                            Receive Newsletter
                        </label>
                    </div>

                    <div class="mb-3">
                        <input class="btn btn-primary" type="submit" name="submit" value="Submit!">
                    </div>
            </fieldset>
        </form>
        </main>
        <?php require_once("footer.html") ?>
    </body>
</html>
