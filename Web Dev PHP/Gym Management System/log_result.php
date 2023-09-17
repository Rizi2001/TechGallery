<!doctype html>
<html>
<head>
	<title></title>
</head>

<body style="background-color:grey;">
<h1 style="text-align: center;"><strong><u>YOUR PROGRESS!</u></strong></h1>
<hr />

<br>
<br>
<h2 "><strong><u>NUTRITION PROGRESS!</u></strong></h2>
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
	  $eid = $_SESSION['log_eID'];
	  $nid = $_SESSION['log_nID'];
	  $eq = $_SESSION['log_eq'];
	  $exN = $_SESSION['log_exN'] ;
	  $tAW = $_SESSION['log_timesAWeek'];
	  $tAD = $_SESSION['log_timesADay'];
	  $bcal = $_SESSION['log_bcal'];
	  $lcal = $_SESSION['log_lcal'];
	  $dcal = $_SESSION['log_dcal'];
	  
	  
		echo "Your Nutrition Plan Was: <br>";
		$query = oci_parse($con, "SELECT * from nutrition where nu_ID = $nid");
		  $r = oci_execute($query);
		  while($row = oci_fetch_array($query, OCI_BOTH + OCI_RETURN_NULLS))
		  {
			$dt = $row['NU_DAILYTARGET'];
			echo "Total Calories Planned: ",  $row['NU_DAILYTARGET'], "<br>", "Breakfast Calories: ", $row['NU_BREAKFAST'], "<br>", "Lunch Calories:  " , $row['NU_LUNCH'], "<br>", "Dinner Calories:  ", $row['NU_DINNER'], "<br><br>";
		  }
		  
		echo "<br>";
		
		echo "What you achieved: <br>";
		$query = oci_parse($con, "SELECT * from log where nu_id = $nid");
		  $r = oci_execute($query);
		  while($row = oci_fetch_array($query, OCI_BOTH + OCI_RETURN_NULLS))
		  {
				$tcal = ($row['LOG_BREAKFAST'] + $row['LOG_LUNCH'] + $row['LOG_DINNER']);
				echo "Total Calories Gained: ", $tcal, "<br>", "Breakfast Calories Gained: ", $row['LOG_BREAKFAST'], "<br>", "Lunch Calories Gained:  " , $row['LOG_LUNCH'], "<br>", "Dinner Calories Calories:  ", $row['LOG_DINNER'], "<br><br>";
		  }
		echo "<br>";
		echo "<br>";
		$percentage = (($tcal / $dt)*100);
		if($percentage <= 50)
		{
			echo "YOURE DOING WAY LESS THAN WHAT YOU PLANNED GOTTA WORK HARD!", "<br>";
			echo "Progress: ", round($percentage), "%<br>";
		}
		else if($percentage <= 80 AND $percentage > 50)
		{
			echo "YOURE DOING GOOD BUT A SLIGHT PUSH WOULD TAKE YOU ON ANOTHER LEVEL! ","<br>";
			echo "Progress: ", round($percentage), "%<br>";
		}
		
		else
		{
			echo "YOURE DOING GREAT KEEP UP THE GOOD WORK AND YOULL ACHIEVE WHAT YOU DESIRED! ","<br>";
			echo "Progress: ", round($percentage), "%<br>";
		}
		echo "<br>";
		
?>

<h2 "><strong><u>WORKOUT PROGRESS!</u></strong></h2>
<?php 
		echo "Your Workout Plan Was: <br>";
		$query = oci_parse($con, "SELECT * from exercise where ex_ID = $eid");
		  $r = oci_execute($query);
		  while($row = oci_fetch_array($query, OCI_BOTH + OCI_RETURN_NULLS))
		  {
			$tdp = $row['EX_TIMESADAY'];
			$twp = $row['EX_TIMESAWEEK'];
			echo "Exercise Planned: ",  $row['EX_NAME'], "<br>", "Times A Day Planned: ", $row['EX_TIMESADAY'], "<br>", "Times A Week Planned:  " , $row['EX_TIMESAWEEK'], "<br><br>";
		  }
		  
		echo "<br>";
		
		echo "What you achieved: <br>";
		$query = oci_parse($con, "SELECT * from log where ex_id = $eid");
		  $r = oci_execute($query);
		  while($row = oci_fetch_array($query, OCI_BOTH + OCI_RETURN_NULLS))
		  {
				$tdg = $row['LOG_TIMESADAY'];
				$twg = $row['LOG_TIMESAWEEK'];
				echo "Exercise Done: ",  $row['LOG_EXNAME'], "<br>", "Times A Day Done: ", $row['LOG_TIMESADAY'], "<br>", "Times A Week Done:  " , $row['LOG_TIMESAWEEK'], "<br><br>";
		  }
		echo "<br>";
		echo "<br>";
		$percentageD = (($tdg / $tdp)*100);
		$percentageW = (($twg / $twp)*100);
		$percentage = (($percentageD + $percentageW)/2);
		if($percentage <= 50)
		{
			echo "YOURE DOING WAY LESS THAN WHAT YOU PLANNED GOTTA WORK HARD!", "<br>";
			echo "Progress: ", round($percentage), "%<br>";
		}
		else if($percentage <= 80 AND $percentage > 50)
		{
			echo "YOURE DOING GOOD BUT A SLIGHT PUSH WOULD TAKE YOU ON ANOTHER LEVEL! ","<br>";
			echo "Progress: ", round($percentage), "%<br>";
		}
		
		else
		{
			echo "YOURE DOING GREAT KEEP UP THE GOOD WORK AND YOULL ACHIEVE WHAT YOU DESIRED! ","<br>";
			echo "Progress: ", round($percentage), "%<br>";
		}
		echo "<br>";
		
?>

<p style="text-align: center;"><em><a href="log_page.php">Click Here to log another Plan.</a></em></p>

<p style="text-align: center;"><em><a href="home.php">Click Here to go back to home.</a></em></p>

<p style="text-align: center;"><em><a href="log_in.php">LOG OUT.</a></em></p>


</body>
</html>
