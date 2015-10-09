//#include"control_wifi.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIFI_DRIVER_MODULE_PATH   "/system/lib/modules/wlcore_sdio.ko"
#define SUPP_CONFIG_FILE          "/data/misc/wifi/wpa_supplicant.conf"

//it  depends on  "SUPP_CONFIG_FILE" 
#define CONTROL_IFACE_PATH	   "/data/misc/wifi/wlan0"


int  command_system(int argcount,const char* args[],const char* binary_name)
{
        char myoutput_array[5000];
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

int  turn_on_wifi(void)
{	
	int  ret;
	const char* args[] = {WIFI_DRIVER_MODULE_PATH};

	ret=command_system(1,args,"insmod");
	return ret;
}

int  turn_off_wifi(void)
{
        int  ret;
        const char* args[] = {WIFI_DRIVER_MODULE_PATH};

        ret=command_system(1,args,"rmmod");
        return ret;

}

int search_wifi_spot(void)
{
     
	int  ret;
	
	const char* args[] = {"wlan0","up"};
		
	ret=command_system(2,args,"ifconfig");

	args[] = {"wlan0","scan"};
	
        ret=command_system(2,args,"iw");

        return ret;
}


#ifdef ANDROID
  //andoid 
int connect_AP()
{
	const char* args[] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};

        ret=command_system(6,args,"wpa_supplicant");
	
	args[]={"-p",CONTROL_IFACE_PATH,""};

	ret=command_system(2,args,"wpa_ci");

	

}


#elif 

//linux  WPA/WPA2-Personal 

int connect_AP(const char* ssid,const char* psk)
{
        const char* args[] = {"-d","-Dnl80211","-c",SUPP_CONFIG_FILE,"-iwlan0","-B"};
	char* ssid_wpa;
	

        ret=command_system(6,args,"wpa_supplicant");
        
        args[]={"-iwlan0","add_network","0"};

        ret=command_system(3,args,"wpa_ci");

        sprintf(ssid_wpa, "%s", "\"");

	strcat(ssid_wpa,ssid);

	strcat(ssid_wpa,"\"");

        args[]={"-iwlan0","0","ssid",ssid_wpa};

        ret=command_system(4,args,"wpa_ci");

       args[]={"-iwlan0","0","psk",psk};

       ret=command_system(4,args,"wpa_ci");

   	args[]={"-iwlan0","select_network","0"};

       ret=command_system(3,args,"wpa_ci");

   	args[]={"-iwlan0","enable_network","0"};

       ret=command_system(3,args,"wpa_ci");

	args[]={"wlan0"};

	ret=command_system(1,args,"dhpad");
	
}

#endif

int main(int argc, char *argv[])
{

	turn_on_wifi();
	search_wifi_spot();
	
	turn_off_wifi();

	return 0;
}


