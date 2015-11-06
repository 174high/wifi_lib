#ifndef  _CONTROL_WIFI_
#define  _CONTROL_WIFI_
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



#define WIFI_DRIVER_MODULE_PATH   "/system/lib/modules/wlcore_sdio.ko"
#define SUPP_CONFIG_FILE          "/data/misc/wifi/wpa_supplicant.conf"


//it  depends on  "SUPP_CONFIG_FILE" 
#define CONTROL_IFACE_PATH	   "/data/misc/wifi/wlan0"
#define DHCPCD_WLAN_PATH           "/data/misc/dhcp/dhcpcd-wlan0.pid"

//#define ANDROID
//#define LINUX

typedef  struct{
	char ssid[50];
	char security[50];
	char signal[50];	
}wifi_spot;

wifi_spot wifi_info[20];

//tool
//different platfrom requires different tool 
#define  DHCP_TOOL  "dhcpcd"



extern int  FLC_Wifi_Turn_On_Wifi(void) ;
extern int  FLC_Wifi_Turn_Off_Wifi(void) ;
extern int  FLC_Wifi_Client_Search_Wifi_Spot(void);
extern int  FLC_Wifi_Client_Connect_AP(const char* ssid,const char* psk) ;
extern int  FLC_Wifi_Client_Disconnect_AP(void);
extern int  FCL_Widi_Client_Clear_AP_History(void);

#endif





