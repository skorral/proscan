<?php  
session_start();
require '../header.php';

?>


<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Test</title>
</head>

<body>
<?php
if(isset($_GET["ip"]) && isset($_GET["community"]))
	{$_SESSION["IP"]=$_GET["ip"]; 
	   $_SESSION["community"]=$_GET["community"];
	}
?>


<form>
<form name="input" action="test.php" method="GET">


<TABLE ALIGN="center" BGCOLOR="#CCCC99" BORDER="1" CELLPADDING="4" WIDTH="70%"> 
<TR> 

 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
<B><FONT COLOR="#336633" SIZE="+1"> Effectuer un test sur un equipement : </FONT></B></TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70"> 

<B><FONT COLOR="#336633" SIZE="+1">




</FONT></B>
</TD>

<TD NOWRAP="NOWRAP" WIDTH="10">



</TD>
 
</TR> 



<TR> 


<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
      <B><FONT COLOR="#336633" SIZE="+1">  
ADRESSE IP:  </FONT></B></TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 


<B><FONT COLOR="#336633" SIZE="+1">  <input type="text" name="ip"><br>  </FONT></B></TD>
 

</TR> 



<TR> 

<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 

<B><FONT COLOR="#336633" SIZE="+1"> COMMUNITY :  </FONT></B>


</TD>


<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 

<B><FONT COLOR="#336633" SIZE="+1"> <input type="text" name="community">  </FONT></B>


</TD>


<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 

<B><FONT COLOR="#336633" SIZE="+1"> <input type="submit" value="Submit">  </FONT></B>


</TD>
 
</TR>





</form>


<?php
if(isset($_GET["ip"])){

echo'

<TABLE ALIGN="center" BGCOLOR="#CCCC99" BORDER="1" CELLPADDING="4" WIDTH="70%"> 
<TR> 
<TD NOWRAP="NOWRAP" WIDTH="10"><BR></TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
<B><FONT COLOR="#336633" SIZE="+1"> SELECTIONNER VOTRE ACTION SUR : </FONT></B></TD>
 
<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70"> 

<B><FONT COLOR="#336633" SIZE="+1">
';

echo '( IP:';
echo $_SESSION["IP"];

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
  Partionnement de Stock  </FONT></B></TD>
 


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