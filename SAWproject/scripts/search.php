<?php
    @session_start();
    require_once("errorRep.php");
    require_once("utilities.php");
    require_once("connect.php");

    function print_project($conn, $p, $q) {
        $query = "SELECT P.*, firstname, lastname FROM projects P JOIN users U ON U.id = P.user_id";
        $query .= " WHERE name LIKE ?";
        $query .= " ORDER BY CHAR_LENGTH(name)";
        $query .= " LIMIT 11 OFFSET ". strval($p * 10);

        $stmt = mysqli_stmt_init($conn);
        $tosearch = "%".$q."%"; // like gitHub :D
        if(exec_query($stmt, $res, $query, "s", $tosearch))
            exit(header('Location: ../error_pages/500.php'));

        $i = 0;
        while(($data = mysqli_fetch_assoc($res)) && $i++ < 10) {
            $fstname = htmlentities($data["firstname"], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8");
            $lstname = htmlentities($data["lastname"], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8");
            echo "<div class='card flex-row flex-wrap'>";
            echo "<div class='card-header border-0 d-flex align-items-center'>";
            echo "<i class='bi bi-folder'></i>";
            echo "</div><div class='card-block px-2'>";
            echo "<h6 class='card-title projname'><a href='show_public_profile.php?user=".$data["user_id"]."'>";
            echo $fstname." ".$lstname."</a>/<wbr>";
            echo "<a href='show_project_folder.php?path=".$data["user_id"]."/".$data["name"]."'>".$data["name"]."</a></h6>";
            echo "<div>";
            for($j = 0; $j < $data["score"]; $j++)
                echo "<span class='fa fa-star fa-1x checked'></span>";
            for($j = $data["score"]; $j < 5; $j++)
                echo "<span class='fa fa-star fa-1x'></span>";
            echo "</div></div></div><br>";
        }
        // number of projects printed
        mysqli_stmt_close($stmt);
        return $i;
    }

    function print_profile($conn, $p, $q) {
        $query = "SELECT id, firstname, lastname FROM users";
        $query .= " WHERE CONCAT(firstname, ' ', lastname) LIKE ?";
        $query .= " ORDER BY CHAR_LENGTH(CONCAT(firstname, ' ', lastname))";
        $query .= " LIMIT 11 OFFSET ". strval($p * 10);

        $stmt = mysqli_stmt_init($conn);
        $tosearch = "%".$q."%"; // like gitHub :D
        if(exec_query($stmt, $res, $query, "s", $tosearch))
            exit(header('Location: ../error_pages/500.php'));

        $i = 0;
        while(($user = mysqli_fetch_assoc($res)) && $i++ < 10) {
            echo "<div class='card flex-row flex-wrap'>";
            echo "<div class='card-header border-0'>";
            if($data = image($user["id"]))
                echo "<img class='profile_pic rounded-circle img-fluid' src='data:image/jpg;base64,".$data."' alt='profile picture'>";
            else
                echo "<img class='profile_pic rounded-circle img-fluid' src='images/default.jpg' alt='profile picture'>";
            echo "</div><div class='card-block px-2'>";

            $prof_name = htmlentities($user["firstname"], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8")." ";
            $prof_name .= htmlentities($user["lastname"], ENT_QUOTES | ENT_SUBSTITUTE | ENT_HTML5, "UTF-8");
            if(strlen($prof_name) > 30)
                $prof_name = substr($prof_name, 0, 27)."...";
            echo "<h4 class='card-title prof_names'>".$prof_name ."</h4>";
            echo "<p class='card-text prof_names'>Status: offline</p>";
            echo "<a href='show_public_profile.php?user=".$user["id"]."' class='btn btn-primary user_btn'>profile</a>";
            echo "</div></div><br>";
        }
        // number of profile printed
        mysqli_stmt_close($stmt);
        return $i;
    }

    if (!isset($_SESSION["user"]) && isset($_COOKIE["login"]))
        handle_login_cookie($conn);

    if(!isset($_GET["type"]) || ($_GET["type"] != "prof" && $_GET["type"] != "proj"))
        exit(header('Location: ../index.php'));

    $q = (isset($_GET["q"])) ? trim($_GET["q"]) : "";
    $p = (isset($_GET["p"]) && is_numeric($_GET["p"])) ? $_GET["p"] : 0;

    $i = 0xBADC0FFEE;
    echo "<a class='btn btn-primary mb-2 ms-2 col-md-auto' href='search_page.php?q=".$q."&p=0&type=";
    if($_GET["type"] == "prof") {
        echo "proj'>Looking for a project?</a><br><br>";
        $i = print_profile($conn, $p, $q);
    }
    else {
        echo "prof'>Looking for a user?</a><br><br>";
        $i = print_project($conn, $p, $q);
    }

    mysqli_close($conn);

    if(!$i)
        exit("<h3 class='text-center mt-3'>Nothing found here :(</h3>");

    echo "<div class='d-flex justify-content-between'><div>";
    if($p)
        echo "<a class='btn btn-info mb-2 ms-2 col-12' href='search_page.php?q=".$q."&p=".strval($p - 1)."&type=".$_GET["type"]."'>Prev</a>";
    echo "</div><div>";
    if($i == 11)
        echo "<a class='btn btn-info mb-2 mr-2 col-12' href='search_page.php?q=".$q."&p=".strval($p + 1)."&type=".$_GET["type"]."'>Next</a>";
    echo "</div></div>";
?>
