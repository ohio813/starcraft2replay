<?php
$classes = get_declared_classes();
//sort($classes);
//print_r($classes);

//MPQArchive
echo "=== MPQArchive ===\n";
$mpq = new MPQArchive();
$mpq->load($_SERVER['DOCUMENT_ROOT'].'/test.SC2Replay');
var_dump($mpq);

//MPQFile
echo "\n=== MPQFile ===\n";
$file = $mpq->getFile('replay.info');
var_dump($file);
var_dump($file->getArchive());
var_dump($file->getFileSize());
var_dump($file->getFileName());
//var_dump($file->getFileContent());

//Replay
echo "\n=== Replay ===\n";
$replay = new Replay($_SERVER['DOCUMENT_ROOT'].'/test.SC2Replay');
//$replay->load($_SERVER['DOCUMENT_ROOT'].'/test.SC2Replay');
var_dump($replay);
var_dump($replay->isValid());
var_dump($replay->getInfo());
var_dump($replay->getGameEvents());
var_dump($replay->getMessageEvents());
var_dump($replay->getSyncEvents());
var_dump($replay->getFilename());
//var_dump($replay->getImageBuffer());
var_dump($replay->getImageSize());
//var_dump($replay->exportImage($_SERVER['DOCUMENT_ROOT'].'/thumb.jpg'));

//PlayerDisplay
echo "\n=== PlayerDisplay ===\n";
var_dump(new PlayerDisplay("ZetaTwo","Zerg","255,128,128,128"));

//Info 
echo "\n=== Info ===\n";
$info = $replay->getInfo();
var_dump($info);
var_dump(Info::SLOW);
var_dump(Info::SLOWER);
var_dump(Info::NORMAL);
var_dump(Info::FAST);
var_dump(Info::FASTER);
var_dump($info->getPlayerNames());
var_dump($info->getNumberOfPlayers());
var_dump($info->getNumberOfSlots());
var_dump($info->getMapFilename());
var_dump($info->getMapName());
var_dump($info->getSpeed());
var_dump($info->getSpeed() == Info::FASTER);
var_dump($info->getAllianceLocked());
var_dump($info->getNumberOfPlayerDisplays());
//var_dump($info->getPlayerDisplays());
var_dump($info->getBufferSize());
//var_dump($info->getBuffer());
//var_dump($info->exportDump($_SERVER['DOCUMENT_ROOT'].'/info_dump.txt'));

//GameEvents 
echo "\n=== GameEvents ===\n";
$gameevents = $replay->getGameEvents();
var_dump($gameevents);

//MessageEvents 
echo "\n=== MessageEvents ===\n";
$messageevents = $replay->getMessageEvents();
var_dump($messageevents);

//SyncEvents 
echo "\n=== SyncEvents ===\n";
$sncevents = $replay->getSyncEvents();
var_dump($sncevents);
?>