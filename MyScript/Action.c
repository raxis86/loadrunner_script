int length=0;
int lengthPrev=0;
char temp[1000];
char itmp[10];

//char html[1000];

char* html;
char res[100];
char name[100];

int i=0, j=0, k=0, p=0, maxlength=0;
int index=0;
int isSuccess=0;

Action()
{

/*Correlation comment - Do not change!  Original value='1486411436' Name ='__timestamp' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=__timestamp",
		"RegExp=name=\"__timestamp\"\\ value=\"(.*?)\"><input\\ type",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		"RequestUrl=*/quiz*",
		LAST);

/*Correlation comment - Do not change!  Original value='62cb776996ad642db0e447afe77c10d7cb97f7d4a78abd040c464093233dffe8' Name ='__secret' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=__secret",
		"RegExp=name=\"__secret\"\\ value=\"(.*?)\"></form",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		"RequestUrl=*/quiz*",
		LAST);

	web_url("quiz", 
		"URL=http://wiley.youplace.net/quiz", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t451.inf", 
		"Mode=HTML", 
		LAST);

	/*web_set_sockets_option("SSL_VERSION", "2&3");*/

	lr_think_time(10);

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
		"Name=__timestamp", "Value={__timestamp}", ENDITEM,
		"Name=__secret", "Value={__secret}", ENDITEM,
		EXTRARES,
		"URL=/img/system/ajax-loader.gif", ENDITEM,
		LAST);
	
	
	
	
	
	

