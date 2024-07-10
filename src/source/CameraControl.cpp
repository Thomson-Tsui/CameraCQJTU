#include "WinSock2.h"
#include "InfraredTempSDK.h"
#include "mex.h"
#include <iostream>
#include <cstring>

enum DeviceType { DEVICE_TYPE_A = 0, DEVICE_TYPE_B = 1, DEVICE_TYPE_C = 2 };
enum SdkReturnType {
    SDK_RETURN_SUCCESS = 0, SDK_RETURN_FAIL = -1, SDK_RETURN_NULL = 1
};

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
    if (nrhs < 1) {
        mexErrMsgIdAndTxt("MATLAB:mexFunction:inputError", "At least one input argument required.");
    }

    if (mxIsChar(prhs[0])) {
        char* cmd = mxArrayToString(prhs[0]);

        if (strcmp(cmd, "initialize") == 0) {
            int sdk_init = sdk_initialize();
            plhs[0] = mxCreateDoubleScalar((double)sdk_init);
        }
        else if (strcmp(cmd, "setDeviceType") == 0 && nrhs == 4) {
            int iDeviceType = (int)mxGetScalar(prhs[1]);
            char* username = mxArrayToString(prhs[2]);
            char* password = mxArrayToString(prhs[3]);

            sdk_set_type(iDeviceType, username, password);
            plhs[0] = mxCreateDoubleScalar(0); // success
        }
        else if (strcmp(cmd, "createHandle") == 0) {
            IRNETHANDLE pHandle = sdk_create();
            plhs[0] = mxCreateDoubleScalar((double)(uintptr_t)pHandle);
        }
        else if (strcmp(cmd, "searchDevice") == 0 && nrhs == 2) {
            IRNETHANDLE pHandle = (IRNETHANDLE)(uintptr_t)mxGetScalar(prhs[1]);
            DeviceList deviceList;
            int sdk_search_device_ret = sdk_search_device(pHandle, deviceList);
            plhs[0] = mxCreateDoubleScalar((double)sdk_search_device_ret);
        }
        else if (strcmp(cmd, "loginDevice") == 0 && nrhs == 3) {
            IRNETHANDLE pHandle = (IRNETHANDLE)(uintptr_t)mxGetScalar(prhs[1]);
            const mxArray* mxDeviceInfo = prhs[2];
            ChannelInfo deviceInfo;

            const mxArray* mxIP = mxGetField(mxDeviceInfo, 0, "szIP");
            if (mxIP) strcpy(deviceInfo.szIP, mxArrayToString(mxIP));

            deviceInfo.channel = (int)mxGetScalar(mxGetField(mxDeviceInfo, 0, "channel"));
            deviceInfo.wPortNum = (unsigned short)mxGetScalar(mxGetField(mxDeviceInfo, 0, "wPortNum"));
            deviceInfo.byChanNum = (unsigned char)mxGetScalar(mxGetField(mxDeviceInfo, 0, "byChanNum"));
            deviceInfo.byChanNum2 = (unsigned char)mxGetScalar(mxGetField(mxDeviceInfo, 0, "byChanNum2"));
            deviceInfo.iStreamNum = (int)mxGetScalar(mxGetField(mxDeviceInfo, 0, "iStreamNum"));
            deviceInfo.iStreamNum2 = (int)mxGetScalar(mxGetField(mxDeviceInfo, 0, "iStreamNum2"));
            strcpy(deviceInfo.szServerName, mxArrayToString(mxGetField(mxDeviceInfo, 0, "szServerName")));
            strcpy(deviceInfo.szUserName, mxArrayToString(mxGetField(mxDeviceInfo, 0, "szUserName")));
            strcpy(deviceInfo.szPWD, mxArrayToString(mxGetField(mxDeviceInfo, 0, "szPWD")));

            int _isLogin = sdk_loginDevice(pHandle, deviceInfo) == SDK_RETURN_SUCCESS;
            plhs[0] = mxCreateLogicalScalar(_isLogin);
        }
        else if (strcmp(cmd, "logoutDevice") == 0 && nrhs == 2) {
            IRNETHANDLE pHandle = (IRNETHANDLE)(uintptr_t)mxGetScalar(prhs[1]);
            int logout_ret = sdk_logoutDevice(pHandle);
            plhs[0] = mxCreateDoubleScalar((double)logout_ret);
        }
        else if (strcmp(cmd, "setDeviceIP") == 0 && nrhs == 4) {
            IRNETHANDLE pHandle = (IRNETHANDLE)(uintptr_t)mxGetScalar(prhs[1]);
            const mxArray* mxDeviceInfo = prhs[2];
            ChannelInfo deviceInfo;

            const mxArray* mxIP = mxGetField(mxDeviceInfo, 0, "szIP");
            if (mxIP) strcpy(deviceInfo.szIP, mxArrayToString(mxIP));

            deviceInfo.channel = (int)mxGetScalar(mxGetField(mxDeviceInfo, 0, "channel"));
            deviceInfo.wPortNum = (unsigned short)mxGetScalar(mxGetField(mxDeviceInfo, 0, "wPortNum"));
            deviceInfo.byChanNum = (unsigned char)mxGetScalar(mxGetField(mxDeviceInfo, 0, "byChanNum"));
            deviceInfo.byChanNum2 = (unsigned char)mxGetScalar(mxGetField(mxDeviceInfo, 0, "byChanNum2"));
            deviceInfo.iStreamNum = (int)mxGetScalar(mxGetField(mxDeviceInfo, 0, "iStreamNum"));
            deviceInfo.iStreamNum2 = (int)mxGetScalar(mxGetField(mxDeviceInfo, 0, "iStreamNum2"));
            strcpy(deviceInfo.szServerName, mxArrayToString(mxGetField(mxDeviceInfo, 0, "szServerName")));
            strcpy(deviceInfo.szUserName, mxArrayToString(mxGetField(mxDeviceInfo, 0, "szUserName")));
            strcpy(deviceInfo.szPWD, mxArrayToString(mxGetField(mxDeviceInfo, 0, "szPWD")));

            char* newIP = mxArrayToString(prhs[3]);
            int iRes = sdk_set_device_ip(pHandle, deviceInfo, newIP, 0);
            plhs[0] = mxCreateDoubleScalar((double)iRes);
        }
        else if (strcmp(cmd, "getUserOnline") == 0 && nrhs == 2) {
            //IRNETHANDLE pHandle = (IRNETHANDLE)(uintptr_t)mxGetScalar(prhs[1]);
            //User_Online user_online;
            //int _online_ret = sdk_get_user_online(pHandle, user_online);
            //plhs[0] = mxCreateDoubleScalar((double)_online_ret);
        }
        else {
            mexErrMsgIdAndTxt("MATLAB:mexFunction:invalidCmd", "Invalid command.");
        }
    }
    else {
        mexErrMsgIdAndTxt("MATLAB:mexFunction:invalidInput", "Input must be a string.");
    }
}
