<html>
	<h1> PHP simple post request</h1>
	<?php if ($_POST["yep"]) { ?>
		<p>You just pushed something via the form : <?php echo $_POST["yep"]; ?></p>
	<?php } else { ?>
		<form action="post.php" method="POST">
			<input name="yep" type="input"/>
			<input type="submit" value="Submit" />
		</form>
	<?php } ?>
</html>