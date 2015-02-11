<?php
require '../header2.php';
session_start();
?>


<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Les Ports TCP</title>
</head>

<body>

<?php


require ('options.php');

$array = array("tcpConnState","tcpConnLocalAddress","tcpConnLocalPort","tcpConnRemAddress","tcpConnRemPort");

   $session = new SNMP(SNMP::VERSION_2c, $_SESSION["IP"], $_SESSION["community"]);

echo"<table border='1'>
  <tr><th>Etat de connection<th>Adresse locale<th>Num de Port<th>Nom de Services<th><th>Adresse Distante<th>Num de Port Distante</tr>";
    echo "<tr>";
	
	echo "#--- Les PORTs Ouvert TCP--- ".'<br>';
	$table=array(array()); //déclaration d'un tableau de  deux dimensions
	$op=new option();
	for($i=0;$i<count($array);$i++)
	  { $table[$i]=$session->walk("$array[$i]",TRUE);
	    $table[$i]=$op->transforme($table[$i]);
	  }
	 //echo count($table[0]);
	for($i=0;$i<count($table[0]);$i++) 
	     {  for($j=0;$j<count($table);$j++)
		      {  $inf=$op->retreive($table[$j][$i]);
			   echo "<td>".$inf."</td>";
			        if($j==2)
				 	 // echo "<td>".gethostbyaddr($inf)."<td>";

			    echo "<td>".getservbyport($inf, "TCP")."<td>";
			 }
		    echo "<td> TCP </td>";
		    echo"</tr>";
		 }	
	   echo '</table>';
	   
	  // gethostbyaddr( '127.0.0.1' );
	   
?>

</body>
</html>