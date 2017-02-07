Action()
{

	web_url("quiz", 
		"URL=http://wiley.youplace.net/quiz", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t451.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=https://translate.googleapis.com/translate_a/l?client=chrome&hl=ru&key=AIzaSyBOti4mM-6x9WDnZIjIeyEU21OpBXqWBgw&alpha=1", "Referer=", ENDITEM, 
		"Url=/fonts/cJZKeOuBrn4kERxqtaUH3VtXRa8TVwTICgirnJhmVJw.woff2", "Referer=http://wiley.youplace.net/css/google.css?v=1", ENDITEM, 
		"Url=/fonts/glyphicons-halflings-regular.woff2", "Referer=http://wiley.youplace.net/css/bootstrap.min.css", ENDITEM, 
		LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_url("seed", 
		"URL=https://clients4.google.com/chrome-variations/seed?osname=win", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t452.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=http://wiley.youplace.net/fonts/DXI1ORHCpsQm3Vp6mXoaTegdm0LZdjqr5-oayXSOefg.woff2", "Referer=http://wiley.youplace.net/css/google.css?v=1", ENDITEM, 
		"Url=http://wiley.youplace.net/img/css/striped_lens.png", "Referer=http://wiley.youplace.net/css/app.css?v=1.0.1", ENDITEM, 
		"Url=https://ssl.gstatic.com/safebrowsing/csd/client_model_v5_ext_variation_0.pb", "Referer=", ENDITEM, 
		"Url=https://ssl.gstatic.com/safebrowsing/csd/client_model_v5_variation_0.pb", "Referer=", ENDITEM, 
		LAST);

	lr_think_time(4);

	web_submit_data("quiz_2", 
		"Action=http://wiley.youplace.net/quiz", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://wiley.youplace.net/quiz", 
		"Snapshot=t453.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=name", "Value=user1", ENDITEM, 
		"Name=password", "Value=test", ENDITEM, 
		"Name=__timestamp", "Value=1486411436", ENDITEM, 
		"Name=__secret", "Value=62cb776996ad642db0e447afe77c10d7cb97f7d4a78abd040c464093233dffe8", ENDITEM, 
		EXTRARES, 
		"Url=/img/system/ajax-loader.gif", ENDITEM, 
		LAST);

	web_url("1", 
		"URL=http://wiley.youplace.net/quiz/question/1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://wiley.youplace.net/quiz", 
		"Snapshot=t454.inf", 
		"Mode=HTML", 
		LAST);

	lr_think_time(5);

	web_custom_request("query", 
		"URL=https://clients1.google.com/tbproxy/af/query?client=Google%20Chrome", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/proto", 
		"Referer=", 
		"Snapshot=t455.inf", 
		"Mode=HTML", 
		"EncType=text/proto", 
		"BodyBinary=\n\\x176.1.1715.1442/en (GGLL)\\x13\\x19\\xC6\\x1B1\\xED\\xB0W\\xCEn#-\\xF7:\\x14t$#-\\x875\"\\x16$#-\\x85\\x06\\x0C!$\\x14", 
		LAST);

	lr_think_time(14);

	web_submit_data("1_2", 
		"Action=http://wiley.youplace.net/quiz/question/1", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://wiley.youplace.net/quiz/question/1", 
		"Snapshot=t456.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=8k7cs1emixl", "Value=short text", ENDITEM, 
		"Name=9yn3rlde0m", "Value=3", ENDITEM, 
		"Name=czk33pbowogy22h0n91x", "Value=short text", ENDITEM, 
		"Name=109fea2laekuinjub", "Value=1", ENDITEM, 
		"Name=__timestamp", "Value=1486411459", ENDITEM, 
		"Name=__secret", "Value=01c89adbc44d7e392c69fd27bdb431d1538fd5ffe13daa09a111121d0b68915c", ENDITEM, 
		LAST);

	web_url("2", 
		"URL=http://wiley.youplace.net/quiz/question/2", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://wiley.youplace.net/quiz/question/1", 
		"Snapshot=t457.inf", 
		"Mode=HTML", 
		LAST);

	return 0;
}