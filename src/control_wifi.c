#include "control_wifi.h"


int  command_System(int argcount,const char* args[],const char* binary_name,char* returndata,int inputcunt,const char * inputdata[])
{
        char myoutput_array[500]={0};
	char myinput_array[500]={0};
	int i;
	FILE *fp_r;
	FILE *fp_w;
        char path[1035]={0};	

	
	sprintf(myoutput_array, "%s", binary_name);
        for(i = 0; i < argcount; ++i)
        {
	//	printf("--OOdata[%d]=%s\r\n",i,args[i]);
                strcat(myoutput_array, " ");
                strcat(myoutput_array, args[i]);
	  //      printf("--OOinput=%s\r\n",myoutput_array);
        }
	
	//iif(inputdata!=NULL)
	//{
	//	sprintf(myinput_array, "%s", inputdata[0]);
		//printf("--data[%d]=%s\r\n",0,inputdata[0]);	
     	for(i = 0; i <inputcunt; ++i)
        {
		///	printf("--data[%d]=%s\r\n",i,inputdata[i]);
		strcat(myinput_array, inputdata[i]);   			
		strcat(myinput_array, " ");
		//	printf("--input=%s\r\n",myinput_array);

        }
	//}

        /* Open the command for reading. */
	
	if(inputdata!=NULL)
	{
	 	//printf("aaaaaaaaaaaa");
		if((fp_w = popen(myoutput_array, "w")) == NULL)
        	{
                        perror("Fail to popen w\n");
                        exit(1);
        	}
	}
	else
	{
		//printf("bbbbbbbbbbbb");
		if((fp_r=popen(myoutput_array, "r")) == NULL)
        	{
                	perror("Failed to popen r\n" );
                	exit(1);
        	}

	}

        if(returndata!=NULL)
	{	
	//	printf("cccccccccc");
		/* Read the output a line at a time - output it. */
        	while (fgets(path, sizeof(path), fp_r) != NULL)
        	{
                	//printf("%s", path);
			strcat(returndata, path);
        	}
        	/* close */
        	pclose(fp_r);
	}

	if(inputdata!=NULL)
	{
		//printf("ddddddddd\r\n");	
		//printf("myinput=%s\r\n",myinput_array);
		fputs(myinput_array,fp_w);
		pclose(fp_w);
	}

	return 0;
}

int  turn_On_Wifi(void)
{	
	int  ret;
	const char* args[] = {WIFI_DRIVER_MODULE_PATH};

	ret=command_System(1,args,"insmod",NULL,0,NULL);
	
	return ret;
}

int  turn_Off_Wifi(void)
{
        int  ret;
        const char* args[] = {WIFI_DRIVER_MODULE_PATH};

        ret=command_System(1,args,"rmmod",NULL,0,NULL);
        return ret;

}

int search_Wifi_Spot(char * wifispot)
{
     
	int  ret;
	
	const char* args[30] = {"wlan0","up"};
		
	ret=command_System(2,args,"ifconfig",NULL,0,NULL);

	args[0] = "wlan0" ;
	args[1] = "scan" ;
	args[2] = "|grep";
	args[3] = "-e SSID -e signal" ;
	args[4] = "-e WPA  -e WEP" ;
	args[5] = "-e Group  -e Pairwise -e Authentication ";
	

        ret=command_System(6,args,"iw",wifispot,0,NULL);

        return ret;
}

int connect_AP(const char* ssid,const char* psk)
{
      	int  ret;

        const char* args[] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};
	const char* input[5];
	
	char recent_network[50]={0};


        printf("---wpa_supplicant---\r\n");
        ret=command_System(6,args,"wpa_supplicant",NULL,0,NULL);

	usleep(3000000);

        args[0]="-p";
        args[1]= CONTROL_IFACE_PATH;
        args[2]="add_network";


        printf("---wpa_cli_add_network---\r\n");
        ret=command_System(3,args,"wpa_cli",recent_network,0,NULL);

	printf("recent_netowrk=%s\r\n",recent_network);
