#include "control_wifi.h"

int main(int argc, char *argv[])
{
	
      	char wifi_spot[5000];
	//char *wifi_ssid;
	//char wifi_psk[100];

       	turn_On_Wifi();

	usleep(3000000); 			//wait for three seconds
	//must wait for ,because insmoding  the driver  requires three seconds

	search_Wifi_Spot(wifi_spot);	

	printf("wifi_spot:\r\n%s",wifi_spot);

        usleep(1000000);                  //wait for one seconds 
	
	printf("----connect--ap--\r\n");
	
	//connect_AP("\"H30-T10\"",NULL);

	connect_AP("\"Flairmicro_XM\"","\"Flaircommxiamen\"");	

//	usleep(1000000); 
	
//	printf("---disconnect_AP--\r\n");

//	disconnect_AP();
	
//	usleep(1000000);
	
  //     printf("---turn_Off_Wifi--\r\n");

//	turn_Off_Wifi();
	return 0 ;
}



