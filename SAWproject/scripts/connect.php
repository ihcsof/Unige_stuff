<?php
    $dbserver = "localhost";
    $user = "S4989646";
    $pwd = "c++enjoyer69";
    $dbname = "S4989646";

    mysqli_report(MYSQLI_REPORT_OFF);

  	if(!($conn = mysqli_connect($dbserver, $user, $pwd, $dbname)))
    	die("Connection failed: ".mysqli_connect_error());
?>
