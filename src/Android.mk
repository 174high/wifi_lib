LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	main.c\
    control_wifi.c

LOCAL_MODULE := control_wifi

include $(BUILD_EXECUTABLE)
