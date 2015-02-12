<?php

 class option
 {    
  function load()
     { $mib_path='D:\usr\share\snmp\mibs';   
       if ($handle = opendir($mib_path))
          { while (false !== ($file = readdir($handle)))
              {  if($file!='.')
                if($file!='..')
                 snmp_read_mib($mib_path.'\\'.$file);   
              }
         }
      }
 ////////////////////////////////////////////////////////
 function retreive($string)
        {    $table = array("/INTEGER: /","/IpAddress: /","/OID: HOST-RESOURCES-TYPES::/","/OID: /","/STRING: /","/Hex-STRING/", "/Gauge32:/","/Timeticks:/","/Counter32:/");
		     $inf=preg_replace($table,'',$string);
		       return $inf;
        }
//////////////////////////////////////////////////////////////
/////transformer un tableau associatif à un tableau indèxé
	function transforme($asso_table)
       {  $table=array();
	      $i=0;
		  foreach($asso_table as $valeur)
		      {  $table[$i]=$valeur;
		         $i++;
		      }
	      return $table;
      }		  
 }


?>