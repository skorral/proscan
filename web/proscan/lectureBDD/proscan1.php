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
				<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70">Nom</td>
				<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70">Description</td>
				<TD ALIGN="left" HEIGHT="40" NOWRAP="NOWRAP" WIDTH="70">Code</td>
				
                                    
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



$response=mysqli_query($base,"SELECT id, nom, description, code from script");

if(!mysqli_fetch_array($response)){
echo "Aucun résultat trouvé\n";
}
else{
while($row=mysqli_fetch_array($response))
   { 
   
   
            ?>
                <tr>
                    <td><?php echo $row['id'];?></td>
					<td><?php echo $row['nom'];?></td>

					<td><?php echo $row['description'];?></td>
					<td><?php echo $row['code'];?></td>

					

                    
                </tr>
				<?php
    
   
   
   }
   


}

 ?>
 </tr>

</table>

</body>
</html>