<html>
	<script type="text/javascipt" src="/test.js"></script>
	<h1> Basic PHP Website </h1>
<ul>
	<li> <a href="get.php?firstVariable=PierreIsTheBest">Try GET superglobals </a> </li>
	<li> <a href="post.php" onClick="alert('TEST');">Try POST superglobals </a> </li>
	<li> <a href="session.php">Try SESSION superglobals </a> </li>
</ul>
<br/>
<br/>
	<?php phpinfo(); ?>
</html>