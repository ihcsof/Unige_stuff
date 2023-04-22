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
        <h1 class="text-center mt-4">Show Projects</h1><br>
		<main class="d-flex justify-content-center mb-2">
        <form class="col-8" action="scripts/add_project.php" method="POST">
			<div class="mb-3">
        		<label for="proj_name" class="form-label">
					Nuovo progetto
				</label>
        		<input required type="text" class="form-control"
					name="proj_name" pattern = "^[a-zA-Z_0-9]{1,52}$" id="proj_name">
				<div class='form-text'>può contenere lettere, numeri e _</div>
    	    </div>
			<div class="mb-3">
        		<input class="btn btn-primary" type="submit" name="submit" value="Create Project">
        	</div>
        </form>
		</main>
		<div class="mb-2">
			<?php list_projects($conn, $_SESSION["user"]); ?>
		</div>
		<?php require_once("footer.html") ?>
  	</body>
</html>
