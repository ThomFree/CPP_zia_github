<?php session_start() ;
	$_SESSION["rank"] = "The Big Genious Administrator";
?>
<html>
	<h1> PHP basic session test</h1>
	<p> A session has been setup and you are <?php echo $_SESSION["rank"]; ?></p>
	<p> To be sure that it is working follow this link and watch your rank : <a href="/admin/admin.php">Here !</a></p>
</html>