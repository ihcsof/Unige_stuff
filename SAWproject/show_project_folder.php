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
        <script src="js/score.js" charset="utf-8"></script>
    </head>
    <body>
        <?php
            require_once("nav.php");

            if(isset($_GET["error"]))
				require_once("error_bar.php");

            if(!isset($_GET["path"]))
                exit(header('Location: error_pages/404.php'));

			if(!preg_match(PATH, $_GET["path"]))
            	exit(header('Location: error_pages/404.php'));

            $path = explode("/", $_GET["path"]);

        	$el = "../../users/".$_GET["path"];
        	if(!($files = scandir($el."/", SCANDIR_SORT_ASCENDING)))
                exit(header('Location: error_pages/404.php'));
            $to_remove = array('.', '..');
            $files = array_diff($files, $to_remove);

            $stmt = mysqli_stmt_init($conn);

			$query = "SELECT firstname, lastname FROM users WHERE id = ?";

			if(exec_query($stmt, $res, $query, "i", $path[0]))
                exit(header('Location: error_pages/500.php'));

			$info = mysqli_fetch_assoc($res);
			$owner = $info["firstname"]." ".$info["lastname"];

            $who = $path[0]; // user id
            if(isset($_SESSION["user"]) && $_SESSION["user"] == $who)
                echo <<< FORM
                    <main class="d-flex mt-4">
                        <form class="me-auto me-2 col-6" enctype="multipart/form-data" action="scripts/add_file.php" method="POST">
                            <div class="input-group mb-3">
                                <input type="file" class="form-control" placeholder="Insert your file" name="fname" value="fname"
                                    aria-label="File name" aria-describedby="File name to be inserted">
                                <input name="path" type="hidden" value="{$_GET['path']}">
                                <button class="btn btn-outline-secondary" type="submit">Invia</button>
                            </div>
                        </form>
                        <form class="me-auto me-2 col-6" action="scripts/add_dir.php" method="POST">
                            <div class="input-group mb-3">
                                <input type="text" class="form-control" placeholder="Specify a folder name (letters, numbers, _)" name="folder"
                                    aria-label="Directory name" aria-describedby="Directory to be inserted" pattern="^[a-zA-Z0-9_]{1,52}$">
                                <button class="btn btn-outline-secondary" type="submit">Crea</button>
                                <input name="path" type="hidden" value="{$_GET['path']}">
                            </div>
                        </form>
                    </main>
                FORM;
            else if(isset($_SESSION["user"])) {
                $proj_name = $path[1];

                // Get proj_id, use it to check if user has already voted:

                $query = "SELECT id FROM projects WHERE user_id = ? AND name = ?";
                if(exec_query($stmt, $res, $query, "is", $who , $proj_name))
                    exit(header('Location: error_pages/500.php'));
                $proj_id =  mysqli_fetch_assoc($res)["id"];

                $query = "SELECT *";
                $query .= " FROM ratings";
                $query .= " WHERE user_id = ? AND proj_id = ?;";

                if(exec_query($stmt, $res, $query, "ii", $_SESSION["user"] , $proj_id))
                    exit(header('Location: error_pages/500.php'));

                $score_already = mysqli_num_rows($res);
                $entry_db = mysqli_fetch_assoc($res);
                // if already voted: take vote, if not: default 1
                $score = ($score_already) ? $entry_db["score"] : 1;

                echo <<< FOUR
                    <form action="scripts/update_score.php">
                        <div>
                            <label for="score" class="form-label ms-2">
                                <h4>Rate the project</h4>
                            </label>
                        </div>
                        <div class="d-flex align-items-center">
                            <input type="range" id="score" value="{$score}" class="form-range slide ms-2" min="1" max="5" >
                            <input type="hidden" id="proj_id" value="{$proj_id}">
                            <input type="hidden" id="score_already" value="{$score_already}">
                            <h6 class="ms-2" id="rat">( {$score} )</h6>
                            <input class="btn btn-primary ms-2" type="submit" id="score_ready" value="Submit">
                        </div>
                    </form>
                FOUR;

            }
            else
                echo "<h4 class='ms-2'><a href='login_form.php'>Login</a> now to rate the project!</h4>";

            mysqli_stmt_close($stmt);
            mysqli_close($conn);

            gen_projbar($who, $owner, $path);

        	$dir_a = "<a href='show_project_folder.php?path=".$_GET["path"]."/";
            $file_a = "<a href='show_file.php?path=".$_GET["path"]."&fname=";

            if(empty($files))
                echo "<h3 class='text-center mt-4'>Nothing to show here :/</h3>";
            else {
                echo "<div class='mt-2 mb-2'>";
            	foreach($files as $k => $v) {
    				echo "<div class='card flex-row flex-wrap'>";
        	        echo "<div class='card-header border-0'>";
    				if (is_dir($el."/".$files[$k])){
    		        	echo "<i class='bi bi-folder2'></i>";
    					echo "</div><div class='card-block px-2 d-flex align-items-center'>";
            	        echo $dir_a.$files[$k]."'>".$files[$k]."</a><br>";
    				}
    				else{
    		           	echo "<i class='bi bi-file-earmark'></i>";
    					echo "</div><div class='card-block px-2 d-flex align-items-center'>";
            	        echo $file_a.$files[$k]."'>".$files[$k]."</a><br>";
    				}
    				echo "</div></div>";
                }
    			echo "</div>";
            }
        ?>
        <?php require_once("footer.html") ?>
    </body>
</html>
