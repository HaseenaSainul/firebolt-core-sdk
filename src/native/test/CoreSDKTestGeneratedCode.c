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

#include "Accessibility.h"
#include "Advertising.h"
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
    Device_VersionsHandle handle;
    uint32_t result = Device_GetVersion(&handle);

    if (result == FireboltSDKErrorNone) {
        if (Device_VersionsHandle_IsValid(handle)) {
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
            result = FireboltSDKErrorUnavailable;
        }
    }

    EXPECT_EQ(result, FireboltSDKErrorNone);
    return result;
}
uint32_t test_generated_properties_get_accessibility_closedcaption()
{
    Accessibility_ClosedCaptionsSettingsHandle handle;
    uint32_t result = Accessibility_GetClosedCaptionsSettings(&handle);

    if (result == FireboltSDKErrorNone) {
        if (Accessibility_ClosedCaptionsSettingsHandle_IsValid(handle) == true) {
            printf("ClosedCaption Settings ------------------\n");
            Accessibility_ClosedCaptionsStylesHandle styleHandle = Accessibility_ClosedCaptionsSettings_Get_Styles(handle);
            if (Accessibility_ClosedCaptionsStylesHandle_IsValid(styleHandle)) {
                printf("ClosedCaptionStyles:\n");
                char* fontFamily = Accessibility_ClosedCaptionsStyles_Get_FontFamily(styleHandle);
                printf("\tFontFamily : %s\n", fontFamily);
                uint32_t fontSize = Accessibility_ClosedCaptionsStyles_Get_FontSize(styleHandle);
                printf("\tFontSize : %d\n", fontSize);
                char* fontColor = Accessibility_ClosedCaptionsStyles_Get_FontColor(styleHandle);
                printf("\tFontColor : %s\n", fontColor);
                char* fontEdge = Accessibility_ClosedCaptionsStyles_Get_FontEdge(styleHandle);
                printf("\tFontEdge : %s\n", fontEdge);
                char* fontEdgeColor = Accessibility_ClosedCaptionsStyles_Get_FontEdgeColor(styleHandle);
                printf("\tFontEdgeColor : %s\n", fontEdgeColor);
                uint32_t fontOpacity = Accessibility_ClosedCaptionsStyles_Get_FontOpacity(styleHandle);
                printf("\tFontOpacity : %d\n", fontOpacity);
                char* bgColor = Accessibility_ClosedCaptionsStyles_Get_BackgroundColor(styleHandle);
                printf("\tBackgroundColor : %s\n", bgColor);
                uint32_t bgOpacity = Accessibility_ClosedCaptionsStyles_Get_BackgroundOpacity(styleHandle);
                printf("\tBackgroundOpacity : %d\n", bgOpacity);
                char* txAlign = Accessibility_ClosedCaptionsStyles_Get_TextAlign(styleHandle);
                printf("\tTextAlign : %s\n", txAlign);
                char* txAlignVertical = Accessibility_ClosedCaptionsStyles_Get_TextAlignVertical(styleHandle);
                printf("\tTextAlignVertical : %s\n", txAlignVertical);
                Accessibility_ClosedCaptionsStylesHandle_Release(styleHandle);
            }
            bool enabled = Accessibility_ClosedCaptionsSettings_Get_Enabled(handle);
            printf("Enabled: %d\n", enabled);
            Accessibility_ClosedCaptionsSettingsHandle_Release(handle);
        } else {
            result = FireboltSDKErrorUnavailable;
        }
    }

    EXPECT_EQ(result, FireboltSDKErrorNone);
    return result;
}
uint32_t test_generated_properties_get_accessibility_voiceguidancesettings()
{
    Accessibility_VoiceGuidanceSettingsHandle handle;
    uint32_t result = Accessibility_GetVoiceGuidanceSettings(&handle);

    if (result == FireboltSDKErrorNone) {
        if (Accessibility_VoiceGuidanceSettingsHandle_IsValid(handle) == true) {
            bool enabled = Accessibility_VoiceGuidanceSettings_Get_Enabled(handle);
            uint32_t speed = Accessibility_VoiceGuidanceSettings_Get_Speed(handle);
            printf("VoiceGuidanceSettings: Enabled : %d, Speed : %d", enabled, speed);
            Accessibility_VoiceGuidanceSettingsHandle_Release(handle);
        } else {
            result = FireboltSDKErrorUnavailable;
        }
    }
    EXPECT_EQ(result, FireboltSDKErrorNone);
    return result;
}
const char* get_skiprestriction_enum_string(Advertising_SkipRestriction skipRestriction)
{
    char* strSkipRestriction;
    switch(skipRestriction) {
    case ADVERTISING_SKIPRESTRICTION_NONE:
        strSkipRestriction = "None";
        break;
    case ADVERTISING_SKIPRESTRICTION_ADS_UNWATCHED:
        strSkipRestriction = "AdsUnwatched";
        break;
    case ADVERTISING_SKIPRESTRICTION_ADS_ALL:
        strSkipRestriction = "AdsAll";
        break;
    case ADVERTISING_SKIPRESTRICTION_ALL:
        strSkipRestriction = "All";
        break;
    default:
        strSkipRestriction = "None";
        break;
    }
    return strSkipRestriction;
}

uint32_t test_generated_properties_get_advertising_policy()
{
    Advertising_AdPolicyHandle handle;
    uint32_t result = Advertising_GetPolicy(&handle);
    if (result == FireboltSDKErrorNone) {
        if (Advertising_AdPolicyHandle_IsValid(handle) == true) {
            printf("AdPolicy: ");
            Advertising_SkipRestriction skipRestriction = Advertising_AdPolicy_Get_SkipRestriction(handle);
            printf("SkipRestriction = %s ", get_skiprestriction_enum_string(skipRestriction));
            bool limitAdTracking = Advertising_AdPolicy_Get_LimitAdTracking(handle);
            printf("LimitAdTracking = %s \n", limitAdTracking? "true" : "false");
            Advertising_AdPolicyHandle_Release(handle);
        } else {
            result = FireboltSDKErrorUnavailable;
        }
    }
    EXPECT_EQ(result, FireboltSDKErrorNone);
    return result;
}

#ifdef __cplusplus
}
#endif
