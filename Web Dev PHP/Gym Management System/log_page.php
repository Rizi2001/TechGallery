<!doctype html>
<html>
<head>
	<title></title>
	<style type="text/css">
	</style>
</head>
<body style="background-color:grey;">
<h1 style="text-align: center;">Enter your <i>Daily Log </i>below&nbsp;</h1>
<hr />


<form action="" method="POST">
<br/>
<p style="text-align: center;">&nbsp;
<?php  // creating a database connection 
	#error_reporting = E_ALL & ~E_NOTICE
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
	
	
	session_start();
	$mid = $_SESSION['MID'];
	
	$query = oci_parse($con, "SELECT * from exercise where m_ID = $mid");
		  $r = oci_execute($query);
		  echo "YOUR WORKOUT PLANS: <br>";
		  while($row = oci_fetch_array($query, OCI_BOTH + OCI_RETURN_NULLS))
		  {
			echo "Plan # " ,$row['EX_ID'], "<br>", "Equipment Used: ", $row['EX_EQUIPMENT'], "<br>", "Exercise Name:  " , $row['EX_NAME'], "<br>", "Times A Day:  ", $row['EX_TIMESADAY'], "<br>", "Times A Week:  ", $row['EX_TIMESAWEEK'], "<br><br>";
		  }
		  
		  
	
	?>
<br />
<label for="eID"><b>Plan #:&nbsp; &nbsp;&nbsp; &nbsp;</b></label><input id="eID" name="eID" type="Number" />
<label for="eq"><b>Equipement:&nbsp; &nbsp;&nbsp; &nbsp;</b></label><input id="eq" name="eq" type="text" />&nbsp; &nbsp; <label for="exN"><b>Exercise Name:&nbsp; &nbsp; &nbsp;&nbsp;</b></label><input id="exN" name="exN" type="text" /><br />
<br />
<label for="tAD"><b>Times a day:&nbsp;</b></label><label for="fname" style="text-align: center;"><b>&nbsp; &nbsp;</b></label><input id="tAD" name="tAD" type="number" />&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<b style="text-align: center;">Times a week</b><label for="tAW"><b>:&nbsp; &nbsp;&nbsp;</b></label><input id="tAW" name="tAW" type="number" /><br />
&nbsp;</p>

</p>
	
<hr />
<br />
<p style="text-align: center;">&nbsp;<?php
$query = oci_parse($con, "SELECT * from nutrition where m_ID = $mid");
		  $r = oci_execute($query);
		  echo "YOUR WORKOUT PLANS: <br>";
		  while($row = oci_fetch_array($query, OCI_BOTH + OCI_RETURN_NULLS))
		  {
			echo "Plan # " ,$row['NU_ID'], "<br>", "Breakfast Calories: ", $row['NU_BREAKFAST'], "<br>", "Lunch Calories:  " , $row['NU_LUNCH'], "<br>", "Dinner Calories:  ", $row['NU_DINNER'], "<br><br>";
		  }
		  
		  
	
	?></p>
<p style="text-align: center;">
<label for="nID"><b>Plan #:&nbsp; &nbsp;&nbsp; &nbsp;</b></label><input id="nID" name="nID" type="number" />
<br />


<label for="bcal"><b>BreakFast:&nbsp; &nbsp;</b></label><input id="bcal" name="bcal" type="number" />&nbsp; &nbsp;&nbsp;<label for="lcal"><b>Lunch:&nbsp; &nbsp; &nbsp;&nbsp;</b></label><input id="lcal" name="lcal" type="number" /><br />
<label for="lcal"><b>Dinner:&nbsp; &nbsp; &nbsp;&nbsp;</b></label><input id="dcal" name="dcal" type="number" /><br />

<br />
<input name="save" type="submit" value="Save to Database" /></p>

<p style="text-align: center;">&nbsp;</p>

<p style="text-align: center;">&nbsp;</p>



<p style="text-align: center;"><em><a href="home.php">Click Here to get back to Home Page.</a></em></p>

<p style="text-align: center;">&nbsp;</p>
</form>

<?php 
	if(isset($_POST['save']))
	  {	 
		  $eid = $_POST['eID'];
		  $nid = $_POST['nID'];
		  $eq = $_POST['eq'];
		  $exN = $_POST['exN'];
		  $tAD = $_POST['tAD'];
		  $tAW = $_POST['tAW'];
		  $bcal = $_POST['bcal'];
		  $lcal = $_POST['lcal'];
		  $dcal = $_POST['dcal'];
		  
		  $_SESSION['log_eID'] = $eid;
		  $_SESSION['log_nID'] = $nid;
		  $_SESSION['log_eq'] = $eq;
		  $_SESSION['log_exN'] = $exN;
		  $_SESSION['log_timesAWeek'] = $tAW;
		  $_SESSION['log_timesADay'] = $tAD;
		  $_SESSION['log_bcal'] = $bcal;
		  $_SESSION['log_lcal'] = $lcal;
		  $_SESSION['log_dcal'] = $dcal;
		  
		  
		  
		  $query = oci_parse($con, "INSERT INTO log(log_ID, ex_ID, nu_ID, log_equipment, log_exname, log_timesaday, log_timesaweek,log_breakfast,log_lunch,log_dinner) 
			                        values (log_id.nextval, $eid, $nid,'$eq','$exN', $tAD,$tAW, $bcal, $lcal, $dcal)");
		  $r = oci_execute($query);
		  echo "<br>";
		  if ($r) 
		  {
			  header("location: log_result.php");
		  }
		  else
		  {
			  echo "Error Try recheking your credentials again!";
				  
		  }
		  
		  
	  }
?>
<p style="text-align: center;"><em><a href="log_result.php">Click Here to Check Progress.</a></em></p>
</body>
</html>