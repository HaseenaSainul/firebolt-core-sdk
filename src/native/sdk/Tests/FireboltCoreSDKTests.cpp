
#include "Module.h"
#include "FireboltCoreSDKTests.h"

namespace FireboltSDK {
    CoreTests::CoreTests()
        : Tests()
    {
        _functionMap.emplace(std::piecewise_construct, std::forward_as_tuple("Get Discovery Policy"),
                             std::forward_as_tuple(&GetDiscoveryPolicy));
    }

    /* static */ uint32_t CoreTests::GetDiscoveryPolicy()
    {
        const string method = _T("discovery.policy");
        WPEFramework::Core::ProxyType<Policy> response;
        uint32_t status = FireboltSDK::Properties::Get(method, response);

        EXPECT_EQ(status, Error::None);
        if (status == Error::None) {
            printf("\nEnableRecommendations : %d", response->EnableRecommendations.Value());
            printf("\nShareWatchHistory : %d", response->ShareWatchHistory.Value());
            printf("\nRememberWatchedPrograms : %d", response->RememberWatchedPrograms.Value());
        } else {
            printf("\nGet %s status = %d\n", method.c_str(), status);
        }

        return status;
    }
}

#ifdef __cplusplus
extern "C" {
#endif

uint32_t test_firebolt_core_main()
{
    return FireboltSDK::Tests::Main<FireboltSDK::CoreTests>();
}

uint32_t test_properties_get_policy()
{
    const string method = _T("discovery.policy");
    WPEFramework::Core::ProxyType<FireboltSDK::Policy> response;
    uint32_t status = FireboltSDK::Properties::Get(method, response);

    EXPECT_EQ(status, FireboltSDK::Error::None);
    if (status == FireboltSDK::Error::None) {
        printf("\nEnableRecommendations : %d", response->EnableRecommendations.Value());
        printf("\nShareWatchHistory : %d", response->ShareWatchHistory.Value());
        printf("\nRememberWatchedPrograms : %d", response->RememberWatchedPrograms.Value());
    } else {
        printf("\nGet %s status = %d\n", method.c_str(), status);
    }

    return status;
}

#ifdef __cplusplus
}
#endif
