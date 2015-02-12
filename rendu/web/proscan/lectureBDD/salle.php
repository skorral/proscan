<!doctype html>

<html>
<head>
<meta charset="utf-8">
<title>Supervision des équipements</title>
</head>

<body>

<?php

include 'etage.php';



	if(isset($_POST["choix2"]) )
	 { $_SESSION["etage"]=$_POST["choix2"];}



	if(isset($_SESSION["bat"])){	 
	 if(isset($_SESSION["etage"]))
	 {  echo  "ETAGE ".$_SESSION["etage"].'<br>';
//	   $result=mysql_query('select ID from Batiment where Name=\''.$_SESSION["bat"].'\'');
//	   $id='';
//	  while($row=mysql_fetch_array($result))
//	      $id=$row["ID"];
//	  $response3=mysql_query('select num_salle from salle where  Etage_ID=\''.$_SESSION["etage"].'\' and Etage_Batiment_ID='.$id.'');


		$response3=mysql_query('select num_salle from salle where  etage_ID=\''.$_SESSION["etage"].'\' and etage_batiment_ID="'.$bat.'"');




	  if(mysql_num_rows($response3)!=0)
	  {
	 echo '<form action="device.php" method="post">';
	 echo '<select name="choix3">';
	 while($row=mysql_fetch_array($response3))
	          { echo "<option>".$row["num_salle"]."</option>"; 
			  }
	echo '</select> ---------->
	    <input type="submit" value="confirmer"/>
		    </form>';
	  }
	  else { echo "Vide";}
		
	 }
	}

?>


</body>
</html>