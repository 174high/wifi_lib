#include "control_wifi.h"

int main(int argc, char *argv[])
{

	turn_On_Wifi();

	usleep(3000000); 			//wait for three seconds
	//must wait for ,because insmoding  the driver  requires three seconds

	search_Wifi_Spot();

        usleep(1000000);                  //wait for one seconds 

	connect_AP("Flaircomm_XM","Flaircommxiamen");	

	usleep(1000000); 

	disconnect_AP();
	
	usleep(1000000);
	
	turn_Off_Wifi();

	return 0;
}


