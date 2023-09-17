<!doctype html>
<html>
<head>
	<title></title>
</head>

<body style="background-color:grey;">
<hr />

<br>
<br>

<?php  // creating a database connection 
   $db_sid = 
   "  (DESCRIPTION =
    (ADDRESS = (PROTOCOL = TCP)(HOST = DESKTOP-F08UJR7)(PORT = 1521))
    (CONNECT_DATA =
      (SERVER = DEDICATED)
      (SERVICE_NAME = XE)
    )
  )";            // Your oracle SID, can be found in tnsnames.ora  ((oraclebase)\app\Your_username\product\11.2.0\dbhome_1\NETWORK\ADMIN) 
  
   $db_user = "system";   // Oracle username e.g "scott"
   $db_pass = "i191776";    // Password for user e.g "1234"
   $con = oci_connect($db_user, $db_pass, $db_sid); 
   if($con) 
    { //echo "Oracle Connection Successful.";
		
	} 
   else 
      { die('Could not connect to Oracle: '); } 
	  session_start();
	  $mid = $_SESSION['MID'];
	  
	 ?> 
	 <h2 style="text-align: center;"><strong><u>WORKOUT PLAN FOR YOU!</u></strong></h2> 
	 
	 <?php 

			?>
			<h2 style="text-align: center;"><strong><u>WEIGHT GAIN <br> <img src="wg.jpg"></u></strong></h2> 
			<h2 style="text-align: center;"><strong><u>WEIGHT LOSS <br> <img src="wl.jpg"></u></strong></h2> 
		
?>


<p style="text-align: center;"><em><a href="home.php">Click Here to go back to home.</a></em></p>

<p style="text-align: center;"><em><a href="log_in.php">LOG OUT.</a></em></p>


</body>
</html>
