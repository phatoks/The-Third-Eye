<?php
require_once 'library/meekrodb.2.3.class.php';
require_once 'library/databaseConfig.php';

extract($_REQUEST);
$intensity = ($l==1)?"ON":"OFF";
$flame=($f==1)?"ON":"OFF";
$temperature=$t;
$humidity=$h;
$motion=($m==1)?"DETECTED":"NO";
$alarm=($a==1)?"ON":"OFF";
$time_added=date("Y-m-d H:i:s");
DB::insert('sensor_data', array(
   'light' => $intensity,
  'flame' => $flame,
  'alarm' => $alarm,
  'temperature' => $temperature,
  'humidity' => $humidity,
  'motion' => $motion,
  'updateDateTime' => $time_added
));
 // echo "Intensity: " . $row['intensity'] . "\n";
  //echo "Flame Detected: " . $row['flame'] . "\n";
  //echo "Temperature: " . $row['temperature'] . "\n";
  //echo "Humidity: " . $row['humidity'] . "\n";
  //echo "Motion Detected: " . $row['motion'] . "\n";
  //echo "Date Time: " . $row['updateDateTime'] . "\n";

?>