<?php
header("Content-type: image/jpeg");

$replay = new Replay($_SERVER['DOCUMENT_ROOT'].'/test.SC2Replay');
$image = imagecreatefromstring($replay->getImageBuffer());
imagejpeg($image);
imagedestroy($image);
?>