<html>
<body style="background-color:powderblue;">
 <style>
h1 {text-align: center;}
body {background-color: powderblue;}
h1   {color: c61f0c;}
p    {color: yellow;
font-family:  Verdana;
  font-size: 200%;
}
input[type=submit] {
    width: 20em;  height: 2em;
}
input[type=button], input[type=submit], input[type=reset] {
  background-color:#00002B;
  border: none;
  color: white;
  padding: 16px 32px;
  text-decoration: none;
  margin: 4px 2px;
  cursor: pointer;
  font-size: 160%;

  top: 150%;
  left: 150%;
 -ms-transform: translate(+80%, +80%);
  transform: translate(+80%, +80%);
}
body {
  background-image: url('blue.jpg');
 background-repeat: no-repeat;

  background-size: cover;
  background-size: 100% 300%;
}
</style>
 <h2>Lowest Humidity </h2>

<?php
$servername = "localhost";
$username = "bojan";
$password = "pijanista";
$dbname = "Temperature_Humidity";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, Temperature, Humidity, reg_date FROM Temperature_Humidity ORDER BY Temperature  LIMIT 1";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
echo "id: " . $row["id"]. "<br>";
    echo "Temperature:  " .$row["Temperature"]. "<br>";
    echo " Humidity: " . $row["Humidity"]. "<br>";
    echo "Time and date: " .$row["reg_date"]. "<br>";
      }
} else {
  echo "0 results";
}
$sql = "SELECT id, Temperature, Humidity, reg_date FROM Temperature_Humidity ORDER BY Humidity DESC LIMIT 1";
$result = $conn->query($sql);
echo "<br>";
$conn->close();
?>
 <h2>Highest Humidity </h2>

<?php
$servername = "localhost";
$username = "bojan";
$password = "pijanista";
$dbname = "Temperature_Humidity";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, Temperature, Humidity, reg_date FROM Temperature_Humidity ORDER BY Humidity DESC LIMIT 1";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
echo "id: " . $row["id"]. "<br>";
    echo "Temperature:  " .$row["Temperature"]. "<br>";
    echo " Humidity: " . $row["Humidity"]. "<br>";
    echo "Time and date: " .$row["reg_date"]. "<br>";
      }
} else {
  echo "0 results";
}

$conn->close();
?>
</body>
</html>
