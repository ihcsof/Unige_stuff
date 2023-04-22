<?php
    $dbserver = "localhost";
    $user = "";
    $pwd = "ehNoVoleviEh";
    $dbname = "";

    mysqli_report(MYSQLI_REPORT_OFF);

  	if(!($conn = mysqli_connect($dbserver, $user, $pwd, $dbname)))
    	die("Connection failed: ".mysqli_connect_error());
?>
