LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    multicast-client.c\
	input.c\
	suinput.c

LOCAL_MODULE := hidip-device

include $(BUILD_EXECUTABLE)
