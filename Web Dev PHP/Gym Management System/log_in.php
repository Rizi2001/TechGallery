<!doctype html>
<html>
<head>
	<title></title>
</head>
<body style="background-color:grey;">
<h1><img alt="" src="p4.jpeg" style="margin: 5px 500px; width: 500px; height: 250px; border-width: 5px; border-style: solid;" /></h1>

<hr />
<h1 style="text-align: center;">FIT ME</h1>

<h2 style="font-style: italic; text-align: center;">Your ultimate health partner</h2>

<p style="text-align: center;">Enter your <u><strong>User Name</strong></u> and <u><strong>Password</strong></u> below to access your FIT ME account.</p>

<hr />
<p>&nbsp;</p>

<h1 style="text-align: center;">Login as User</h1>

<form action="" method="POST" style="text-align: center;">
<div class="container"><label for="uname"><b>User ID</b></label> <input name="id" id = "mid" placeholder="Enter User Id" required="" type="text" /> <label for="psw"><b>Password</b></label> <input name="psw" id = "psw" placeholder="Enter Password" required="" type="password" /><input type="submit" name="save" value="LogIn"></button></div>
</form>

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
	if(isset($_POST['save']))
	  {	 
		  $id = $_POST['id'];
		  $pass = $_POST['psw'];

		  $query = oci_parse($con, "SELECT * FROM members WHERE m_ID = '$id' AND m_password = '$pass'");
		  $r = oci_execute($query);
		  $arr = oci_fetch_array($query);
		  session_start();
		  $_SESSION['MID'] = $id;
		  $fname = $arr[1];
		  $_SESSION['NAME'] = $fname;
		  echo "<br>";
		  if ($arr) 
		  {
			  header("location: home.php");
		  }
		  else
		  {
			  echo "Incorrect Username or Password !";
				  
		  }
		  
	  }
?>

<hr />
<h2 style="font-style: italic; text-align: center;">Not a member, sign up below to get full access to our services.</h2>

<p style="text-align: center;"><em><a href="Sign_up.php">REGISTER NOW.</a></em></p>
<p>&nbsp;</p>

<p>&nbsp;</p>


<p style="text-align: center;">Enter your <u><strong>User Name</strong></u> and <u><strong>Password</strong></u> below to access your FIT ME account.</p>

<hr />
<p>&nbsp;</p>



<h2 style="text-align: center;" text-align:="">Thank you for visiting FIT ME.<img alt="smiley" height="23" src="https://www.quackit.com/html/online-html-editor/ckeditor/ckeditor_4.4.1_full/plugins/smiley/images/regular_smile.png" title="smiley" width="23" /></h2>

<p>&nbsp;</p>

<p>&nbsp;</p>
</body>
</html>









