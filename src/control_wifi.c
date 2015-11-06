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
                strcat(myoutput_array, " ");
                strcat(myoutput_array, args[i]);
        }
	
     	for(i = 0; i <inputcunt; ++i)
        {
		strcat(myinput_array, inputdata[i]);   			
		strcat(myinput_array, " ");
        }

        /* Open the command for reading. */
	
	if(inputdata!=NULL)
	{
		if((fp_w = popen(myoutput_array, "w")) == NULL)
        	{
                        perror("Fail to popen w\n");
                        exit(1);
        	}
	}
	else
	{
		if((fp_r=popen(myoutput_array, "r")) == NULL)
        	{
                	perror("Failed to popen r\n" );
                	exit(1);
        	}

	}

        if(returndata!=NULL)
	{	
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
		//printf("myinput=%s\r\n",myinput_array);
		fputs(myinput_array,fp_w);
		pclose(fp_w);
	}

	return 0;
}

int  FLC_Wifi_Turn_On_Wifi(void)
{	
	int  ret;
	const char* args[] = {WIFI_DRIVER_MODULE_PATH};

	ret=command_System(1,args,"insmod",NULL,0,NULL);
	
	return ret;
}

int  FLC_Wifi_Turn_Off_Wifi(void)
{
        int  ret;
        const char* args[] = {WIFI_DRIVER_MODULE_PATH};

        ret=command_System(1,args,"rmmod",NULL,0,NULL);
        return ret;

}


void init_wifi_spot(void)
{
	int i=0;
	
	for(i=0;i<20;i++)
	{	
		memset(wifi_info[i].ssid,0,sizeof(wifi_info[i].ssid));	
		memset(wifi_info[i].signal,0,sizeof(wifi_info[i].signal));
		strcpy(wifi_info[i].security,"open");
	}

}



int FLC_Wifi_Client_Search_Wifi_Spot(void)
{
     
	int  ret;
	char wifi_spot_data[5000];	
	int i=0,j=0,k=0;
        int spot_id=0;
	

	const char* args[30] = {"wlan0","up"};

		
	ret=command_System(2,args,"ifconfig",NULL,0,NULL);

	args[0] = "wlan0" ;
	args[1] = "scan" ;
	args[2] = "|grep";
	args[3] = "-e SSID -e signal" ;
	args[4] = "-e WPA  -e WEP" ;
	args[5] = "-e Group  -e Pairwise -e Authentication ";
	args[6] = "-e Extended supported";
	

        ret=command_System(7,args,"iw",wifi_spot_data,0,NULL);

/*
	for(i=0;i<sizeof(wifi_spot_data)-20;i++)
	{
	
	if(wifi_spot_data[i]=='s')
        {
        if(wifi_spot_data[i+1]=='i')
        {
        if(wifi_spot_data[i+2]=='g')
        {
        if(wifi_spot_data[i+3]=='n')
        {
        if(wifi_spot_data[i+4]=='a')
        {
        if(wifi_spot_data[i+5]=='l')
        {
       	if(wifi_spot_data[i+6]==':')
        { 
	if(wifi_spot_data[i+7]==' ')
	{
	j=0; 
        while(wifi_spot_data[i+8]!=' ')
        {
        wifi_info[spot_id].signal[j]=wifi_spot_data[i+8];
        i++;
        j++;
        }
	i=i+8;

	}
	}
	}
	}
	}
	}
	}
	}

	if(wifi_spot_data[i]=='s')
	{
	if(wifi_spot_data[i+1]=='s')
	{
	if(wifi_spot_data[i+2]=='i')
	{
	if(wifi_spot_data[i+3]=='d')
	{
	if(wifi_spot_data[i+4]==':')
	{
	if(wifi_spot_data[i+5]==' ')
        {
	j=0;
	while(wifi_spot_data[i+6]!=' ')
	{
	wifi_info[spot_id].ssid[k]=wifi_spot_data[i+6];
	i++;
	k++;
	}
	i=i+6;
							
	}
	}		
	}
	}
	}	
	}

	if(wifi_spot_data[i]=='R')
	{
	if(wifi_spot_data[i+1]=='S')
	{
	if(wifi_spot_data[i+2]=='N')
	{
	strcpy(wifi_info[spot_id].security,"psk"); 		
	}
	}	
	}
	
	if(wifi_spot_data[i]=='E')
	{
	if(wifi_spot_data[i+1]=='x')
	{
	if(wifi_spot_data[i+2]=='t')
	{
	if(wifi_spot_data[i+3]=='e')
	{
	if(wifi_spot_data[i+4]=='n')	
	{
	if(wifi_spot_data[i+5]=='d')
	{
	if(wifi_spot_data[i+6]=='e')
	{
	if(wifi_spot_data[i+7]==' ')
	{
	if(wifi_spot_data[i+8]=='s')
	{
	if(wifi_spot_data[i+9]=='u')
	{
	spot_id++;
	i=i+9;
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	
	}

*/


        return ret;
}

