<?php
require_once 'library/meekrodb.2.3.class.php';
require_once 'library/databaseConfig.php';
$row = DB::queryFirstRow("SELECT * FROM sensor_data ORDER BY updateDateTime DESC");
$celsiusValue = $row['temperature'];
$farenhiteValue = ($celsiusValue * 1.8) + 32;

 // echo "Intensity: " . $row['intensity'] . "\n";
  //echo "Flame Detected: " . $row['flame'] . "\n";
  //echo "Temperature: " . $row['temperature'] . "\n";
  //echo "Humidity: " . $row['humidity'] . "\n";
  //echo "Motion Detected: " . $row['motion'] . "\n";
  //echo "Date Time: " . $row['updateDateTime'] . "\n";

?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
<!-- 
This template is designed by Sergey Pimenov using Metro-UI-CSS
https://github.com/olton/Metro-UI-CSS
 -->

    <meta name="author" content="A K M Nazmul Hasan">
       <link href="css/metro-all.css?ver=@@b-version" rel="stylesheet">
    <link href="css/start.css" rel="stylesheet">

    <title>ThirdEye : A smart home monitoring system</title>
</head>
<body class="bg-dark fg-white h-vh-100 m4-cloak">

    <div class="container-fluid start-screen h-100">
        
        <div class="tiles-area clear">
            <div class="tiles-grid tiles-group size-2 fg-white">
		
                <div data-role="tile" class="bg-indigo fg-white">
                   <img src="images/icons8-humidity-100.png" class="icon">
                    <span class="branding-bar">Humidity</span>
                    <span class="badge-bottom bg-red"><?=$row['humidity']?> %</span>
                </div>
				
                <div data-role="tile" class="bg-green fg-white" >
				<img src="images/icons8-temperature-inside-100.png" class='icon'> 
				 <span class='badge-bottom bg-red'>
				 <?=$celsiusValue?>°C / <?=$farenhiteValue?>°F</span>                   
                    <span class="branding-bar">Temp.</span>
                </div>
                
                	<div data-role="tile" class="bg-amber fg-white">
			<?php if($row['light']=='ON'){ ?>
                    <img src="images/icons8-light-on-100.png" class="icon blink">
			<?php } else { ?>
			 <img src="images/icons8-light-off-100.png" class="icon">
			<?php }?>
                    <span class="branding-bar">Light</span>
                    <span class="badge-bottom bg-red"><?=$row['light']?></span>
               </div>
				<div data-role="tile" class="bg-darkPink fg-white">
				    
				    	<?php if($row['motion']=='DETECTED'){ ?>
                    <img src="images/icons8-motion-detector-100.png" class="icon blink">
				<?php } else { ?>
				<img src="images/icons8-motion-detector-100.png" class="icon">
				<?php } ?>
                    
                     <span class='badge-bottom bg-red'>
				 <?=$row['motion']?></span>    
                    <span class="branding-bar">Motion</span>
                </div>
                <div data-role="tile" class="bg-darkRed" >
				<?php if($row['flame']=='ON'){ ?>
                    <img src="images/icons8-matches-100.png" class="icon blink">
				<?php } else { ?>
				<img src="images/icons8-no-fire-100.png" class="icon">
				<?php } ?>
                    <span class="branding-bar">Fire</span>
					<span class="badge-bottom bg-red"><?=$row['flame']?></span>
                </div>
                <div data-role="tile" class="bg-yellow fg-black" >
				<?php if($row['alarm']=='ON'){ ?>
                    <img src="images/icons8-fire-alarm-filled-100.png" class="icon blink">
				<?php } else { ?>
				<img src="images/icons8-alarm-off-filled-100.png" class="icon">
				<?php } ?>
                    <span class="branding-bar">Alarm</span>
					<span class="badge-bottom bg-red"><?=$row['alarm']?></span>
                </div>
            </div>

            
        </div>
		
    </div>


    <script src="js/jquery-3.3.1.min.js"></script>
    <script src="js/metro.js"></script>
    <script src="js/start.js"></script>
	<script>
	
function blink(selector){
$(selector).fadeOut('slow', function(){
    $(this).fadeIn('slow', function(){
        blink(this);
    });
});
}
    
blink('.blink');
</script>

</body>
</html>