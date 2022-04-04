<?php

function getid($id) { $tmp=$id;

$cnt=0; while (intval($id)!=0){$id/=10;$cnt++;}

for ($i=1;$i<=3-$cnt;$i++) $tmp="0".$tmp;

return $tmp;}

for ($i=1;$i<=157;$i++) exec("wget https://mhua.zerobywrevi.com/manhua/Pa7n7m5ic/29-33/".getid($i).".jpg -O ./output/".getid($i).".jpg");

?>
