<?php
	function GetFromHTML($url)
	{
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_HEADER, 0);
		curl_setopt($ch, CURLOPT_TIMEOUT, 10);
		$output=curl_exec($ch);
		curl_close($ch);
		return $output;
	}
	$array=json_decode(strip_tags(GetFromHTML("https://api.obfs.dev/api/pixiv/member_illust?id=".$argv[1])),true);
	for ($i=0;$i<count($array["illusts"]);$i++) 
	{
		$url=$array["illusts"]["meta_single_page"]["original_image_url"];
		str_replace("https://i.pximg.net/","https://proxy-jp1.pixivel.moe/c/600x1200_90_webp/",$url);
		shell_exec("wget ".$url);
	}
?>