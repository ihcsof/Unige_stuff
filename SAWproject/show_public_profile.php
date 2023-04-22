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

        <section class="mb-2">
            <div class="card mb-4">
              	<div class="card-body text-center">
               		<?php
                   		if(!isset($_GET["user"]) || !is_numeric($_GET["user"]))
						  	exit(header('Location: index.php'));

                      	$query = "SELECT firstname, lastname, email FROM users WHERE id = ?;";
                      	$stmt = mysqli_stmt_init($conn);
                      	if(exec_query($stmt, $res, $query, "i", $_GET["user"]))
                        	exit(header('Location: error_pages/500.php'));

                      	if(!($user = mysqli_fetch_assoc($res)))
                          	exit(header('Location: error_pages/500.php'));

                      	if($data = image($_GET["user"]))
                          	echo "<img class='profile_pic rounded-circle img-fluid' src='data:image/jpg;base64,".$data."' alt='profile picture'>";
                      	else
                          	echo "<img class='profile_pic rounded-circle img-fluid' src='images/default.jpg' alt='profile picture'>";
                      	echo "<h5 class='my-3'>".htmlentities($user["firstname"], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8")." ";
                        echo htmlentities($user["lastname"], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8")."</h5>";
                      	echo "<p class='text-muted mb-1'>".htmlentities($user["email"], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8")."</p>";
                    ?>
                	<p class="text-muted mb-4"><strong>Status:</strong> Offline</p>
                	<div class="d-flex justify-content-center mb-2">
                		<button type="button" class="btn btn-primary">Follow</button>
                  		<button type="button" class="btn btn-outline-primary ms-1">Message</button>
                	</div>
           		</div>
          	</div>
          	<h3 class="text-center mt-4">Projects</h3><br>
          	<div class="card mb-4 mb-lg-0">
	            <?php
    	        	list_projects($conn, $_GET["user"]);
        	        mysqli_stmt_close($stmt);
            	    mysqli_close($conn);
	            ?>
	        </div>
        </section>
        <?php require_once("footer.html") ?>
    </body>
</html>
