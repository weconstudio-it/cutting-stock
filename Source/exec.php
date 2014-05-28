<?php
function fdebug($var){
	$ret="\n----------LOGGER.PHP-----------\n".date("Y-m-d H:i:s")."\n";
	ob_start();
	var_dump($var);
	$ret .= ob_get_clean();
	$ret .= "\n";
	file_put_contents("/tmp/logger.log", $ret,FILE_APPEND);
}
fdebug($_REQUEST);


$deviceId = $_REQUEST['deviceId'];
$stockLength = $_REQUEST['stockLength'];

$d = array();
$cuts = $_REQUEST['cuts'];
for($i=0;$i<count($cuts);$i++){
	$cut = explode(":", $cuts[$i]);
	$d[$cut[0]] = $cut[1];
}

//$d = array_reverse(ksort($d),true);

$aParam = array("w"=>$stockLength,"m"=>count($d), "d"=>$d);

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

//$result = shell_exec("./cutting-stock -a -s heuristic -b best-local-bound data/input.dat");
$result = shell_exec("./cutting-stock -a -s exact -b best-local-bound data/input.dat");


//fdebug($sOut);
//fdebug($result);

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

fdebug($jsonOut);
$response = json_encode($jsonOut);

echo "{\"response\":$response}";