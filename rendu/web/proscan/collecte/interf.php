<?php require '../header2.php'; ?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        
        <title>INTERFACES</title>
    </head>

    <body> 



<?php
session_start();
?>


<?php


//chemin de la base MIB
$mib_path='D:\usr\share\snmp\mibs';   
//Ouvrir le dossier
  if ($handle = opendir($mib_path))
    {   while (false !== ($file = readdir($handle)))
          {  if($file!='.')
             if($file!='..')
               snmp_read_mib($mib_path.'\\'.$file);    // cette fonction pour la compilation des mibs pour utiliser seulement les noms
          }
   }
  
////////////////////////////////////////////////////////////////


class option
 {    
    function retreive($string)
       {   $table = array("INTEGER", "STRING", "Hex-STRING", "Gauge32","Timeticks","Counter32");
	       $element=explode(":",$string);
	     if(in_array($element[0],$table))
	         {  $rem=$element[0].': ';
		        $inf=str_replace($rem,'',$string);
		        $inf=str_replace(' ','',$inf);
		          return $inf;
			 }
      }
 }


////////////////////////////////////////////////////////////////
$array = array("ifIndex","ifDescr","ifType","ifMtu","ifSpeed","ifPhysAddress","ifAdminStatus","ifOperStatus","ifLastChange","ifInOctets","ifInUcastPkts","ifInNUcastPkts","ifInDiscards","ifInErrors","ifInUnknownProtos","ifOutOctets","ifOutUcastPkts","ifOutNUcastPkts","ifOutDiscards","ifOutErrors","ifOutQLen","ifSpecific");
 
   $session = new SNMP(SNMP::VERSION_2c, $_SESSION["IP"], $_SESSION["community"]);

echo"<table border='1'>
    <tr><th>Index<th>Description<th>Type<th>Mtu<th>Speed<th>Physical Address<th>Admin Status<th>Current Operational State<th>Last Change<th>In Octets<th>In Ucast Pkts<th>In NUcast Pkts<th>In Discards<th>In Errors<th>In Unknown Protos<th>Out Octets<th>Out Ucast Pkts<th>Out NUcast Pkts<th>Out Errors<th>Out QLen<th>Specific</tr>";
    echo "<tr>";
	echo "----LES INTERFACES SONT---- ".'<br>';
	 $op=new option();
     $intefaces=$session->get("ifNumber.0");
     $interf=$session->walk("$array[0]",TRUE);
       foreach($interf as $i) {
	   
	      $indice=$op->retreive($i);
		  
		  echo "<td>".$indice."</td>";
		  for($j=1;$j<count($array);$j++)                   
           { $inf="$array[$j].".$indice;
	         $inf=$session->get($inf);
			// echo $inf.'-';
		     $inf=$op->retreive($inf);
		     echo "<td>".$inf."</td>";
		   }
		  echo"</tr>";
		  }
	   
echo "</table>";

?>


</body>
</html>