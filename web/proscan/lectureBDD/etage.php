<!doctype html>

<html>
<head>
<meta charset="utf-8">
<title>Supervision des équipements</title>
</head>

<body>
<?php


include 'proscan.php';

if(isset($_POST["choix1"]))
    { $_SESSION["bat"]=$_POST["choix1"];}
	
	if(isset($_SESSION["bat"]))
	 {echo "BATIMENT ".$_SESSION["bat"].'<br>';
//	 $response1=mysql_query('select ID from Batiment where Name=\''.$_SESSION["bat"].'\'');
//	    {while($row=mysql_fetch_array($response1))
//         { $response2=mysql_query('select Number from etages where BatimentID=\''.$row["ID"].'\'');
//	      {

$bat = $_SESSION["bat"]	;
			  
			  $response=mysql_query('select ip from client');
		  
		  if(mysql_num_rows($response)!=0)
		    { echo '<form action="result.php" method="post">
		       <select name="choix2">';
		      while($row=mysql_fetch_array($response))
			    {
				  echo "<option>".$row["ip"]."</option>"; 
			    }
		     echo '</select>
		    -----------> <input type="submit" value="confirmer"/>
		    </form>';}
			else { echo "Vide";}
           }
//		}
//	 }


?>
</body>
</html>