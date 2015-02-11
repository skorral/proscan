<?php
require '../header2.php';
session_start();
?>


<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Les Ports UDP</title>
</head>

<body>
<?php

require ('options.php');


////////////////////////////////////////////////////////

$array = array("udpLocalAddress","udpLocalPort");

   $session = new SNMP(SNMP::VERSION_2c, $_SESSION["IP"], $_SESSION["community"]);
echo"<table border='1'>
  <tr><th>LocalAddress<th>num_port<th>Type du port </tr>";
    echo "<tr>";
	echo "---- Les PORTS Ouvert UDP--- ".'<br>';
	$op=new option();
	$addr=$session->walk("$array[0]",TRUE);
	$port=$session->walk("$array[1]",TRUE);
	$addr_table=$op->transforme($addr);
	$port_table=$op->transforme($port);
	
	for($i=0;$i<count($addr_table);$i++) 
	   { $addr=$op->retreive($addr_table[$i]);
	     $port=$op->retreive($port_table[$i]);
		   echo "<td>".$addr."</td>";
		   echo "<td>".$port."</td>";
		   echo "<td> UDP </td>";
		    echo"</tr>";
		}
	   echo '</table>';
	   



?>

</body>
</html>