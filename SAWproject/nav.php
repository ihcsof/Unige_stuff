<nav class="navbar navbar-expand-lg navbar-dark bg-dark">
	<div class="container-fluid">
		<a class="navbar-brand" href="index.php">
  			<img src="images/favicon.ico" alt="Git-Saw Logo" width="40"
				height="40" class="d-inline-block align-text-top">
		</a>
  		<button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarColor01" aria-controls="navbarColor01" aria-expanded="false" aria-label="Toggle navigation">
    		<span class="navbar-toggler-icon"></span>
  		</button>
  		<div class="collapse navbar-collapse" id="navbarColor01">
    		<ul class="navbar-nav me-auto mb-2 mb-lg-0">
      			<li class="nav-item">
        			<a class="nav-link" href="#">Pricing</a>
      			</li>
      			<li class="nav-item">
        			<a class="nav-link" href="#">Solutions</a>
      			</li>
				<li class="nav-item">
        			<a class="nav-link" href="#">Open Source</a>
      			</li>
    		</ul>
    		<ul class="navbar-nav ms-auto mb-2 mb-lg-0">
    			<form class="d-flex me-auto me-2" role="search" action="search_page.php" method="get">
      				<input class="form-control me-2" type="search" placeholder="Search" name="q">
      				<button class="btn btn-outline-light me-2" type="submit">
						Search
					</button>
					<input type="hidden" name="p" value="0">
					<input type="hidden" name="type" value="proj">
    			</form>
				<li class="nav-item">
				<?php
					echo "<a class='nav-link active' href='";
					echo (!isset($_SESSION["user"]) ?
							"login_form.php'>Login" :
							"show_profile.php'>Show Profile");
					echo "</a>";
				?>
				</li>
				<li class="nav-item">
				<?php
					if(isset($_SESSION["user"]))
						echo "<a class='nav-link active' href='show_projects.php'>My Projects</a>";
				?>
      			</li>
				<li class="nav-item">
				<?php
                    if(isset($_SESSION["admin"]))
                        echo "<a class='nav-link active' href='write_newsletter.php'>Send Newsletter</a>";
                ?>
      			</li>
      			<li class="nav-item">
				<?php
					echo "<a class='nav-link active' href='";
					echo (!isset($_SESSION["user"]) ?
							"registration_form.php'>Register" :
							"scripts/logout.php?logout=logout'>Logout");
					echo "</a>";
				?>
      			</li>
    		</ul>
  		</div>
	</div>
</nav>
