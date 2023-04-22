<?php
    session_start();
    require_once("errorRep.php");
    require_once("utilities.php");
    require_once("connect.php");

    if(!isset($_SESSION["user"])) {
        if (!isset($_COOKIE["login"]))
            exit(header('Location: ../index.php'));
        if(!handle_login_cookie($conn))
            exit(header('Location: ../index.php'));
    }
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <!-- Ai fini del test -->
        <?php require_once("../head.html"); ?>
        <script src="../js/show_profile.js" charset="utf-8"></script>
    </head>
    <body>
        <?php
            // Ai fini del test
            require_once("../nav.php");

            if(isset($_GET["error"]))
				require_once("../error_bar.php");
        ?>
        <h1 class="mt-4 text-center">My profile</h1><br>

        <!--<div class='text-center mt-5'></div>-->
        <main class="d-flex justify-content-center">
            <?php
                if($data = image($_SESSION["user"]))
                    echo "<img class='profile_pic rounded-circle img-fluid' id = 'pic' src='data:image/jpg;base64,".$data."' alt='profile picture'>";
                else
                    echo "<img class='profile_pic rounded-circle img-fluid' id = 'pic' src='../images/default.jpg' alt='default profile picture'>";
            ?>
            <form class="mt-4" id = "sendImg" enctype="multipart/form-data">
                <div class="mb-3">
                    <input type="file" class="form-control" aria-label="update profile pic"
                        required id="fileToSend" type="file" name="profile" value="profile" onchange="takeLocalFile(this)">
                </div>
                <div class="mb-3">
                    <input class="btn btn-primary" type="submit" name="submit" value="Save File">
                    <a href="#" id="delImg" class="ms-2">Delete Pic</a>
                </div>
            </form>
        </main>

        <main class="d-flex justify-content-center mb-2">
            <form action="update_profile.php" method="POST">
                <fieldset>
                    <legend>I tuoi dati:</legend>
                    <?php
                        $query = "SELECT firstname, lastname, email, nwl FROM users WHERE id = ?;";
                        $stmt = mysqli_stmt_init($conn);
                        if(exec_query($stmt, $res, $query, "s", $_SESSION["user"]))
                            exit(header('Location: ../index.php?error=404'));

                        if(!($user = mysqli_fetch_assoc($res)))
                            exit(header('Location: ../index.php?error=404'));

                        mysqli_stmt_close($stmt);
                        mysqli_close($conn);

                        $names = ["firstname", "lastname", "email"];
                        foreach($names as $str) {
                            echo "<div class='mb-3'>";
                            echo "<label for='".$str."' class='form-label'>".$str."</label>";
                            echo "<input type='text' class='form-control' id='".$str;
                            echo "' name='".$str;
                            echo "' value='".htmlentities($user[$str], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML401, "UTF-8");
                            echo "'></div>";
                        }
                    ?>
                </fieldset>
                <div class="form-check form-switch mb-3">
                    <input class="form-check-input" type="checkbox" name="nwl" value="on"
                        <?php echo (($user["nwl"]) ? "checked" : ""); ?>>
                    <label class="form-check-label" for="flexCheckDefault">
                        Receive Newsletter
                    </label>
                </div>
                <div class="mb-3">
                    <input class="btn btn-primary" type="submit" name="submit" value="Save Changes">
                </div>
                <a href="update_pwd_form.php">Change Password</a>
            </form><br>
        </main>
        <?php require_once("../footer.html") ?>
    </body>
</html>