int FLC_Wifi_Client_Connect_AP(const char* ssid,const char* psk)
{
      	int  ret;
	
	int fd;
	
	char buffer[1000]={0};
        
	int i=0,j=0;

       bool  store_ssid=true;	

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

	//if((fp=fopen(SUPP_CONFIG_FILE,"w"))==NULL)
	//{
	//	printf("不能打开文件\n");
	//	exit(0);
	//}

	fd=open(SUPP_CONFIG_FILE,O_RDONLY);

	read(fd,buffer,sizeof(buffer));
/*
	for(i=0;i<sizeof(buffer)-20;i++)
	{
	if(buffer[i]=='s')
	{
        if(buffer[i+1]=='s')	
	{
	if(buffer[i+2]=='i')
	{
	if(buffer[i+3]=='d')
	{
      	if(buffer[i+4]=='=')
        {	
	
	j=0;
	while(1)
	{	

	if(buffer[i+5]==ssid[j])
	{	
	store_ssid=false;
	}
	else
	{
	store_ssid=true;
	break;
	}
	i++;
	j++;

	if(ssid[j]=='"'||j>20)
	{
	
		break;	
	}

	}

	}


	}
	}			
	}
	}	

	}

	}
*/
	if(store_ssid==true)
	{

		//fd=open(SUPP_CONFIG_FILE, O_CREAT|O_WRONLY|O_APPEND);

		write(fd,"network={\n",sizeof("network={\n")-1);
       		write(fd,"	ssid=",sizeof("      ssid=")-1);
		write(fd,ssid,sizeof(ssid)-1);
		write(fd,"\n",sizeof("\n")-1);

	}
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

		if(store_ssid==true)
                {
                	write(fd,"      key_mgmt=",sizeof("      key_mgmt=")-1);
                	write(fd,"NONE",sizeof("NONE")-1);
                	write(fd,"\n",sizeof("\n")-1);

            		write(fd,"      priority=",sizeof("      priority=")-1);
               		write(fd,"1",sizeof("1")-1);
                	write(fd,"\n",sizeof("\n")-1);

                	write(fd,"}",sizeof("}")-1);
                	write(fd,"\n",sizeof("\n")-1);
                }

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
       	
		if(store_ssid==true)
        	{
	       
			write(fd,"      psk=",sizeof("      psk=")-1);
        		write(fd,psk,sizeof(psk)-1);
			write(fd,"\n",sizeof("\n")-1);

            		write(fd,"      key_mgmt=",sizeof("      key_mgmt=")-1);
                	write(fd,"psk",sizeof(psk)-1);
                	write(fd,"\n",sizeof("\n")-1);

			write(fd,"      priority=",sizeof("      priority=")-1);
                	write(fd,"1",sizeof("1")-1);
                	write(fd,"\n",sizeof("\n")-1);

			write(fd,"}",sizeof("}")-1);
                	write(fd,"\n",sizeof("\n")-1);
		}
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



int FLC_Wifi_Client_Disconnect_AP(void)
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

int FLC_Wifi_Client_Clear_AP_History(void)
{
	int ret,i;
	int fd;	
	const char* args[] = {SUPP_CONFIG_FILE};
	char buffer[5000];
	

	fd=open(SUPP_CONFIG_FILE, O_CREAT|O_WRONLY|O_APPEND);

        read(fd,buffer,sizeof(buffer));

        for(i=0;i<sizeof(buffer)-10;i++)
        {
        if(buffer[i]=='n')
        {
        if(buffer[i+1]=='e')
        {
        if(buffer[i+2]=='t')
        {
        if(buffer[i+3]=='w')
        {
        if(buffer[i+4]=='o')
        {
      	if(buffer[i+5]=='r')
	{
	if(buffer[i+6]=='k')
        {	        
                write(fd,buffer,(ssize_t)i);
                // printf("----%s-----",buffer);
               break;
        }
	}
	}
	}
	}
	}
	}
	}
	
	return ret;
}