/*Correlation comment - Do not change!  Original value='1486411459' Name ='__timestamp_1' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=__timestamp_1",
		"RegExp=name=\"__timestamp\"\\ value=\"(.*?)\"><input\\ type",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		LAST);

/*Correlation comment - Do not change!  Original value='01c89adbc44d7e392c69fd27bdb431d1538fd5ffe13daa09a111121d0b68915c' Name ='__secret_1' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=__secret_1",
		"RegExp=name=\"__secret\"\\ value=\"(.*?)\"><hr",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		LAST);
		

	web_reg_save_param_ex(
		"ParamName=Texts",
		"LB=<input type=\"text\" class=\"form-control\" name=\"",
		"RB=\">",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		LAST);

	web_reg_save_param_ex(
		"ParamName=Textareas",
		"LB=<textarea name=\"",
		"RB=\" class=\"form-control\"",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		LAST);
		

	web_reg_save_param_ex(
		"ParamName=Selectgroups",
		"LB=<div class=\"form-group\"><select",
		"RB=</select></div>",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		LAST);

	web_reg_save_param_ex(
		"ParamName=Radiogroups",
		"LB=<div class=\"form-group\"><div class=\"radio\">",
		"RB=</div></div>",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		LAST);
		

	web_reg_save_param_ex(
		"ParamName=Checkboxgroups",
		"LB=<div class=\"form-group\"><div class=\"checkbox\">",
		"RB=</div></div>",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		LAST);

		
		
	web_url("1", 
		"URL=http://wiley.youplace.net/quiz/question/1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://wiley.youplace.net/quiz", 
		"Snapshot=t454.inf", 
		"Mode=HTML", 
		LAST);	
		
	/*lr_output_message(lr_eval_string("{Checkboxes_count}"));*/
	
	
	//Create string variable for Body save
	lr_save_string(lr_eval_string("__timestamp={__timestamp_1}"), "Body");
	lr_save_string(lr_eval_string("{Body}&__secret={__secret_1}"), "Body");
	
	
	
	//Check on checkboxes
	for(i=1; i<=lr_paramarr_len("Checkboxgroups"); i++) {
		
		//fill temp variable
		sprintf(temp,"{Checkboxgroups_%d}",i );

		html=lr_eval_string(temp);
		index=0; maxlength=0;
		
		for(p=0;p<strlen(html);p++){
				
			if((html[p]=='n')&&(html[p+1]=='a')&&(html[p+2]=='m')&&(html[p+3]=='e')&&(html[p+4]=='=')){
				k=0;
				memset(res,0,100);
				for(j=p+6;j<strlen(html);j++){
					if(html[j]=='"'){
						break;
					}
					res[k]=html[j];
					k++;
				}
				index++;
			
				if(k>maxlength){
					maxlength=k;
					lr_save_string(res, "CheckboxName");
					itoa(index,itmp,10);
					lr_save_string(itmp, "CheckboxValue");
				}
		
				lr_output_message(res);
			}
	
		}
		
		lr_save_string(lr_eval_string("{Body}&{CheckboxName}={CheckboxValue}"), "Body");
	}	
	
	
	//check on radiogroups
	for(i=1; i<=lr_paramarr_len("Radiogroups"); i++) {
		//fill temp variable
		sprintf(temp,"{Radiogroups_%d}",i );

		html=lr_eval_string(temp);
		
		memset(name,0,100);
		
		for(p=0;p<strlen(html);p++){
	
			if((html[p]=='n')&&(html[p+1]=='a')&&(html[p+2]=='m')&&(html[p+3]=='e')&&(html[p+4]=='=')&&(strlen(name)==0)){
				k=0;
				for(j=p+6;j<strlen(html);j++){
					if(html[j]=='"'){
						break;
					}
					name[k]=html[j];
					k++;
				}
				lr_save_string(name, "RadioName");
			}
		
			if((html[p]=='v')&&(html[p+1]=='a')&&(html[p+2]=='l')&&(html[p+3]=='u')&&(html[p+4]=='e')&&(html[p+5]=='=')){
				k=0;
				memset(res,0,100);
				for(j=p+7;j<strlen(html);j++){
					if(html[j]=='"'){
						break;
					}
					res[k]=html[j];
					k++;
				}
				if(k==1){
					lr_save_string(res, "RadioValue");
				}
			}
		}
		
		lr_save_string(lr_eval_string("{Body}&{RadioName}={RadioValue}"), "Body");
	}
	
	//check on selectgroups
	for(i=1; i<=lr_paramarr_len("Selectgroups"); i++) {
		//fill temp variable
		sprintf(temp,"{Selectgroups_%d}",i );

		html=lr_eval_string(temp);
		
		memset(name,0,100);
		
		for(p=0;p<strlen(html);p++){
				
			if((html[p]=='n')&&(html[p+1]=='a')&&(html[p+2]=='m')&&(html[p+3]=='e')&&(html[p+4]=='=')&&(strlen(name)==0)){
				k=0;
				for(j=p+6;j<strlen(html);j++){
					if(html[j]=='"'){
						break;
					}
					name[k]=html[j];
					k++;
				}
				lr_save_string(name, "SelectName");
			}
		
			if((html[p]=='v')&&(html[p+1]=='a')&&(html[p+2]=='l')&&(html[p+3]=='u')&&(html[p+4]=='e')&&(html[p+5]=='=')){
				k=0;
				memset(res,0,100);
				for(j=p+7;j<strlen(html);j++){
					if(html[j]=='"'){
						break;
					}
					res[k]=html[j];
					k++;
				}
				if(k==1){
					lr_save_string(res, "SelectValue");
				}
			}
		}
		
		lr_save_string(lr_eval_string("{Body}&{SelectName}={SelectValue}"), "Body");
	}
	
	//-----------------------------------------------------
	
	//Check on text elements
	for(i=1; i<=lr_paramarr_len("Texts"); i++) {

		lr_save_string(lr_paramarr_idx("Texts", i), "TextName");
		lr_save_string("short text", "TextValue");
		
		lr_save_string(lr_eval_string("{Body}&{TextName}={TextValue}"), "Body");
		
	}	
	
	//-----------------------------------------------------
	
	//Check on textareas elements
	for(i=1; i<=lr_paramarr_len("Textareas"); i++) {

		lr_save_string(lr_paramarr_idx("Textareas", i), "TextareaName");
		lr_save_string("large text", "TextareaValue");
		
		lr_save_string(lr_eval_string("{Body}&{TextareaName}={TextareaValue}"), "Body");
		
	}	


	
	

	lr_think_time(10);
	

	web_custom_request("web_custom_request",
		"URL=http://wiley.youplace.net/quiz/question/1",
		"Method=POST",
		"Resource=0", 
		"RecContentType=text/html", 
		"Snapshot=t456.inf", 
		"Mode=HTTP", 
		"Body={Body}",
		LAST);

	
	//Регистрация текста для завершения теста
	

	web_reg_find("Search=All",
		"SaveCount=SuccessCount",
		"Text=Congratulations, you've answered all the questions correctly!",
		LAST);

	
	web_url("2", 
		"URL=http://wiley.youplace.net/quiz/question/2", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://wiley.youplace.net/quiz/question/1", 
		"Snapshot=t457.inf", 
		"Mode=HTML", 
		LAST);
	
	isSuccess=atoi(lr_eval_string("{SuccessCount}"));
	
	if(isSuccess!=0){
		lr_output_message("Sucess!");
		//break;
	}

	return 0;
}