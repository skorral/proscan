<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Supervision des équipements</title>
</head>
<?php

include 'salle.php';



	if(isset($_POST["choix3"]) )
	 { $_SESSION["salle"]=$_POST["choix3"];}
	 
	 if(isset($_SESSION["salle"]))
	 {
	  echo  "SALLE ".$_SESSION["salle"].'<br>';
//	  $result=mysql_query('select ID from Batiment where Name=\''.$_SESSION["bat"].'\'');
//	   $id='';
//	  while($row=mysql_fetch_array($result))
//	      $id=$row["ID"];
//	 $result=mysql_query('select ID from salle where num_salle=\''.$_SESSION["salle"].'\'');
//		$id_salle='';
//	  while($row=mysql_fetch_array($result))
//	      $id_salle=$row["ID"];
	  $response4=mysql_query('select * from equipement where  Salles_Etage_Batiment_ID=\''.$bat.'\'  and    Salles_ID=\''.$_SESSION["salle"].'\'and salles_Etage_ID=\''.$_SESSION["etage"].'\'');
	  if(mysql_num_rows($response4)!=0)
	   {  
	   echo '
			<TABLE ALIGN="center" BGCOLOR="#CCCC99" BORDER="0" CELLPADDING="4" WIDTH="70%"> 
				<TR> 
					<TD NOWRAP="NOWRAP" WIDTH="10"><BR></TD>
 						
					<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
						<B><FONT COLOR="#336633" SIZE="+1">   
							
							SELECT   </FONT></B></TD>
 
					<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70"> 

					     ADRESSE IP
					</TD>

					<TD NOWRAP="NOWRAP" WIDTH="10">

					     COMMUNAUTE

					</TD>
 
 					<TD NOWRAP="NOWRAP" WIDTH="10">

					     DESCRIPTION

					</TD>
 
					</TR> 
					
						<form action="action.php" method="GET">
						';
						
						 
	  while($row=mysql_fetch_array($response4)){
	            
				echo '
			
				<TR> 
					<TD NOWRAP="NOWRAP" WIDTH="10"><BR></TD>
 						
					<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
						<B><FONT COLOR="#336633" SIZE="+1">   
							
							<input type="radio" name="device" value="'.$row["IP"].'" id="oui" checked="checked" />   </FONT></B></TD>
							 
 
					<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70"> 

					     '.$row["IP"].'
					</TD>

					<TD NOWRAP="NOWRAP" WIDTH="10">

					     '.$row["community"].'

					</TD>
 
 					<TD NOWRAP="NOWRAP" WIDTH="10">

					     '.$row["description"].'

					</TD>
 
					</TR> 
							
				';
				            }
							
				echo ' 
			
				<TR> 
					<TD NOWRAP="NOWRAP" WIDTH="10"><BR></TD>
 						
					<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="140"> 
						<B><FONT COLOR="#336633" SIZE="+1">   
							
							</FONT></B></TD>
 
					<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70"> 

					     
					</TD>

					<TD NOWRAP="NOWRAP" WIDTH="10">

					     <input type="submit" value="Valider" />

					</TD>
 
 					<TD NOWRAP="NOWRAP" WIDTH="10">

					   
					</TD>
 
					</TR> 
							
				</form>
				
				';
							
				
				
				
//				echo $row["IP"].'--'.$row["Community"].'--'.$row["Desc"]; 
	   }	
	 }
//session_destroy();

?>

<body>
</body>
</html>