#include <stdio.h>
#include "Firebolt.h"
#include "Device.h"
#include <assert.h>

int main (int argc, char* argv[])
{
    char* config = "{\
    \"waitTime\": 1000,\
    \"logLevel\": \"Info\",\
    \"workerPool\":{\
        \"queueSize\": 8,\
        \"threadCount\": 3\
    },\
    \"wsUrl\": \"ws://127.0.0.1:9998\"\
}";

    FireboltTypes_StringHandle handle;

    printf("Firebolt Core SDK Test\n");
    
    //Intitialize the SDK
    FireboltSDK_Initialize(config);

    //Lets get the Device ID
    uint32_t result = Device_GetId(&handle);
    if (result == FireboltSDKErrorNone) {
        printf("\nDevice: Id:%s\n", FireboltTypes_String(handle));
        FireboltTypes_StringHandle_Release(handle);
        handle = NULL;
    }
    else {
        printf("\nFailed to get Device ID\n");
    }

    {
        Device_VersionsHandle handle;
        uint32_t result = Device_GetVersion(&handle);
        if (result == FireboltSDKErrorNone) {
            assert(Device_VersionsHandle_IsValid(handle)); 
            Types_SemanticVersionHandle sdkHandle = Device_Versions_Get_Sdk(handle);
            if (Types_SemanticVersionHandle_IsValid(sdkHandle)) {
                uint32_t major = Types_SemanticVersion_Get_Major(sdkHandle);
                uint32_t minor = Types_SemanticVersion_Get_Minor(sdkHandle);
                uint32_t patch = Types_SemanticVersion_Get_Patch(sdkHandle);
                char* readable = Types_SemanticVersion_Get_Readable(sdkHandle);
                printf("\nDevice:SDK Version major:%d minor:%d patch:%d readable:%s\n",
                major, minor, patch, readable);
                Types_SemanticVersionHandle_Release(sdkHandle);
                result = FireboltSDKErrorNone;
            }
            Types_SemanticVersionHandle osHandle = Device_Versions_Get_Os(handle);
            if (Types_SemanticVersionHandle_IsValid(osHandle)) {
                uint32_t major = Types_SemanticVersion_Get_Major(osHandle);
                uint32_t minor = Types_SemanticVersion_Get_Minor(osHandle);
                uint32_t patch = Types_SemanticVersion_Get_Patch(osHandle);
                const char* readable = Types_SemanticVersion_Get_Readable(osHandle);
                printf("\nDevice:OS  Version major:%d minor:%d patch:%d readable:%s\n",
                major, minor, patch, readable);
                Types_SemanticVersionHandle_Release(osHandle);
                result = FireboltSDKErrorNone;
            }
            Device_VersionsHandle_Release(handle);
        } else {
            printf("\nFailed to get Device Version\n");
        }

    }

    FireboltSDK_Deinitialize();

    return 0;
}
