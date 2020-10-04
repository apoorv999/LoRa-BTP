<?php
 
header('content-type: application/json; charset=utf-8');
header("access-control-allow-origin: *");

//Creating Array for JSON response
$response = array();
 
    // Include data base connect class
    $filepath = realpath (dirname(__FILE__));
	require_once($filepath."/db_connect.php");
 
    // Connecting to database 
    $db = new DB_CONNECT();
 
    // Fire SQL query to delete pollution level data by id
    $result = mysql_query("TRUNCATE TABLE pollutionlevel");
 
        // successfully deleted
        $response["success"] = 1;
        $response["message"] = "Table Successfully Truncated";
 
        // Show JSON response
        echo json_encode($response);
?>