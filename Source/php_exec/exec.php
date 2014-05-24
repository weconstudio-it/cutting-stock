<?php

$d = array(
	10=>3,
	20=>2,
	30=>1
);
$aParam = array("w"=>50,"m"=>count($d), "d"=>$d);

//echo "<pre>"; var_dump($aParam);

$sOut = "";
foreach ($aParam as $key=>$val){
	switch ($key){
		case "w":
			$sOut .= "$val\n";
			break;
		case "m":
			$sOut .= "$val\n";
			break;
		case "d":
			$d = $val;
			foreach ($d as $width=>$nPezzi){
				$sOut .= "$width $nPezzi\n";
			}
			break;
	}
}

file_put_contents("data/input.dat", $sOut);

$result = shell_exec("../cutting-stock -a -s heuristic -b best-local-bound data/input.dat");

$aResult = explode("\n", $result);

$jsonOut = array("R"=>array(), "T"=>array());
$nBarra = 1;
foreach ($aResult as $row){
	$aRow = explode("|", $row);
	$skip=false;
	foreach ($aRow as $elem){
		if($aRow[0]=="R"){
			$jIndice = "R";
		}elseif ($aRow[0]=="T"){
			$jIndice = "T";
		}else{
			$skip=true;
		}
		if(!$skip){
			$aElem = explode(":", $elem);
			if(count($aElem)==2){
				if(!isset($jsonOut[$jIndice][$nBarra])){
					$jsonOut[$jIndice][$nBarra] = array();
				}
				$jsonOut[$jIndice][$nBarra][]=array($aElem[0]=>$aElem[1]);
			}
		}
	}
	$nBarra ++;
}





header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Origin: *");


$response = json_encode($jsonOut);

echo "{\"response\":$response}";