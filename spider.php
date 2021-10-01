<?php
	define("USER","LittleYang0531");
	define("REPO","Photo");
	define("MAIL","littleyang0531@outlook.com");
	define("TOKEN","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");
	function upload_github($filename, $content)
	{   
	    $url = "https://api.github.com/repos/" . USER . "/" . REPO . "/contents/" . $filename;
	    $ch = curl_init();
	    $defaultOptions=[
	        CURLOPT_URL => $url,
	        CURLOPT_FOLLOWLOCATION => true,
	        CURLOPT_RETURNTRANSFER => true,
	        CURLOPT_CUSTOMREQUEST=>"PUT",
	        CURLOPT_POSTFIELDS=>json_encode([
	            "message"=>"upload By autoPicCdn",
	            "committer"=> [
	                "name"=> USER,
	                "email"=> MAIL,
	            ],
	            "content"=> $content,
	        ]),
	        CURLOPT_HTTPHEADER => [
	            "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
	            "Accept-Language:zh-CN,en-US;q=0.7,en;q=0.3",
	            "User-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36",
	            'Authorization:token '.TOKEN,
	        ],
	    ];
	    curl_setopt_array($ch, $defaultOptions);
	    $chContents = curl_exec($ch);
	    curl_close($ch);
	    return $chContents;
	}
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
		$url=$array["illusts"][$i]["meta_single_page"]["original_image_url"];
		$url=str_replace("i.pximg.net","proxy-jp1.pixivel.moe",$url);
		shell_exec("wget ".$url." -O ".$array["illusts"][$i]["id"]."_0.jpg");
		echo upload_github($array["illusts"][$i]["id"]."_0.jpg",base64_encode(file_get_contents($array["illusts"][$i]["id"]."_0.jpg")));
	}
?>