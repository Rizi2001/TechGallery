<!doctype html>
<html>
<head>
	<title></title>
</head>
<body style="background-color:grey;">
<h1 style="text-align: center;">Enter your <i>NUTRITION PLAN</i>&nbsp;below&nbsp;</h1>

<hr />
<form action="" method="POST">



<h1 style="text-align: center;">Enter your&nbsp;<i>Nutrition Intake Plan</i>&nbsp;below</h1>

<p style="text-align: center;">&nbsp;<strong>Daily Target Calories</strong><label for="eid"><b>:</b></label>&nbsp;&nbsp;<input id="cal" name="cal" type="number" />&nbsp;&nbsp;<br />
<br />
<label for="bcal"><b>BreakFast:&nbsp; &nbsp;</b></label><input id="bcal" name="bcal" type="number" />&nbsp; &nbsp;&nbsp;<label for="lcal"><b>Lunch:&nbsp; &nbsp; &nbsp;&nbsp;</b></label><input id="lcal" name="lcal" type="number" /><br />
<br />
<label for="dcal"><b>Dinner:&nbsp; &nbsp;</b></label><label for="dcal"><b>&nbsp; &nbsp;</b></label><input id="dcal" name="dcal" type="number" />&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<b>Not allowed</b><label for="dept"><b>:&nbsp; &nbsp;&nbsp;</b></label><input id="dept" name="dept" type="text" /><br />
<br />
<input name="save" type="submit" value="Save to Database" /></p>
<p style="text-align: center;">&nbsp;</p>
</form>

<?php  // creating a database connection 
   $db_sid = 
   "(DESCRIPTION =
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
	
	if(isset($_POST['save']))
	  {	 
		  $cal = $_POST['cal'];
		  $bcal = $_POST['bcal'];
		  $lcal = $_POST['lcal'];
		  $dcal = $_POST['dcal'];
		  session_start();
		  $mid = $_SESSION['MID'];
		  
		  
		  $query = oci_parse($con, "INSERT INTO nutrition(nu_ID, m_ID, nu_dailytarget, nu_breakfast,nu_lunch,nu_dinner) 
			                        values (nu_ID.nextval, $mid, $cal,$bcal,$lcal, $dcal)");
		  $r = oci_execute($query);
		  echo "<br>";
		  
		  if ($r) 
		  {
			  echo "\nDATA ADDED IN Nutrition!";
		  }
		  else
		  {
			  echo "Error Try recheking your credentials again!";
				  
		  }
	  }
?>

<p style="text-align: center;">&nbsp;</p><p style="text-align: center;"><em><a href="home.php">Click Here to get back to Home Page.</a></em></p>
</body>
</html>
