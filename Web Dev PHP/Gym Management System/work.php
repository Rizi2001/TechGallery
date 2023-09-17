<!doctype html>
<html>
<head>
	<title></title>
</head>
<body style="background-color:grey;">
<h1 style="text-align: center;">Enter your <i>WORK OUT PLAN</i>&nbsp;below&nbsp;</h1>

<hr />
<form action="" method="POST">

<p style="text-align: center;">&nbsp;<strong>Muscle Group</strong><label for="eid"><b>:</b></label> &nbsp; &nbsp; &nbsp; &nbsp;<input id="mg" name="mg" type="text" /><br />
<br />
<label for="job"><b>Weight Loss:</b></label><label for="fname" style="text-align: center;"><b>&nbsp; </b></label><label for="job"><b>&nbsp;</b></label> <input name="WL" type="checkbox" value="WL" />&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;<label for="job" style="text-align: center;"><b>Weight Gain:</b></label><label for="fname" style="text-align: center;"><b>&nbsp;&nbsp;</b></label><label for="job" style="text-align: center;"><b>&nbsp;</b></label><span style="text-align: center;">&nbsp;</span><input name="WG" type="checkbox" value="WG" /><span style="text-align: center;">&nbsp;&nbsp;</span><br />
<br />
<label for="eq"><b>Equipement:&nbsp; &nbsp;&nbsp; &nbsp;</b></label><input id="eq" name="eq" type="text" />&nbsp; &nbsp; <label for="exN"><b>Exercise Name:&nbsp; &nbsp; &nbsp;&nbsp;</b></label><input id="exN" name="exN" type="text" /><br />
<br />
<label for="tAD"><b>Times a day:&nbsp;</b></label><label for="tAD" style="text-align: center;"><b>&nbsp; &nbsp;</b></label><input id="tAD" name="tAD" type="number" />&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<b style="text-align: center;">Times a week</b><label for="tAW"><b>:&nbsp; &nbsp;&nbsp;</b></label><input id="tAW" name="tAW" type="number" /><br />
<br />
<input name="save" type="submit" value="Save to database" /></p>

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
    { 
		  die('Could not connect to Oracle: '); 
	} 

	if(isset($_POST['save']))
	  {	 
		  $mg = $_POST['mg'];
		  $eq = $_POST['eq'];
		  $exN = $_POST['exN'];
		  $tAD = $_POST['tAD'];
		  $tAW = $_POST['tAW'];
		  session_start();
		  $mid = $_SESSION['MID'];
		  
		  if(isset($_POST['WG']))
		  {
			  $wp = "Weight Gain";
		  }
		  else
		  {
				$wp = "Weight Loss";
		  }
		  $query = oci_parse($con, "INSERT INTO exercise(ex_ID, m_ID, ex_weightplan, ex_muscleGroup,ex_equipment,ex_name,ex_timesADay,ex_timesAWeek) 
			                        values (ex_ID.nextval, $mid, '$wp', '$mg', '$eq', '$exN', $tAD, $tAW)");
		  $r = oci_execute($query);
		  echo "<br>";
		  if ($r) 
		  {
			  echo "\nDATA ADDED IN WORKOUT!";
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
