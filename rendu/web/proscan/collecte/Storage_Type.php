<?php
require '../header2.php';
session_start();
?>

<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>REPARTITION MEMOIRE</title>
</head>

<body>
<?php


require ('options.php');


////////////////////////////////////////////////////////

$array = array("hrStorageIndex","hrStorageType","hrStorageDescr","hrStorageAllocationUnits","hrStorageSize","hrStorageUsed");

   $session = new SNMP(SNMP::VERSION_2c, $_SESSION["IP"], $_SESSION["community"]);

echo"<table border='1'>
  <tr><th>Num<th>Type<th>Path<th><th>Storage Size<th>Rate </tr>";
    echo "<tr>";
	echo "----Storage Table---- ".'<br>';
	$op=new option();
	$op->load();
	$interf=$session->walk("$array[0]",TRUE);
       foreach($interf as $i) {
		  $toto=1;
	      $indice=$op->retreive($i);
		  for($j=0;$j<count($array);$j++)
          {$inf="$array[$j].".$indice;
	      $inf=$session->get($inf);
		  $des_interf=$op->retreive($inf);
		  if($j==4)
		  {$toto=$des_interf;
		  if($toto==0)
		  $toto=1;
		  }
		  if($j==5)
		  $des_interf=number_format(100*($des_interf/$toto),2)."%"; 
		  echo "<td>".$des_interf."</td>";
		  }
		  echo"</tr>";
		         }
	   echo '</table>';
	   


?>


</body>
</html>