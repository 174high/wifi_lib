//#include"control_wifi.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIFI_DRIVER_MODULE_PATH   "/system/lib/modules/wlcore_sdio.ko"
#define SUPP_CONFIG_FILE          "/data/misc/wifi/wpa_supplicant.conf"

//it  depends on  "SUPP_CONFIG_FILE" 
#define CONTROL_IFACE_PATH	   "/data/misc/wifi/wlan0"
#define ANDROID

extern int  command_System(int argcount,const char* args[],const char* binary_name);

int  command_System(int argcount,const char* args[],const char* binary_name)
{
        char myoutput_array[1000];
	int i,ret;	
	
	sprintf(myoutput_array, "%s", binary_name);
        for(i = 0; i < argcount; ++i)
        {
                strcat(myoutput_array, " ");
                strcat(myoutput_array, args[i]);
        }
        ret=system(myoutput_array);
        return ret;
}

int  turn_On_Wifi(void)
{	
	int  ret;
	const char* args[] = {WIFI_DRIVER_MODULE_PATH};

	ret=command_System(1,args,"insmod");
	
	return ret;
}

int  turn_Off_Wifi(void)
{
        int  ret;
        const char* args[] = {WIFI_DRIVER_MODULE_PATH};

        ret=command_System(1,args,"rmmod");
        return ret;

}

int search_Wifi_Spot(void)
{
     
	int  ret;
	
	const char* args[] = {"wlan0","up"};
		
	ret=command_System(2,args,"ifconfig");

	args[0] = "wlan0" ;
	args[1] = "scan" ;
	
	
        ret=command_System(2,args,"iw");

        return ret;
}


#ifdef ANDROID
  //andoid 
int connect_AP(const char* ssid,const char* psk)
{
	int  ret;
	char* ssid_wpa;
	const char* args[] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};


        ret=command_System(6,args,"wpa_supplicant");
	
        args[0]="-p";
	args[1]= CONTROL_IFACE_PATH;
	args[2]="add_network";
	args[3]= "0";

        ret=command_System(4,args,"wpa_ci");

    	sprintf(ssid_wpa, "%s", "\"\'");

	strcat(ssid_wpa,ssid);

	strcat(ssid_wpa,"\'\"");

	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	args[2]="0";
	args[3]="ssid";
	args[4]=ssid_wpa;

        ret=command_System(5,args,"wpa_ci");

        args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	args[2]="0";
	args[3]="psk";
	args[4]=psk;

       ret=command_System(5,args,"wpa_ci");

   	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	args[2]="select_network";
	args[3]="0";

       ret=command_System(4,args,"wpa_ci");

   	args[0]="-p";
	args[1]=CONTROL_IFACE_PATH;
	args[2]="enable_network";
	args[3]="0";

       ret=command_System(4,args,"wpa_ci");

	args[0]="wlan0";

	ret=command_System(1,args,"dhpad");
	

}

/*
int Disconnect_AP(voi)
{
	int ret;	
        const char* args[] = {""};
	
	ret=command_system(6,args,"ps");


}
*/

#else 

//linux  WPA/WPA2-Personal 

int connect_AP(const char* ssid,const char* psk)
{
        const char* args[] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};
	char* ssid_wpa;
	

        ret=command_System(6,args,"wpa_supplicant");
        
        args[]={"-iwlan0","add_network","0"};

        ret=command_System(3,args,"wpa_ci");

        sprintf(ssid_wpa, "%s", "\"\'");

	strcat(ssid_wpa,ssid);

	strcat(ssid_wpa,"\'\"");

        args[]={"-iwlan0","0","ssid",ssid_wpa};

        ret=command_System(4,args,"wpa_ci");

       args[]={"-iwlan0","0","psk",psk};

       ret=command_System(4,args,"wpa_ci");

   	args[]={"-iwlan0","select_network","0"};

       ret=command_System(3,args,"wpa_ci");

   	args[]={"-iwlan0","enable_network","0"};

       ret=command_System(3,args,"wpa_ci");

	args[]={"wlan0"};

	ret=command_System(1,args,"dhpad");
	
}

#endif

int main(int argc, char *argv[])
{

	turn_On_Wifi();

	usleep(3000000); 			//wait for three seconds
	//must wait for ,because insmoding  the driver  requires three seconds

	search_Wifi_Spot();

        usleep(1000000);                  //wait for one seconds 

	connect_AP("Flaircomm_XM","Flaircommxiamen");	

	usleep(1000000); 


	turn_Off_Wifi();

	return 0;
}


