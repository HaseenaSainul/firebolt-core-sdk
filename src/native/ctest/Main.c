#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "Firebolt.h"
#include "Accessibility.h"
#include "Account.h"
#include "Advertising.h"
#include "Device.h"
#include "Discovery.h"
#include "Common/Entertainment.h"

void ShowMenu()
{
    printf("Enter\n"
           "\tI : Get Device ID\n"
           "\tV : Get Device Version\n"
           "\tS : Get Closed Caption Settings\n"
           "\tG : Get Voice Guidance Settings\n"
           "\tP : Get Advertising Policy\n"
           "\tU : Get Account UID\n"
           "\tE : Push EntityInfo\n"
           "\tN : Register/Unregister for Device Name change\n"
           "\tR : Register/Unregister for Screen Resolution change\n"
           "\tA : Register/Unregister for Accessibilty Voice Guidance change\n"
           "\tQ : Quit\n\n"
          );
}

void ShowEventMenu()
{
    printf("Enter\n"
         "\tR: Register Event\n"
         "\tU: Unregister Event\n"
         "\tQ : Quit\n");
}

#define HandleEventListener(Module, eventFuncName, Callback, eventTestStr, eventName) \
{ \
    int opt; \
    do { \
        getchar(); \
        ShowEventMenu(); \
        printf("Enter option : "); \
        opt = toupper(getchar()); \
        switch (opt) { \
        case 'R': { \
            uint32_t result = Module##_Register_##eventFuncName##Update((const void*)Callback, eventTestStr); \
            if (result != FireboltSDKErrorNone) { \
                printf("Register event %s is failed, status = %d \n", eventName, result); \
            } else { \
                printf("Event %s is registered successfully\n", eventName); \
            } \
            break; \
        } \
        case 'U': { \
            uint32_t result = Module##_Unregister_##eventFuncName##Update((const void*)Callback); \
            if (result != FireboltSDKErrorNone) { \
                printf("Unregister event %s is failed, status = %d \n", eventName, result); \
            } else { \
                printf("Event %s is unregistered successfully\n", eventName); \
            } \
            break; \
        } \
        default: \
            break; \
        } \
    } while (opt != 'Q'); \
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

static const char deviceNameTestStr[] = "DeviceNameTestStr";
static void NotifyDeviceNameChange(const void* userData, FireboltTypes_StringHandle handle)
{
    if (handle) {
        printf("Got new device.name :%s\n", FireboltTypes_String(handle));
        FireboltTypes_StringHandle_Release(handle);
    } else {
        printf("device.name event handle is not valid\n");
    }
}

static const char deviceScreenResolutionTestStr[] = "deviceScreenResolutionTestStr";
static void NotifyDeviceScreenResolutionChange(const void* userData, Device_ResolutionIntegerArrayHandle handle)
{
    if (Device_ResolutionIntegerArrayHandle_IsValid(handle) == true) {
        uint32_t size = Device_ResolutionIntegerArray_Size(handle);
        printf("Device ScreenResolutions changed for %d numbers\n", size);
        for (uint32_t i = 0; i < size; ++i) {
            printf("New reslution[%d] = %d\n", i, Device_ResolutionIntegerArray_Get(handle, i));
        }
        Device_ResolutionIntegerArrayHandle_Release(handle);
    } else {
        printf("device.screenresolution event handle is not valid\n");
    }
}

static const char accessibilityVoiceGuidanceTestStr[] = "AccessibilityVoiceGuidanceTestStr";
static void NotifyAccessibilityVoiceGuidanceChange(const void* userData, Accessibility_VoiceGuidanceSettingsHandle handle)
{
    if (Accessibility_VoiceGuidanceSettingsHandle_IsValid(handle) == true) {
        bool enabled = Accessibility_VoiceGuidanceSettings_Get_Enabled(handle);
        uint32_t speed = Accessibility_VoiceGuidanceSettings_Get_Speed(handle);
        printf("VoiceGuidanceSettings: Enabled : %d, Speed : %d\n", enabled, speed);
        Accessibility_VoiceGuidanceSettingsHandle_Release(handle);
    } else {
        printf("accessibility.voiceguidance event handle is not valid\n");
    }
}

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

    printf("Firebolt Core SDK Test\n");
    
    //Intitialize the SDK
    FireboltSDK_Initialize(config);
    int option;

    do {
        ShowMenu();
        printf("Enter option : ");
        option = toupper(getchar());
        switch (option) {
        case 'I': {
            //Lets get the Device ID
            FireboltTypes_StringHandle handle;
            uint32_t result = Device_GetId(&handle);
            if (result == FireboltSDKErrorNone) {
                printf("Device: Id:%s\n\n", FireboltTypes_String(handle));
                FireboltTypes_StringHandle_Release(handle);
                handle = NULL;
            } else {
                printf("Failed to get Device ID\n\n");
            }
            break;
        }
        case 'V': {
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
                    printf("Device:SDK Version major:%d minor:%d patch:%d readable:%s\n",
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
                    printf("Device:OS  Version major:%d minor:%d patch:%d readable:%s\n\n",
                    major, minor, patch, readable);
                    Types_SemanticVersionHandle_Release(osHandle);
                    result = FireboltSDKErrorNone;
                }
                Device_VersionsHandle_Release(handle);
            } else {
                printf("Failed to get Device Version\n\n");
            }
            break;
        }
	case 'S': {
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
                    printf("Enabled: %d\n\n", enabled);
                    Accessibility_ClosedCaptionsSettingsHandle_Release(handle);
                } else {
                    printf("Invalid ClosedCaptionsSettingsHandle\n\n");
                }
            } else {
                printf("Failed to get Closed Caption Settings\n\n");
            }
            break;
        }
        case 'G': {
            Accessibility_VoiceGuidanceSettingsHandle handle;
            uint32_t result = Accessibility_GetVoiceGuidanceSettings(&handle);

            if (result == FireboltSDKErrorNone) {
                if (Accessibility_VoiceGuidanceSettingsHandle_IsValid(handle) == true) {
                    bool enabled = Accessibility_VoiceGuidanceSettings_Get_Enabled(handle);
                    uint32_t speed = Accessibility_VoiceGuidanceSettings_Get_Speed(handle);
                    printf("VoiceGuidanceSettings: Enabled : %d, Speed : %d\n", enabled, speed);
                    Accessibility_VoiceGuidanceSettingsHandle_Release(handle);
                } else {
                    printf("Invalid VoiceGuidanceSettingsHandle\n\n");
                }
            } else {
                printf("Failed to get Voice Guidance Settings\n\n");
            }
            break;
        }
        case 'P': {
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
                    printf("Invalid Advertising_AdPolicyHandle\n\n");
                }
            } else {
                printf("Failed to get Advertising Policy\n\n");
            }
            break;
        }
        case 'U': {
            FireboltTypes_StringHandle handle;
            uint32_t result = Account_GetUid(&handle);
            if (result == FireboltSDKErrorNone) {
                if (Advertising_AdPolicyHandle_IsValid(handle) == true) {
                    printf("Account: Uid:%s\n\n", FireboltTypes_String(handle));
                    FireboltTypes_StringHandle_Release(handle);
                    handle = NULL;
                }
            } else {
                printf("Failed to get Advertising Policy\n\n");
            }
            break;
        }
        case 'E': {
            {
                Discovery_EntityInfoFederatedResponseHandle federatedResponse = Discovery_EntityInfoFederatedResponseHandle_Create();
                Discovery_EntityInfoResultHandle entityInfoResult = Discovery_EntityInfoResultHandle_Create();
                Discovery_EntityInfoHandle entityInfo = Discovery_EntityInfoHandle_Create();

                //Populate the ContentIdentifiers Object
                Discovery_ContentIdentifiersHandle ci = Discovery_ContentIdentifiersHandle_Create();
                Discovery_ContentIdentifiers_Set_AssetId(ci, "12345678");
                Discovery_ContentIdentifiers_Set_EntityId(ci, "ABCDEFGH");
                Discovery_ContentIdentifiers_Set_SeasonId(ci, "1");
                Discovery_ContentIdentifiers_Set_SeriesId(ci, "9ER34FR");
                Discovery_ContentIdentifiers_Set_AppContentData(ci, "Sample App Content Data");

                //Populate EntityInfo Object
                //Set the ContentIdentifiers Object to EntityInfo Object
                Discovery_EntityInfo_Set_Identifiers(entityInfo, ci);
                Discovery_EntityInfo_Set_Title(entityInfo, "Game Of Thrones");
                Discovery_EntityInfo_Set_EntityType(entityInfo, "program");
                Discovery_EntityInfo_Set_ProgramType(entityInfo, ENTERTAINMENT_PROGRAMTYPE_SEASON);
                Discovery_EntityInfo_Set_Synopsis(entityInfo, "The imaginary continent of Westeros was once inhabited by a magical people, the Children of the Forest. For centuries, other people came across the Narrow Sea from the eastern continent of Essos: up North, the First Men; in the Center, the Andals; down South, the Dornish.");
                Discovery_EntityInfo_Set_SeasonNumber(entityInfo, 1);
                Discovery_EntityInfo_Set_EpisodeNumber(entityInfo, 1);
                Discovery_EntityInfo_Set_ReleaseDate(entityInfo, "2012-04-23T18:25:43.511Z");
                {
                    //Populate the ContentRatings Handle for US TV scheme
                    Discovery_ContentRatingHandle cr = Discovery_ContentRatingHandle_Create();
                    Discovery_ContentRating_Set_Scheme(cr, DISCOVERY_SCHEME_US_TV);
                    Discovery_ContentRating_Set_Rating(cr, "TVMA");
                    Discovery_ContentRating_AdvisoriesArray_Add(cr, "V");
                    Discovery_ContentRating_AdvisoriesArray_Add(cr, "S");
                    Discovery_ContentRating_AdvisoriesArray_Add(cr, "L");
                    Discovery_EntityInfo_ContentRatingsArray_Add(entityInfo, cr);
                }

                {
                    //Populate the ContentRatings Handle for US TV scheme
                    Discovery_ContentRatingHandle cr = Discovery_ContentRatingHandle_Create();
                    Discovery_ContentRating_Set_Scheme(cr, DISCOVERY_SCHEME_CA_TV);
                    Discovery_ContentRating_Set_Rating(cr, "18+");
                    Discovery_ContentRating_AdvisoriesArray_Add(cr, "18+");
                    Discovery_EntityInfo_ContentRatingsArray_Add(entityInfo, cr);
                }

                //Populate WayToWatch Array in EntityInfo
                {
                    //Populate the WayToWatch Object
                    Discovery_WayToWatchHandle w2w = Discovery_WayToWatchHandle_Create();
                    {
                         //Add the ContentIdentifiers Object in WayToWatch
                        Discovery_ContentIdentifiersHandle ciI = Discovery_ContentIdentifiersHandle_Create();
                        Discovery_ContentIdentifiers_Set_AssetId(ciI, "12345678");
                        Discovery_ContentIdentifiers_Set_EntityId(ciI, "ABCDEFGH");
                        Discovery_ContentIdentifiers_Set_SeasonId(ciI, "1");
                        Discovery_ContentIdentifiers_Set_SeriesId(ciI, "9ER34FR");
                        Discovery_ContentIdentifiers_Set_AppContentData(ciI, "Sample App Content Data");
                        Discovery_WayToWatch_Set_Identifiers(w2w, ciI);
                    }
                    Discovery_WayToWatch_Set_Expires(w2w, "2014-04-23T18:25:43.511Z");
                    Discovery_WayToWatch_Set_Entitled(w2w, true);
                    Discovery_WayToWatch_Set_EntitledExpires(w2w, "2014-04-23T18:25:43.511Z");
                    Discovery_WayToWatch_Set_OfferingType(w2w, ENTERTAINMENT_OFFERINGTYPE_FREE);
                    Discovery_WayToWatch_Set_HasAds(w2w, true);
                    Discovery_WayToWatch_VideoQualityArray_Add(w2w, DISCOVERY_VIDEOQUALITY_HD);
                    Discovery_WayToWatch_VideoQualityArray_Add(w2w, DISCOVERY_VIDEOQUALITY_UHD);
                    Discovery_WayToWatch_AudioProfileArray_Add(w2w, TYPES_AUDIOPROFILE_STEREO);
                    Discovery_WayToWatch_AudioProfileArray_Add(w2w, TYPES_AUDIOPROFILE_DOLBY_DIGITAL_5_1);
                    Discovery_WayToWatch_AudioProfileArray_Add(w2w, TYPES_AUDIOPROFILE_DOLBY_DIGITAL_5_1_PLUS);

                    Discovery_WayToWatch_AudioLanguagesArray_Add(w2w, "en");
                    Discovery_WayToWatch_AudioLanguagesArray_Add(w2w, "fr");

                    Discovery_WayToWatch_ClosedCaptionsArray_Add(w2w, "en");
                    Discovery_WayToWatch_ClosedCaptionsArray_Add(w2w, "fr");

                    Discovery_WayToWatch_SubtitlesArray_Add(w2w, "en");
                    Discovery_WayToWatch_SubtitlesArray_Add(w2w, "fr");

                    Discovery_WayToWatch_AudioDescriptionsArray_Add(w2w, "en");

                    Discovery_EntityInfo_WaysToWatchArray_Add(entityInfo, w2w);
              }

                //Populate EntityInfoResult Object
                Discovery_EntityInfoResult_Set_Expires(entityInfoResult, "2012-06-23T18:25:43.511Z");
                Discovery_EntityInfoResult_Set_Entity(entityInfoResult, entityInfo);

                //Populate the EntityInfoFederatedRespnse
                Discovery_EntityInfoFederatedResponse_Set_EntityInfoFederatedResponseResult(federatedResponse, entityInfoResult);


                //All Set, Call the Push
                uint32_t result = Discovery_PushEntityInfo(federatedResponse);
                if (result == FireboltSDKErrorNone) {
                    printf("\nSuccessfully Pushed entityInfo\n");

                } else {
                    printf("\nFailed to Push entityInfo\n");
                }
                break;
            }
        }
        case 'R': {
            HandleEventListener(Device, ScreenResolution, (const void*)NotifyDeviceScreenResolutionChange, deviceScreenResolutionTestStr, "device.screenresolution")
            break;
        }
        case 'N': {
            HandleEventListener(Device, Name, (const void*)NotifyDeviceNameChange, deviceNameTestStr, "device.name")
            break;
        }
        case 'A': {
            HandleEventListener(Accessibility, VoiceGuidanceSettings, (const void*)NotifyAccessibilityVoiceGuidanceChange, accessibilityVoiceGuidanceTestStr, "accessibility.voiceguidance")
            break;
        }
        default:
            break;
        }
        getchar(); // Skip white space
    } while (option != 'Q');

    FireboltSDK_Deinitialize();

    return 0;
}
