#include "control_wifi.h"

int main(int argc, char *argv[])
{

       	FLC_Wifi_Turn_On_Wifi();

	usleep(3000000); 			//wait for three seconds
	//must wait for ,because insmoding  the driver  requires three seconds

	FLC_Wifi_Client_Search_Wifi_Spot();	

	//printf("wifi_spot:\r\n%s",wifi_spot);

        usleep(1000000);                  //wait for one seconds 
	
	printf("----connect--ap--\r\n");
	
	//connect_AP("\"H30-T10\"",NULL);

	FLC_Wifi_Client_Connect_AP("\"Flairmicro_XM\"","\"Flaircommxiamen\"");	

//	usleep(1000000); 
	
//	printf("---disconnect_AP--\r\n");

	//FLC_Wifi_Client_Disconnect_AP();
	
//	usleep(1000000);
	
  //     printf("---turn_Off_Wifi--\r\n");

	//FLC_Wifi_Turn_Off_Wifi();
	return 0 ;
}



