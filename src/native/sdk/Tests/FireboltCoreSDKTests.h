#pragma once
#include <FireboltSDKTests.h>

namespace FireboltSDK {
    class Policy : public WPEFramework::Core::JSON::Container {
    public:
        Policy(const Policy& copy) = delete;
        Policy()
            : WPEFramework::Core::JSON::Container()
            , EnableRecommendations(false)
            , ShareWatchHistory(false)
            , RememberWatchedPrograms(false)
        {
            Add(_T("enableRecommendations"), &EnableRecommendations);
            Add(_T("shareWatchHistory"), &ShareWatchHistory);
            Add(_T("rememberWatchedPrograms"), &RememberWatchedPrograms);
        }
        Policy& operator=(const Policy& RHS)
        {
           EnableRecommendations = RHS.EnableRecommendations;
           ShareWatchHistory = RHS.ShareWatchHistory;
           RememberWatchedPrograms = RHS.RememberWatchedPrograms;

           return (*this);
        }

       ~Policy() override = default;

    public:
        WPEFramework::Core::JSON::Boolean EnableRecommendations;
        WPEFramework::Core::JSON::Boolean ShareWatchHistory;
        WPEFramework::Core::JSON::Boolean RememberWatchedPrograms;
    };

    class CoreTests : public Tests {

    public:
        CoreTests();
        ~CoreTests() override = default;

        static uint32_t GetDiscoveryPolicy();
    };
}
