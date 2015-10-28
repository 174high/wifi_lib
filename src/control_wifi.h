#ifndef  _CONTROL_WIFI_
#define  _CONTROL_WIFI_
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIFI_DRIVER_MODULE_PATH   "/system/lib/modules/wlcore_sdio.ko"
#define SUPP_CONFIG_FILE          "/data/misc/wifi/wpa_supplicant.conf"

//it  depends on  "SUPP_CONFIG_FILE" 
#define CONTROL_IFACE_PATH	   "/data/misc/wifi/wlan0"
//#define ANDROID
//#define LINUX


//tool
//different platfrom requires different tool 
#define  DHCP_TOOL  "dhcpcd"



extern int  command_System(int argcount,const char* args[],const char* binary_name,char* returndata,int inputcunt,const char * inputdata[]);

extern int  turn_On_Wifi(void) ;
extern int  turn_Off_Wifi(void) ;
extern int  search_Wifi_Spot(char * wifispot);
extern int  connect_AP(const char* ssid,const char* psk) ;
extern int  disconnect(void);
extern int  clear_AP_History(void);

#endif





