#include "control_wifi.h"



int  command_System(int argcount,const char* args[],const char* binary_name,char* returndata)
{
        char myoutput_array[1000];
	int i,ret;
	FILE *fp;
        char path[1035];	
	
	sprintf(myoutput_array, "%s", binary_name);
        for(i = 0; i < argcount; ++i)
        {
                strcat(myoutput_array, " ");
                strcat(myoutput_array, args[i]);
        }

	if(returndata==NULL)
	{
		 ret=system(myoutput_array);
	}
	else
	{
        	/* Open the command for reading. */
        	fp = popen(myoutput_array, "r");
        	if (fp == NULL)
       		{
                	printf("Failed to run command\n" );
                	exit(1);
       		 }

        	/* Read the output a line at a time - output it. */
        	while (fgets(path, sizeof(path), fp) != NULL)
        	{
                	printf("%s", path);
			strcat(returndata, path);
        	}

        	/* close */
        	pclose(fp);
	}
        return ret;
}

int  turn_On_Wifi(void)
{	
	int  ret;
	const char* args[] = {WIFI_DRIVER_MODULE_PATH};

	ret=command_System(1,args,"insmod",NULL);
	
	return ret;
}

int  turn_Off_Wifi(void)
{
        int  ret;
        const char* args[] = {WIFI_DRIVER_MODULE_PATH};

        ret=command_System(1,args,"rmmod",NULL);
        return ret;

}

int search_Wifi_Spot(char * wifispot)
{
     
	int  ret;
	
	const char* args[30] = {"wlan0","up"};
		
	ret=command_System(2,args,"ifconfig",NULL);

	args[0] = "wlan0" ;
	args[1] = "scan" ;
	args[2] = "|grep";
	args[3] = "-e SSID -e signal" ;
	args[4] = "-e WPA  -e WEP" ;
	args[5] = "-e Group  -e Pairwise -e Authentication ";
	

        ret=command_System(6,args,"iw",wifispot);

        return ret;
}


#ifdef ANDROID
  //andoid

