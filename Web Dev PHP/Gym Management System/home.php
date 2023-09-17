<!doctype html>
<html>
<head>
	<title></title>
</head>

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
	$fname = $_SESSION['NAME'];
	#  $query = oci_parse($con, "SELECT m_ID FROM members WHERE m_ID = '$id'");
	#  $r = oci_execute($query);
	#  $arr = oci_fetch_array($query);
	 echo "<br>";
		
?>

<body style="background-color:grey;">
<h1 style="text-align: center;"><strong><u>Home</u></strong></h1>
<hr />

<p style="text-align: center;"><em>WELCOME <?php  echo $fname ?>.</em></p>

<p style="text-align: center;"><em><a href="dp.php">Click here to get a diet plan based on daily target.</a></em></p>

<p style="text-align: center;"><a href="ep.php">Click here to get information about exercise, exercise type based on fitness goal.</p>

<p style="text-align: center;"><em><a href="work.php">Click Here to enter your workout routine.</a></em></p>

<p style="text-align: center;"><em><a href='nut.php'>Click Here to enter your nutrititon intake.</a></em></p>

<p style="text-align: center;"><em><a href="log_page.php">Click Here to enter your daily log.</a></em></p>

<p style="text-align: center;"><em><a href="log_in.php">LOG OUT.</a></em></p>

<p style="text-align: center;">&nbsp;</p>

<p style="text-align: center;">&nbsp;</p>
</body>
</html>
