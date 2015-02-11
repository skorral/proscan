<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Connexion a la base</title>
</head>
<?php
try
{
	$bdd = new PDO('mysql:host=localhost;dbname=proscan', 'root', '');
}
catch(Exception $e)
{
        die('Erreur : '.$e->getMessage());
}
?>
<body>
</body>
</html>