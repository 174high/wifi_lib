#include "control_wifi.h"

int main(int argc, char *argv[])
{
	
	char wifi_spot[5000];
	//char *wifi_ssid;
	//char wifi_psk[100];

       	//turn_On_Wifi();

	//usleep(3000000); 			//wait for three seconds
	//must wait for ,because insmoding  the driver  requires three seconds

	//search_Wifi_Spot(wifi_spot);	

        //usleep(1000000);                  //wait for one seconds 
	
	printf("----connect--ap--\r\n");
	
	connect_AP_Open("\'\"H30-T10\"\'");
	//wifi_ssid[0]='\'';
	//wifi_ssid[1]='\"';
	//wifi_ssid[2]='\"';
	//wifi_ssid[3]='\'';
	//wifi_psk[0]=;
	
	//wifi_ssid="\'\"Flaircommxiamen\"\'";
	//printf("---wifi_ssid=%s-----",wifi_ssid);

//	connect_AP("\'\"Flairmicro_XM\"\'","\'\"Flaircommxiamen\"\'");	

//	usleep(1000000); 
	
//	printf("---disconnect_AP--\r\n");

//	disconnect_AP();
	
//	usleep(1000000);
	
  //     printf("---turn_Off_Wifi--\r\n");

//	turn_Off_Wifi();


	return 0;
}


