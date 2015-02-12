<?php

  $port='';
  $protocol='';
function service($port,$protocol)
 { $this->port=$port;
   $this->protocol=$protocol;
   $trouve=false;
   $xml=simplexml_load_file("service-names-port-numbers.xml"); 
   foreach( $xml as $record ) 
     {  if( $record->number==$this->port )
          { if($record->description=='Unassigned' || $record->description=='Reserved' )
		         {  $trouve=true;
					return $record->description;    
			     }
		     else  
			     {   $trouve=true; 
				   return  $record->name;
                 }
           }
      }
  if($trouve==false)
		return 'Unassigned';
  } 
   


/*
require('tcp.php');
  
 $port=array();
 $proto_trans=array();
 $services=array();
 
//function csv_to_array() 
	$filename='service-names-port-numbers.csv';
  if(!file_exists($filename) || !is_readable($filename))
       return 'pas du fihier de service http://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xml';
	$header = NULL;
    $data = array();
  if (($handle = fopen($filename, 'r'))!== FALSE)
      { while(($row = fgetcsv($handle, ','))!=false)
            { if(!empty($row[0]) )
			        array_push($services,$row[0]);
			   else array_push($services,'unsigned');
			       array_push($port,$row[1]);
				   array_push($proto_trans,$row[2]);
		    }
         fclose($handle);
      } 
	 
	 /// echo $data[0]['Service Name'].'///////////';
////////////////////////////////////////////////////////////////////////
echo 'les services dans une machine'.'<br>';
  for($i=0;$i<count($tab);$i++) 
    {  for($j=0;$j<13380;$j++)
	         {       if($tab[$i]==$port[$j])
				                 { echo  $services[$j].'||||||'.$tab[$i].'<br>';
                                    break;
								 }
				     else   {  	if(preg_match('/-/',$port[$j]))
                                   {     $num_port=preg_split('/-/',$port[$j]);
				                        if($tab[$i]>=$num_port[0] && $tab[$i]<=$num_port[1])
					                       {   echo  $services[$j].'||||||'.$tab[$i].'<br>';
								               break;
								           }
					                   else  continue;
	                               }							 
					        }
			 }
	 }
  
  
 */

?>