//	delchar(recent_network,"Selected interface \'wlan0\'");
	
	unsigned char i=0;
	
	do
	{	
		recent_network[i]=recent_network[27+i];
		i++;
	}
	while(recent_network[27+i]!='\n');

	recent_network[i]='\0';

	printf("recent_netowrk=%s\r\n",recent_network);

	usleep(10000);

      	args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        input[0]="set_network";
        input[1]=recent_network;
        input[2]="ssid";
        input[3]=ssid;
	input[4]="\r";

        printf("--ssid=%s\r\n",ssid);


        printf("---wpa_cli_ssid---\r\n");
        ret=command_System(2,args,"wpa_cli",NULL,5,input);

	usleep(10000);

	if(psk==NULL)
	{	

       		args[0]="-p";
        	args[1]=CONTROL_IFACE_PATH;
        	input[0]="set_network";
        	input[1]=recent_network;
        	input[2]="key_mgmt";
        	input[3]="NONE";
        	input[4]="\r";

        	printf("---wpa_cli_key_mgmt--NONE---\r\n");
        	ret=command_System(2,args,"wpa_cli",NULL,5,input);
	}
	else
	{
   		args[0]="-p";
        	args[1]=CONTROL_IFACE_PATH;
        	input[0]="set_network";
        	input[1]=recent_network;
        	input[2]="psk";
        	input[3]=psk;
        	input[4]="\r";

        	printf("----psk=%s=----\r\n",psk);

        	printf("---wpa_cli_psk---\r\n");
        	ret=command_System(2,args,"wpa_cli",NULL,5,input);
       
	}

	usleep(10000);

     	args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        input[0]="select_network";
        input[1]=recent_network;
	input[2]="\r";

        printf("---wpa_cli_select_network---\r\n");
        ret=command_System(2,args,"wpa_cli",NULL,3,input);
        usleep(100000);

        args[0]="-p";
        args[1]=CONTROL_IFACE_PATH;
        input[0]="enable_network";
        input[1]=recent_network;
	input[2]="\r";

        printf("---wpa_cli_enable_network---\r\n");
       ret=command_System(2,args,"wpa_cli",NULL,3,input);

        usleep(100000);

        args[0] = DHCPCD_WLAN_PATH;

        ret=command_System(1,args,"rm -rf",NULL,0,NULL);
	

	args[0]="wlan0";

        printf("---wpa_cli_DHCP_TOOL---\r\n");
        ret=command_System(1,args,DHCP_TOOL,NULL,0,NULL);

	return ret;
}

/*
int connect_AP(const char* ssid,const char* psk)
{
	int  ret;
	const char* args[] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};
	const char* input[5];

	printf("---wpa_supplicant---\r\n");
        ret=command_System(6,args,"wpa_supplicant",NULL,0,NULL);
      	
	usleep(3000000);	
        
	args[0]="-p";
	args[1]= CONTROL_IFACE_PATH;
	input[0]="add_network";
	input[1]="\r";

	printf("---wpa_cli_add_network---\r\n");
        ret=command_System(1,args,"wpa_cli",NULL,2,input);
	
       	usleep(10000);
    	//sprintf(ssid_wpa, "%s", "\"");
        //sprintf(ssid_wpa, "%s", "\'");
	//strcat(ssid_wpa,ssid);
	//strcat(ssid_wpa,"\'");
       	//strcat(ssid_wpa,"\"");

	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	input[0]="set_network";
	input[1]="2";
	input[2]="ssid";
	input[3]=ssid;
	input[4]="\r";	

	printf("--ssid=%s\r\n",ssid);

        printf("---wpa_cli_ssid---\r\n");
        ret=command_System(2,args,"wpa_cli",NULL,5,input);
      
	usleep(10000);
	//sprintf(psk_wpa, "%s", "\"");
        //sprintf(psk_wpa, "%s", "\'");
        //strcat(psk_wpa,psk);     
        //strcat(psk_wpa,"\'");
      	//sprintf(psk_wpa, "%s", "\"");

        args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	input[0]="set_network";
	input[1]="2";
	input[2]="psk";
	input[3]=psk;
	input[4]="\r";

	printf("----psk=%s=----\r\n",psk);

	printf("---wpa_cli_psk---\r\n");
	ret=command_System(2,args,"wpa_cli",NULL,5,NULL);
  	
	usleep(10000);
   	
	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	input[0]="select_network";
	input[1]="2";
	input[2]="\r";

        printf("---wpa_cli_select_network---\r\n");
        ret=command_System(4,args,"wpa_cli",NULL,3,input);
	usleep(10000);
	
   	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	input[0]="enable_network";
	input[1]="2";
	input[2]="\r";

        printf("---wpa_cli_enable_network---\r\n");
       ret=command_System(2,args,"wpa_cli",NULL,3,input);

	usleep(10000);

	args[0]="wlan0";

        printf("---wpa_cli_DHCP_TOOL---\r\n");
	ret=command_System(1,args,DHCP_TOOL,NULL,0,NULL);

	usleep(10000);
	//system("netcfg");
	
	return ret;
}


*/


int disconnect_AP(void)
{
	int ret;	
	const char* args[30] = {"-ef | grep wpa_supplicant | awk '{print $2}' | xargs kill -9"};
	
	ret=command_System(1,args,"ps",NULL,0,NULL);

	args[0]="-ef | grep  wpa_cli | awk '{print $2}' | xargs kill -9";	

    	ret=command_System(1,args,"ps",NULL,0,NULL);

        args[0]="-ef | grep ";
	args[1]= DHCP_TOOL;
	args[2]="| awk '{print $2}' | xargs kill -9"; 

	ret=command_System(3,args,"ps",NULL,0,NULL);
	
	return ret;
}

int clear_AP_History(void)
{
	int ret;	
	const char* args[] = {SUPP_CONFIG_FILE};
	
	ret=command_System(1,args,"rm -rf",NULL,0,NULL);
	
	return ret;
}