int connect_AP_Open(const char*ssid)
{
      	int  ret;
        const char* args[] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};

        printf("---wpa_supplicant---\r\n");
        ret=command_System(6,args,"wpa_supplicant",NULL);

        args[0]="-p";
        args[1]= CONTROL_IFACE_PATH;
        args[2]="add_network";
        args[3]= "2";

        printf("---wpa_cli_add_network---\r\n");
        ret=command_System(4,args,"wpa_cli",NULL);

      	args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        args[2]="set_network";
        args[3]="2";
        args[4]="ssid";
        args[5]=ssid;

        printf("--ssid=%s\r\n",ssid);

        printf("---wpa_cli_ssid---\r\n");
        ret=command_System(6,args,"wpa_cli",NULL);

       	args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        args[2]="set_network";
        args[3]="2";
        args[4]="key_mgmt";
        args[5]="NONE";
        
         printf("---wpa_cli_key_mgmt--NONE---\r\n");
        ret=command_System(6,args,"wpa_cli",NULL);


	return ret;
}

 
int connect_AP(const char* ssid,const char* psk)
{
	int  ret;
	const char* args[] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};

	printf("---wpa_supplicant---\r\n");
        ret=command_System(6,args,"wpa_supplicant",NULL);
	
        args[0]="-p";
	args[1]= CONTROL_IFACE_PATH;
	args[2]="add_network";
	args[3]= "2";

	printf("---wpa_cli_add_network---\r\n");
        ret=command_System(4,args,"wpa_cli",NULL);
	
    	//sprintf(ssid_wpa, "%s", "\"");
        //sprintf(ssid_wpa, "%s", "\'");
	//strcat(ssid_wpa,ssid);
	//strcat(ssid_wpa,"\'");
       	//strcat(ssid_wpa,"\"");

	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	args[2]="set_network";
	args[3]="2";
	args[4]="ssid";
	args[5]=ssid;
	
	printf("--ssid=%s\r\n",ssid);

        printf("---wpa_cli_ssid---\r\n");
        ret=command_System(6,args,"wpa_cli",NULL);


    	args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        args[2]="set_network";
        args[3]="2";
        args[4]="key_mgmt";
        args[5]="WPA-PSK";

        printf("---wpa_cli_-key_mgmt WPA-PSK--\r\n");
        ret=command_System(6,args,"wpa_cli",NULL);

      	args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        args[2]="set_network";
        args[3]="2";
        args[4]="proto";
        args[5]="WPA";

        printf("---wpa_cli_ssid	 proto WPA---\r\n");
        ret=command_System(6,args,"wpa_cli",NULL);

      	args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        args[2]="set_network";
        args[3]="2";
        args[4]="pairwise";
        args[5]="TKIP";

        printf("---wpa_cli_pairwise TKIP---\r\n");
        ret=command_System(6,args,"wpa_cli",NULL);



      	args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        args[2]="set_network";
        args[3]="2";
        args[4]="group";
        args[5]="TKIP";

        printf("---wpa_cli_group TKIP---\r\n");
        ret=command_System(6,args,"wpa_cli",NULL);

	//sprintf(psk_wpa, "%s", "\"");
        //sprintf(psk_wpa, "%s", "\'");
        //strcat(psk_wpa,psk);     
        //strcat(psk_wpa,"\'");
      	//sprintf(psk_wpa, "%s", "\"");

        args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	args[2]="set_network";
	args[3]="2";
	args[4]="psk";
	args[5]=psk;

	printf("----psk=%s=----\r\n",psk);

       printf("---wpa_cli_psk---\r\n");
       ret=command_System(6,args,"wpa_cli",NULL);
  	/*
   	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	args[2]="select_network";
	args[3]="2";

        printf("---wpa_cli_select_network---\r\n");
       ret=command_System(4,args,"wpa_cli",NULL);
	*/
	
   	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	args[2]="enable_network";
	args[3]="2";

        printf("---wpa_cli_enable_network---\r\n");
       ret=command_System(4,args,"wpa_cli",NULL);

	args[0]="wlan0";

        printf("---wpa_cli_DHCP_TOOL---\r\n");
	ret=command_System(1,args,DHCP_TOOL,NULL);

	//system("netcfg");
	
	return ret;
}




#else 

//linux  WPA/WPA2-Personal 

int connect_AP(const char* ssid,const char* psk)
{
        const char* args[30] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};
	char ssid_wpa[100];
	

        ret=command_System(6,args,"wpa_supplicant",NULL);
        
        args[]={"-iwlan0","add_network","0"};

        ret=command_System(3,args,"wpa_cli",NULL);

        sprintf(ssid_wpa, "%s", "\"\'");

	strcat(ssid_wpa,ssid);

	strcat(ssid_wpa,"\'\"");

        args[]={"-iwlan0","0","ssid",ssid_wpa};

        ret=command_System(4,args,"wpa_cli",NULL);

       args[]={"-iwlan0","0","psk",psk};

       ret=command_System(4,args,"wpa_cli",NULL);

   	args[]={"-iwlan0","select_network","0"};

       ret=command_System(3,args,"wpa_cli",NULL);

   	args[]={"-iwlan0","enable_network","0"};

       ret=command_System(3,args,"wpa_cli",NULL);

	args[]={"wlan0"};

	ret=command_System(1,args,DHCP_TOOL);
	
}

#endif


int disconnect_AP(void)
{
	int ret;	
	const char* args[30] = {"-ef | grep wpa_supplicant | awk '{print $2}' | xargs kill -9"};
	
	ret=command_System(1,args,"ps",NULL);

	args[0]="-ef | grep  wpa_cli | awk '{print $2}' | xargs kill -9";	

    	ret=command_System(1,args,"ps",NULL);

        args[0]="-ef | grep ";
	args[1]= DHCP_TOOL;
	args[2]="| awk '{print $2}' | xargs kill -9"; 

	ret=command_System(3,args,"ps",NULL);
	
	return ret;
}

int clear_AP_History(void)
{
	int ret;	
	const char* args[] = {SUPP_CONFIG_FILE};
	
	ret=command_System(1,args,"rm -rf",NULL);
	
	return ret;
}


