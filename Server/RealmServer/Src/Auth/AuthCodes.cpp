#include "AuthCodes.h"

namespace AuthHelper
{
     bool GetAcceptedClientBuilds(uint32 clientBuild)
    {
        uint32 accept0 = CL_ACCEPTED_CLIENT_BUILD;
        uint32 accept1 = BC_ACCEPTED_CLIENT_BUILD;
        uint32 accept2 = LK_ACCEPTED_CLIENT_BUILD;
        uint32 accept3 = CT_ACCEPTED_CLIENT_BUILD || LT_ACCEPTED_CLIENT_BUILD;

        bool isAcceptedBuild = accept0 || accept1 || accept2 || accept3;
        if (isAcceptedBuild)
            return true;

        return false;
    }

    bool IsAcceptedClientBuild(uint32 clientBuild)
    {
        return GetAcceptedClientBuilds(clientBuild);
    }
};
