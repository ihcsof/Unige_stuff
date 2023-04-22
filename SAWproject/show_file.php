<?php
	session_start();
	require_once("scripts/errorRep.php");
	require_once("scripts/utilities.php");
	require_once("scripts/connect.php");

    if (!isset($_SESSION["user"]) && isset($_COOKIE["login"]))
        handle_login_cookie($conn)
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <?php require_once("head.html"); ?>
        <link rel="stylesheet" href="../hljs/styles/default.min.css" type="text/css">
    </head>
    <body>
        <header>
            <?php
				require_once("nav.php");

				if(isset($_GET["error"]))
					require_once("error_bar.php");
			?>
        </header>
        <?php
			if(!isset($_GET["path"]) || !isset($_GET["fname"]))
				exit(header('Location: index.php'));

			// path validation
		    if(!preg_match(PATH, $_GET["path"]))
		        exit(header('Location: error_pages/404.php'));

		    // project name validation
		    if(!preg_match(NAMEFILE, $_GET["fname"]))
		        exit(header('Location: error_pages/404.php'));

            $path = "../../users/".$_GET["path"];
            $fname = $_GET["fname"];
			// from documentation
			if(is_dir($path."/".$fname))
				exit(header('Location: error_pages/404.php'));

            $fp = fopen($path."/".$fname, "r");
			if(!$fp)
				exit(header('Location: error_pages/404.php'));
            $stat = round((fstat($fp)["size"] / 1024.), 3);
            if(is_null($ext = pathinfo($path."/".$fname, PATHINFO_EXTENSION)))
                $ext = "plaintext";

			$stmt = mysqli_stmt_init($conn);
			$links = explode("/", $_GET["path"]."/".$_GET["fname"]);
			$query = "SELECT firstname, lastname FROM users WHERE id = ?";

            if(exec_query($stmt, $res, $query, "i", $links[0]))
                exit(header('Location: error_pages/500.php'));

            $info = mysqli_fetch_assoc($res);
            $owner = $info["firstname"]." ".$info["lastname"];

			mysqli_stmt_close($stmt);
            mysqli_close($conn);

			gen_projbar($links[0], $owner, $links);

	        echo "<h3 class='mt-2'></h3>";

            $i = 0;
			echo "<div style='overflow-x: auto;'>";
			echo "<table class='table-responsive'><tbody>";
            while(!feof($fp)) {
				$str = stream_get_line($fp, 0, "\n");
                echo "<tr><td>".++$i.".</td>";
                echo "<td class='loc'><pre><code class = 'hljs language-".$ext."'>";
                echo "&#8203;".htmlentities($str, ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8");
                echo "</code></pre></td></tr>";
            }
			echo "</table></tbody></div>";

            echo "<script>";
            echo "$('h3').html('$fname | $i lines | $stat KB');";
            echo "</script>";
            fclose($fp);
        ?>
		<br>
		<?php require_once("footer.html") ?>
    </body>
    <script src="../hljs/highlight.min.js"></script>
    <script> hljs.highlightAll(); </script>
</html>
