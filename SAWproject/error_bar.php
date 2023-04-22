<?php
    $error_mapping = array (
        "loginfailed" => "Login failed!",
        "wrongold" => "Old password was wrong",
        "no_pwd" => "Missing password",
        "no_name" => "Missing name",
        "no_email" => "Missing email",
        "invalid_pwd" => "Password was too short",
        "diff_pwd" => "Password confirm was wrong",
        "invalid_name" => "Invalid name format",
        "invalid_fname" => "Invalid format: letters/numbers(.extension)",
        "invalid_email" => "Invalid mail format",
        "regok" => "User successfully registered",
        "logok" => "Logged in",
        "updateok" => "The profile was successfully updated",
        "updatepwdok" => "Password was successfully updated",
        "no_file" => "No file was sent",
        "file_err" => "File upload error",
        "call_err" => "Something went wrong :(",
        "file_size" => "Max file dimension: 10MB",
        "ext_err" => "Valid extensions: jpg, jpeg, png, webp",
        "ext_err2" => "Invalid file extension",
        "addok" => "The project was successfully added",
        "projdup" => "This project name already exists",
        "maildup" => "This email already exists",
        "tok_expired" => "Link expired",
        "recovery" => "We sent you an email to recover your password",
        "recoverpwdok" => "Password was successfully changed",
        "recoverpwderr" => "Something went wrong in password recovery",
        "duplicat" => "This folder name already exists",
        "file_added" => "New file added",
        "dir_added" => "New folder added",
        "nwl_ok" => "Newsletter sent",
        "nwl_empty" => "You can't send an empty email!",
        "rate_ok" => "Thank you for voting!",
        "tok_invalid" => "Token was invalid"
    );

    $success = array (
        "regok",
        "logok",
        "updateok",
        "updatepwdok",
        "addok",
        "recovery",
        "recoverpwdok",
        "file_added",
        "dir_added",
        "nwl_ok",
        "rate_ok"
    );

	if (array_key_exists($_GET["error"], $error_mapping)){
    	echo "<div id = 'errorBar' class='error_bar alert alert-";
    	echo ((in_array($_GET["error"], $success)) ? "success" : "danger");
    	echo " alert-dismissible fade show' role='alert'>";
    	echo $error_mapping[$_GET["error"]];
		echo "<button type='button' class='btn-close' data-bs-dismiss='alert' aria-label='Close'></button>";
		echo "</div>";
	}
?>
