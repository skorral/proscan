<?php
require '../header2.php';
session_start();
?>

<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>TABLEAU DE ROUTAGE</title>
</head>

<body>





<?php



$mib_path='D:\mibbrowser\mibs';   
  if ($handle = opendir($mib_path))
   {   while (false !== ($file = readdir($handle)))
         {  if($file!='.')
             if($file!='..')
               snmp_read_mib($mib_path.'\\'.$file);    // cette fonction pour la compilation des mibs pour utiliser //seulement les noms
         }
  }
 
 ////////////////////////////////////////////////////////
 
 function retreive($string)
        {    $table = array("/INTEGER: /","/IpAddress: /","/OID: HOST-RESOURCES-TYPES::/","/OID: /","/STRING: /","/Hex-STRING/", "/Gauge32:/","/Timeticks:/","/Counter32:/");
         $inf=preg_replace($table,'',$string);
           return $inf;
        }

////////////////////////////////////////////////////////

$array = array("ipRouteDest","ipRouteMetric1","ipRouteNextHop","ipRouteType","ipRouteAge","ipRouteMask");

   $session = new SNMP(SNMP::VERSION_2c, $_SESSION["IP"], $_SESSION["community"]);

echo"<table border='1'>
  <tr><th>Destination<th><th>Mertic<th><th>Passerelle<th><th>Type de Routage<th><th>Derniere mise à jour (en s)<th><th>Masque<th> </tr>";
    echo "<tr>";
	echo "----Le Tableau de Routage---- ".'<br>';
	
	$interf=$session->walk("$array[0]",TRUE);
       foreach($interf as $i) {
	      $indice=retreive($i);
		  for($j=0;$j<count($array);$j++)
          {$inf="$array[$j].".$indice;
	         $inf=$session->get($inf);
		        $des_interf=retreive($inf);
		         echo "<td>".$des_interf."<td>";
		       }
		  echo"</tr>";
		         }
	   echo '</table>';
	   








































?>

</body>
</html>