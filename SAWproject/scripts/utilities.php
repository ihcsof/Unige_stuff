<?php
define("PATH", "/^[0-9]+(\/[a-zA-Z0-9_]{1,52})+$/");
define("NAMEFILE", "/^[A-Za-z0-9_]+(\.[a-z]+)?$/");

// fill the redirected page with info from the previous one
function err_handling($errorType, $where) {
    $redirect = "Location: ".$where."?error=$errorType";
    $names = ["firstname","lastname","email"];

    foreach($names as $name)
        if(isset($_POST[$name]))
            $redirect .= "&".$name."=".$_POST[$name];

    exit(header($redirect));
}

function exec_query($stmt, &$res, $query, $pholders, ...$args){
   	if(!mysqli_stmt_prepare($stmt, $query)) return mysqli_stmt_errno($stmt);
    mysqli_stmt_bind_param($stmt, $pholders, ...$args);
    if(!mysqli_stmt_execute($stmt)) return mysqli_stmt_errno($stmt);

	$res = mysqli_stmt_get_result($stmt);
    return mysqli_stmt_errno($stmt);
}

function destroy_cookie($cookie) {
    setcookie($cookie, "", time() - 1, "/");
    unset($_COOKIE[$cookie]);
}

function handle_login_cookie($conn) {
    $hash = substr($_COOKIE["login"], -32);
    $tok = substr($_COOKIE["login"], -49, 16);
    // numbers can have lots of digits :)
    $uid = substr($_COOKIE["login"], 0, -50);

    $query = "SELECT * FROM login_cookies WHERE userid = ?;";
    $stmt = mysqli_stmt_init($conn);

    if(exec_query($stmt, $res, $query, "i", $uid))
        exit(header('Location: ../error_pages/500.php'));

    if(!($cookie = mysqli_fetch_assoc($res))) {
        destroy_cookie("login");
        return false;
    }

    $hash_db = substr($cookie["cookieid"], -32);
    if(!hash_equals($hash_db, $hash)) {
        destroy_cookie("login");
        return false;
    }

    if($cookie["expires"] <= time()) {
        $query = "DELETE FROM login_cookies WHERE userid = ?;";
        if(exec_query($stmt, $res, $query, "i", $uid))
            exit(header('Location: ../error_pages/500.php'));

        destroy_cookie("login");
        return false;
    }

    $_SESSION["user"] = $uid;

    // if admin
    $query = "SELECT admin FROM users WHERE id = ?;";
    $stmt = mysqli_stmt_init($conn);

    if(exec_query($stmt, $res, $query, "i", $uid))
        exit(header('Location: ../error_pages/500.php'));

    if(!($user = mysqli_fetch_assoc($res)))
        exit(header('Location: ../error_pages/500.php'));

    if($user['admin']) $_SESSION["admin"] = "xD";

    return true;
}

function image($id) {
    $path = dirname($_SERVER["CONTEXT_DOCUMENT_ROOT"])."/users/".$id."/icon";
    $fcontent = @file_get_contents($path);

    return $fcontent ? base64_encode($fcontent) : false;
}

function list_projects($conn, $who) {
    $query = "SELECT * FROM projects WHERE user_id = ? ORDER BY name;";
    $stmt = mysqli_stmt_init($conn);
    if(exec_query($stmt, $res, $query, "i", $who))
		exit(header('Location: error_pages/500.php'));

    if(!mysqli_num_rows($res)) {
        echo "<h3 class='text-center mt-3'>Nothing to show here :/</h3>";
        return;
    }

    while($project = mysqli_fetch_assoc($res)) {
        echo "<div class='card flex-row flex-wrap mt-2'>";
        echo "<div class='card-header border-0 d-flex align-items-center'>";
        echo "<i class='bi bi-folder'></i>";
        echo "</div><div class='card-block px-2'>";
        echo "<h6 class='card-title projname'>";
        echo "<a href='show_project_folder.php?path=".$who."/".$project["name"]."'>".$project["name"]."</a></h6>";
        for($j = 0; $j < $project["score"]; $j++)
            echo "<span class='fa fa-star fa-1x checked'></span>";
        for($j = $project["score"]; $j < 5; $j++)
            echo "<span class='fa fa-star fa-1x'></span>";
        echo "</div></div>";
    }
}

// id = id owner del proj; owner = nome,cognome owner; links = path
function gen_projbar($id, $owner, $links){
	$len_a = count($links) - 1;
    $owner = htmlentities($owner, ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8");

	echo "<div class='card mt-4'><div class='card-body'>";
   	echo "<a class='text-decoration-none' href='show_public_profile.php?user=".$id."'>".$owner."</a>/";
    $aux = $links[0];
    for($i = 1; $i < $len_a; $i++){
      	$aux .= "/".$links[$i];
       	echo "<a class='text-decoration-none' href='show_project_folder.php?path=".$aux."'>".$links[$i]. "</a>/";
	}
	echo "<strong>".$links[$len_a]."</strong>";
    echo "</div></div>";
}
?>
