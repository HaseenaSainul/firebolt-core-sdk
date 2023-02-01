/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CoreSDKCTests.h"
#include "CoreSDKTestGeneratedCode.h"
#include "Common/Types.h"
#include "Device.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t test_generated_properties_get_device_id()
{
    FireboltTypes_StringHandle handle;
    uint32_t result = Device_GetId(&handle);

    if (result == FireboltSDKErrorNone) {
        printf("\nDevice: Id:%s\n", FireboltTypes_String(handle));
        FireboltTypes_StringHandle_Release(handle);
    }
    EXPECT_EQ(result, FireboltSDKErrorNone);
    return result;
}
uint32_t test_generated_properties_get_device_version()
{
    uint32_t result = FireboltSDKErrorGeneral;
    Device_VersionsHandle handle = Device_VersionsHandle_Create();
    if (Device_VersionsHandle_IsValid(handle)) {
        Device_VersionsHandle_Addref(handle);
        result = Device_GetVersion(&handle);

        if (result == FireboltSDKErrorNone) {
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

        }
        Device_VersionsHandle_Release(handle);
    }
    EXPECT_EQ(result, FireboltSDKErrorNone);
    return result;
}

#ifdef __cplusplus
}
#endif
