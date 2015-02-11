<!doctype html>

<html>
<head>
<meta charset="utf-8">
<title>BD</title>
</head>

<body>
<table>
                <tr>
				
 					
                <TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70">Id</td>
				<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70">idclient </td>
				<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70">idScript</td>
				<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70">result</td>
                                    
				</tr>



<?php 

require '../headersupervision.php';
//include ('connectBD.php');

// Déclaration des paramètres de connexion


// Généralement la machine est localhost
// c'est-a-dire la machine sur laquelle le script est hébergé







// Connexion au serveur
$base=mysqli_connect('localhost', 'root','') or die("erreur de connexion au serveur");

mysqli_select_db($base, 'proscan') or die("erreur de connexion a la base de donnees");



$response=mysqli_query($base,"SELECT id, idclient, idscript, result from result");

if(!mysqli_fetch_array($response)){
echo "Aucun résultat trouvé\n";
}
else{
while($row=mysqli_fetch_array($response))
   { 
   
   
            ?>
                <tr>
                    <td><?php echo $row['id'];?></td>
					<td><?php echo $row['idclient'];?></td>

					<td><?php echo $row['idscript'];?></td>
					<td><?php echo $row['result'];?></td>

					

                    
                </tr>
				<?php
    
   
   
   }
   


}

 ?>
 </tr>

</table>

</body>
</html>
