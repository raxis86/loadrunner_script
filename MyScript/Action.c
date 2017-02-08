//for temp values
char temp[1000];
char itmp[10];
//****************

//for url handling
char host_car[] = "http://wiley.youplace.net";
char* host;
char* cudr;
char cdr[100];
//*******************************************

//for elements handling
char* html;
char res[100];
char name[100];

int i=0, j=0, k=0, p=0, maxlength=0;
int index=0;
//*********************

//for script progress
int isSuccess=0;
int isError=0;
//*******************

Action()
{
	//for elements parsing (by default too small for form-groups)
	web_set_max_html_param_len("8192");

	//Block of login
	
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
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_think_time(5);
	
	//param for saving redirect-address to next page
	web_reg_save_param_ex(
		"ParamName=Redirect",
		"LB=[\"redirect\",\"",
		"RB=\",false]",
		"NotFound=warning",
		SEARCH_FILTERS,
		"Scope=BODY",
		LAST);

	//submit login form (Username - from csv file, Password - custom param)
	web_submit_data("quiz_login",
		"Action=http://wiley.youplace.net/quiz",
		"Method=POST",
		"RecContentType=application/json",
		"Referer=http://wiley.youplace.net/quiz",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=name", "Value={Username}", ENDITEM,
		"Name=password", "Value={Password}", ENDITEM,
		"Name=__timestamp", "Value={__timestamp}", ENDITEM,
		"Name=__secret", "Value={__secret}", ENDITEM,
		EXTRARES,
		"URL=/img/system/ajax-loader.gif", ENDITEM,
		LAST);
	
	
	//form url from Redirect and host parameters
	host=lr_eval_string(host_car);
	cudr=lr_eval_string("{Redirect}");		
	k=0;
	memset(cdr,0,100);
	for(i=0;i<strlen(cudr);i++){
		if(cudr[i]!=92){				//92 - backslash symbol. Need to convert (example:\/quiz\/question\/14) 
			cdr[k]=cudr[i];				//to (example:/quiz/question/14)
			k++;						//
		}								//
	}									//and
	strcat(host,cdr);					//
	lr_save_string(host,"Host");		//form http://wiley.youplace.net/quiz/question/14
	//********************************************
	
	
	//run loop for handling pages (quiz all time changes!)
	do { 

	/*Correlation comment - Do not change!  Original value='1486411459' Name ='__timestamp_1' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=__timestamp_1",
		"RegExp=name=\"__timestamp\"\\ value=\"(.*?)\"><input\\ type",
		"NotFound=warning",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		LAST);

	/*Correlation comment - Do not change!  Original value='01c89adbc44d7e392c69fd27bdb431d1538fd5ffe13daa09a111121d0b68915c' Name ='__secret_1' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=__secret_1",
		"RegExp=name=\"__secret\"\\ value=\"(.*?)\"><hr",
		"NotFound=warning",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		LAST);
	
	//registering parameters for containing text fields
	web_reg_save_param_regexp(
		"ParamName=Texts",
		"RegExp=<input type=\"text\" class=\"form-control\" name=\"(.*?)\">",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		LAST);
	
	//registering parameters for containing textareas fields	
	web_reg_save_param_regexp(
		"ParamName=Textareas",
		"RegExp=<textarea name=\"(.*?)\"",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		LAST);	
	
	//registering parameters for containing select group-forms
	web_reg_save_param_ex(
		"ParamName=Selectgroups",
		"LB=<div class=\"form-group\"><select",
		"RB=</select></div>",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		"Scope=BODY",
		LAST);
	
	//registering parameters for containing radio group-forms
	web_reg_save_param_ex(
		"ParamName=Radiogroups",
		"LB=<div class=\"form-group\"><div class=\"radio\">",
		"RB=</div></div>",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		"Scope=BODY",
		LAST);
		
	//registering parameters for containing checkbox group-forms
	web_reg_save_param_ex(
		"ParamName=Checkboxgroups",
		"LB=<div class=\"form-group\"><div class=\"checkbox\">",
		"RB=</div></div>",
		"NotFound=warning",
		"Ordinal=all",
		SEARCH_FILTERS,
		"Scope=BODY",
		LAST);
		
	//Registering text for complete quiz
	web_reg_find("Search=All",
		"SaveCount=Success_Count",
		"Text=Congratulations, you've answered all the questions correctly!",
		LAST);
	
	lr_think_time(10);
		
	//go to (next) quiz page
	web_url("1",
		"URL={Host}",
		"RecContentType=text/html",
		"Snapshot=t3.inf",
		"Mode=HTML",
		LAST);	
	
	isSuccess=atoi(lr_eval_string("{Success_Count}"));
	
	//if it is final page, then break loop
	if(isSuccess>0){
		lr_output_message("Sucess!");
		break;
	}
	
	
	//Create string variable for Body save
	lr_save_string(lr_eval_string("__timestamp={__timestamp_1}"), "Body");
	lr_save_string(lr_eval_string("{Body}&__secret={__secret_1}"), "Body");
	
	
	//Check on checkboxes and add right parameters to Body for post request (if exists)
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
	
	
	//check on radiogroups and add right parameters to Body for post request (if exists)
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
	
	//check on selectgroups and add right parameters to Body for post request (if exists)
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
		lr_save_string("short+text", "TextValue");
		
		lr_save_string(lr_eval_string("{Body}&{TextName}={TextValue}"), "Body");
		
	}	
	
	//-----------------------------------------------------
	
	//Check on textareas elements
	for(i=1; i<=lr_paramarr_len("Textareas"); i++) {

		lr_save_string(lr_paramarr_idx("Textareas", i), "TextareaName");
		lr_save_string("large+text", "TextareaValue");
		
		lr_save_string(lr_eval_string("{Body}&{TextareaName}={TextareaValue}"), "Body");
		
	}	


	lr_think_time(10);
	
	//param for saving redirect-address to next page
	web_reg_save_param_ex(
		"ParamName=Redirect",
		"LB=[\"redirect\",\"",
		"RB=\",false]",
		"NotFound=warning",
		SEARCH_FILTERS,
		"Scope=BODY",
		LAST);

	//param for error on page
	web_reg_find("Search=All",
		"SaveCount=Error_Count",
		"Text=Some field has wrong value",
		LAST);
	
	//Post form whith checked params in Body
	web_custom_request("web_custom_request",
		"URL={Host}",
		"Method=POST",
		"Resource=0", 
		"RecContentType=text/html", 
		"Snapshot=t4.inf",
		"Mode=HTTP", 
		"Body={Body}",
		LAST);
	
	
	isError=atoi(lr_eval_string("{Error_Count}"));
	
	if(isError>0){
		lr_output_message("Error!");
		isError=0;
	}
	else
	{
		host=lr_eval_string(host_car);
		cudr=lr_eval_string("{Redirect}");		
		k=0;
		memset(cdr,0,100);
		for(i=0;i<strlen(cudr);i++){
			if(cudr[i]!=92){
				cdr[k]=cudr[i];
				k++;
			}
		}
		strcat(host,cdr);
		lr_save_string(host,"Host");
	}
		
	
	}while(isSuccess==0);

	return 0;
}