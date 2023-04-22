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
	</head>
	<body>
		<?php
			require_once("nav.php");

			if(isset($_GET["error"]))
				require_once("error_bar.php");
		?>
    	<main>
			<div class="container mt-5">
		      <h1 class="display-4 mb-5 text-center">GitSAW Website</h1>
		      <p class="lead mb-5">Welcome to the GitSAW website! Here you can host and manage your Saw repositories,
				  collaborate with others on open source projects, and track issues and pull requests.</p>
		      <div class="row">
		        <div class="col-md-6 mb-5">
		          <h2>Host and manage your Saw repositories</h2>
		          <p>Our website allows you to easily create and host your Saw repositories.
					  You can choose to make your repositories public or private,
					  and invite other users to collaborate with you.</p>
		        </div>
		        <div class="col-md-6 mb-5">
		          <h2>Collaborate on open source projects</h2>
		          <p>Join our community of open source developers and contribute to a wide range of projects.
					  You can use our website to find and join projects, track issues and pull requests,
					  and discuss changes with others.</p>
		        </div>
		      </div>
		      <div class="row">
		        <div class="col-md-6 mb-5">
		          <h2>Track issues and pull requests</h2>
		          <p>Our website allows you to easily track and manage issues and pull requests for your repositories.
					  You can assign issues to team members, label and prioritize them, and discuss changes with others.</p>
		        </div>
		        <div class="col-md-6 mb-5">
		          <h2>Connect with other developers</h2>
		          <p>Join our community of developers and connect with others who share your interests.
					  You can follow other users, participate in discussions, and stay up-to-date on
					  the latest developments in your favorite projects.</p>
		        </div>
		      </div>
			  <?php
			  	if (!isset($_SESSION["user"]))
					echo "<p class='text-center'><a href='registration_form.php' class='btn btn-primary btn-lg'>Join us now!</a></p>";
			  ?>
		    </div>
    	</main>
		<?php require_once("footer.html") ?>
  	</body>
</html>
