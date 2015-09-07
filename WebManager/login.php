<?php
session_start();
if (isset($_POST['user'])) {
	$username="root";
	$password="root";
	$hostname="localhost";
	$database="Audio";

	$givedUser=$_POST['user'];
	$givedPass=$_POST['pass'];

	$query="SELECT * FROM tbl_utenti WHERE utente='$givedUser' AND password='$givedPass'";

	$connessione = mysqli_connect($hostname,$username,$password,$database);

	$ris = mysqli_query($connessione, $query);
	if (!$ris) {
    	die(mysqli_error($link));
	}
	$quantita=mysqli_num_rows($ris);
	echo $quantita;
	if ($quantita>0) {
		$_SESSION['user']=true;
		header('Location: index.php');
		echo "Login effettuato con successo. <a href='index.php'> Avanti</a>";
	}
	else
	{
		$_SESSION['logged']=false;
		echo "Dati inseriti errati!";
	}
	mysqli_close($connessione);
} else {
?>

<html>
<head>
	<title>Riproduttore Audio - Login</title> <!-- Titolo della pagina -->
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
				<a class="navbar-brand" href="#">Riproduttore Audio - Login</a>
			</div>
		</div>
	</nav>
</head>
<body>
	<div id="container" class="container"> <!-- Il div che contiene il contenuto -->
		<div class="row">
			<center>
				<h1>Autenticazione</h1>
				<p>Per poter utilizzare il sistema e' necessario possedere un' username e una password! <br>
				Se non ne possiedi una, chiedi all'amministratore di fornirtela</p>
				<div class="table-responsive">
					<form action="#" method="POST">
						<table class="table table-hover" id="tabSongs">
							<tr>
								<td>Nome Utente</td>
								<td><input type="text" name="user" placeholder="Nome Utente"></td>
							</tr>
							<tr>
								<td>Password</td>
								<td><input type="password" name="pass"></td>
							</tr>
								<td colspan="2"><center><input type="submit" value="Esegui il Login"></center></td>
						</table>
					</form>
				</div>
			</center>
		</div> <!-- row -->
	</div> <!-- container -->
</body>
	<footer class="footer">
			<div class="row">
				<center><p>(C) - Devin Taietta</p></center>
			</div>
		</div>
	</footer>
</html>
<?php } ?>
