<?php 
require '../headersupervision.php'; 

//require '../header.php';
include 'connectBD.php';
//include 'device.php';

?>

<?php
 



if(isset($_GET["script"]))
{	$_SESSION["script"]=$_GET["script"];


//if(isset($_SESSION["device"])){
 $result=mysql_query('select IP,description,MAC,community from equipement ');

while($row=mysql_fetch_array($result))
{$desc = $row['description'];
$mac = $row['MAC'];
$_SESSION["community"] = $row['community'];
$_SESSION["IP"] = $row['IP'];
}
//echo $result;

//}
}

?>



<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Affichage</title>
</head>



<body>

<?php
if(isset($_GET["device"])){

echo'

<TABLE ALIGN="center" BGCOLOR="#CCCC99" BORDER="1" CELLPADDING="4" WIDTH="70%"> 
<TR> 
<TD NOWRAP="NOWRAP" WIDTH="10"><BR></TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
<B><FONT COLOR="#336633" SIZE="+1"> SELECTIONNER VOTRE ACTION SUR : </FONT></B></TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70"> 

<B><FONT COLOR="#336633" SIZE="+1">
';
echo $desc;
echo '( IP:';
echo $_GET["device"];
echo ', MAC:';
echo $mac;

echo ')
</FONT></B>
</TD>

<TD NOWRAP="NOWRAP" WIDTH="10">



</TD>
 
</TR> 



<TR> 
<TD NOWRAP="NOWRAP" WIDTH="10"><BR></TD>

<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
      <B><FONT COLOR="#336633" SIZE="+1">  <a href="http://localhost/happy_snmp/collecte/interf.php" color="#336633" >
  Interfaces  </FONT></B></TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 


<B><FONT COLOR="#336633" SIZE="+1">  <a href="http://localhost/happy_snmp/collecte/Storage_Type.php" color="#336633" >
  Partionnement de la mémoire  </FONT></B></TD>
 


<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 

<B><FONT COLOR="#336633" SIZE="+1">  <a href="http://localhost/happy_snmp/collecte/TabDeRoutage.php" color="#336633" >
  Table de Routage  </FONT></B>


</TD>


 
</TR>




<TR> 
<TD NOWRAP="NOWRAP" WIDTH="10"><BR></TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
<B><FONT COLOR="#336633" SIZE="+1">  <a href="http://localhost/happy_snmp/collecte/TCP.php" color="#336633" >
  Les Ports TCP  </FONT></B>
  
  
</TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
<B><FONT COLOR="#336633" SIZE="+1">  <a href="http://localhost/happy_snmp/collecte/UDP.php" color="#336633" >
  Les Ports UDP  </FONT></B>
  
  
</TD>

<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
<B><FONT COLOR="#336633" SIZE="+1">  </FONT></B>
  
  
</TD>
 
</TR>


</TABLE>


';

}
?>


</body>
</html>