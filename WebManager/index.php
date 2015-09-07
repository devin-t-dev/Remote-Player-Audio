	<?php
	session_start();
	if ($_SESSION['user']!=true) {
		header('Location: login.php');
		die();
	}
	?>
<html>
<head>
	<title>Riproduttore Audio - Interfaccia WEB</title> <!-- Titolo della pagina -->
	<meta http-equiv="X-UA-Compatible" content="IE=edge"> <!-- Forza il browser ad ottenere le versioni più recenti-->
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1"> <!-- Possibilità di Zoom per dispositivi mobili -->
	<link rel="stylesheet" href="assets/bootstrap/css/bootstrap.css"> <!-- Bootstrap FrameWork -->
	<script type="text/javascript" src="assets/jquery-2.1.4.js"></script> <!-- Jquery library -->
	<script type="text/javascript" src="assets/bootstrap/js/bootstrap.min.js"></script>
	<link rel="stylesheet" href="style.css"> <!-- Style for this page -->
	<script></script>
	<nav class="navbar navbar-inverse navbar-fixed-top"> <!-- barra di navigazione -->
		<div class="container">
			<div class="navbar-header">
				<button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#navbar">
				<span class="sr-only">Navigazione</span>
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>
		       	<span class="icon-bar"></span>
		        </button>
				<a class="navbar-brand" href="#">Riproduttore Audio</a>
			</div>
			<div id="navbar" class="collapse navbar-collapse">
				<ul class="nav navbar-nav">
					<!--<li><a href="#">Riproduttore</a></li>-->
					<li><a href="doxygeninfo/index.html">Informazioni</a></li>
				</ul>
				<ul class="nav navbar-nav navbar-right">
				<li><input type="text" placeholder="Cerca canzone..." id="search" class="form-control"></li><li>
				<button type="button" class="btn btn-default actionMenu" id="userButton"><span class="glyphicon glyphicon-user"></span></button><button type="button" class="btn btn-default actionMenu" id="shutdownButton"><span class="glyphicon glyphicon-off"></span></button></li>
				</ul>
			</div>
		</div>
	</nav>
</head>
<body>
	<div id="container" class="container"> <!-- Il div che contiene il contenuto -->
	<div id="coverContainer">
		<p>Caricamento Canzoni in corso</p>
	</div>
	<div class="row">
		<div class="table-responsive">
			<table class="table table-hover" id="tabSongs">
				<thead>
					<tr>
						<td>Lista canzoni</td>
						<td></td>
					</tr>
				</thead>
				<tbody>
				</tbody>
			</table>
		</div>
	</div> <!-- row -->
	</div> <!-- container -->
</body>
	<footer class="footer">
		<div class="container">
			<div class="row">
					<div class="col-md-8 col-xs-12" id="canzoneAttuale"></div>
					<div class="col-md-4 col-xs-12">
						<button type="button" class="btn btn-default btn-lg" id="prevButton"><span class="glyphicon glyphicon-backward"></span></button>
						<button type="button" class="btn btn-default btn-lg" id="playButton"><span class="glyphicon glyphicon-play"></span></button>
						<button type="button" class="btn btn-default btn-lg" id="nextButton"><span class="glyphicon glyphicon-forward"></span></button>
					</div>
			</div>
			<div class="row">
				<center><p>(C) - Devin Taietta</p></center>
			</div>
		</div>
	</footer>

<!-- Sezione script  -->

<script type="text/javascript" src="index.js"></script>
</html>
