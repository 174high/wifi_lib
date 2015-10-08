//#include"control_wifi.h"
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIFI_DRIVER_MODULE_PATH   "/system/lib/modules/wlcore_sdio.ko"

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
        system(myoutput_array);
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
        int argcount = 1,i,ret;
        const char* args[] = {WIFI_DRIVER_MODULE_PATH};
        const char* binary_name = "rmmod";
        char myoutput_array[5000];

        sprintf(myoutput_array, "%s", binary_name);
        for(i = 0; i < argcount; ++i)
        {
                strcat(myoutput_array, " ");
                strcat(myoutput_array, args[i]);
        }
        system(myoutput_array);
        return ret;
}


int search_wifi_spot()
{
       int argcount = 1,i,ret;
        const char* args[] = {WIFI_DRIVER_MODULE_PATH};
        const char* binary_name = "";
        char myoutput_array[5000];

        sprintf(myoutput_array, "%s", binary_name);
        for(i = 0; i < argcount; ++i)
        {
                strcat(myoutput_array, " ");
                strcat(myoutput_array, args[i]);
        }
        system(myoutput_array);
        return ret;



}


int main(int argc, char *argv[])
{

	turn_on_wifi();
	turn_off_wifi();

	return 0;
}


