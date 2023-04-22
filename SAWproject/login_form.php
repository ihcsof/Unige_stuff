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
        <h1 class="text-center mt-4">Login form</h1>

        <main class="d-flex justify-content-center">
        <form action="scripts/login.php" method="POST" class="col-8">
            <div class="mb-3">
                <label for="email" class="form-label">
                    Email
                </label>
                <input type="email" class="form-control" name="email" id="email">
            </div>
            <div class="mb-3">
        		<label for="pwd" class="form-label">
					Password
				</label>
        		<input type="password" class="form-control" name="pass" id="pwd">
    	    </div>
            <div class="mb-3 form-check form-switch">
	    	    <input type="checkbox" class="form-check-input" name="rememberme" value="on" id="remember">
        		<label class="form-check-label" for="remember">
					Remember Me
				</label>
        	</div>
            <div class="mb-3">
        		<button class="btn btn-primary " type="submit" name="submit" value="Login">Submit</button>
                <a class="link-primary ms-2" href='reset_pwd.php'>I forgot the pwd :(</a>
        	</div>
        </form>
        </main>
        <?php require_once("footer.html") ?>
    </body>
</html>
