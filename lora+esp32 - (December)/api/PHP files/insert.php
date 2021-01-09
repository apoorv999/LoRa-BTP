<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
//Creating Array for JSON response
$response = array();
 
// Check if we got the field from the user
if (isset($_GET['lat']) && isset($_GET['lon']) && isset($_GET['turbidity']) && isset($_GET['ph']) && isset($_GET['ec'])) {
 
    $lat = $_GET['lat'];
    $lon = $_GET['lon'];
    $turbidity = $_GET['turbidity'];
    $ph = $_GET['ph'];
    $ec = $_GET['ec'];
 
    // Include data base connect class
    $filepath = realpath (dirname(__FILE__));
	require_once($filepath."/db_connect.php");
 
    // Connecting to database 
    $db = new DB_CONNECT();
 
    // Fire SQL query to insert data in weather
    $result = mysql_query("INSERT INTO pollutionlevel(lat,lon,turbidity,ph,ec) VALUES('$lat','$lon','$turbidity','$ph','$ec')");
 
    // Check for succesfull execution of query
    if ($result) {
        // successfully inserted 
        $response["success"] = 1;
        $response["message"] = "pollution level logged.";
 
        // Show JSON response
        echo json_encode($response);
    } else {
        // Failed to insert data in database
        $response["success"] = 0;
        $response["message"] = "Something has been wrong";
 
        // Show JSON response
        echo json_encode($response);
    }
} else {
    // If required parameter is missing
    $response["success"] = 0;
    $response["message"] = "Parameter(s) are missing. Please check the request";
 
    // Show JSON response
    echo json_encode($response);
}
?>