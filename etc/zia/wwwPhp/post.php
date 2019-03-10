<html>
	<h1> PHP simple post request</h1>
	<?php if ($_POST["test"]) { ?>
		<p>You just pushed something via the form : <?php echo $_POST["test"]; ?></p>
	<?php } else { ?>
		<form action="post.php" method="POST">
			<input name="test" type="input"/>
			<input type="submit" value="Submit" />
		</form>
	<?php } ?>
</html>