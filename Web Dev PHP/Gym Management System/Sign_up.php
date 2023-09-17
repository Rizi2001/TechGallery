<!doctype html>
<html>
<head>
	<title></title>
</head>
<body style="background-color:grey;">
<h1 style="text-align: center;">Enter the information below for signing up.</h1>

<hr />
<form action="" method="POST">
<p style="text-align: center;"><label for="fname"><b>Name:&nbsp; &nbsp; &nbsp;</b></label>&nbsp;<input id="fname" name="fname" type="text" />&nbsp;<strong>Member_ID</strong><label for="eid"><b>:</b></label> <input id="mid" name="mid" type="number" /><br />
<br />
<label for="age"><b>Age:</b></label><label for="fname" style="text-align: center;"><b>&nbsp; &nbsp; &nbsp;</b></label><label for="job"><b>&nbsp; &nbsp;</b></label> <input id="age" name="age" type="number" />&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<label for="gender"><b>Gender:</b></label><input id="gender" name="gender" type="text" /><br />
<br />
<label for="weight"><b>Weight:&nbsp; &nbsp; &nbsp;&nbsp;</b></label><input id="weight" name="weight" type="float" />&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<label for="height"><b>Height:</b></label><input id="height" name="height" type="number" /><br />
<br />
<label for="bmi"><b>BMI:</b></label><label for="fname" style="text-align: center;"><b>&nbsp; &nbsp; &nbsp;</b></label><span style="text-align: center;">&nbsp; &nbsp;</span><input id="bmi" name="bmi" type="float" />&nbsp; &nbsp; &nbsp;&nbsp;<label for="psw"><b>Password:</b></label><input id="psw" name="psw" type="text" /><br />
<br />
<input name="save" type="submit" value="Save to Database" /></p>
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
		  $id = $_POST['mid'];
		  $fname = $_POST['fname'];
		  $pass = $_POST['psw'];
		  $age = $_POST['age'];
		  $gender = $_POST['gender'];
		  $weight = $_POST['weight'];
		  $height = $_POST['height'];
		  $bmi = $_POST['bmi'];
		  
		  $query = oci_parse($con, "INSERT INTO members(m_ID,m_name,m_password,m_age, m_gender,m_weight,m_height,m_bmi) 
			                        values ($id,'$fname','$pass', $age, '$gender', $weight, $height, $bmi)");
		  $r = oci_execute($query);
		  
		  session_start();
		  $_SESSION['MID'] = $id;
		  $_SESSION['NAME'] = $fname;
		  echo "<br>";
		  if ($r) 
		  {
			  header("location: home.php");
		  }
		  else
		  {
			  echo "Error Try recheking your credentials again!";
				  
		  }
	  }
?>
</body>
</html>
