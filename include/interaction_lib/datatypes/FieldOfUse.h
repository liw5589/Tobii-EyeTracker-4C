/*
COPYRIGHT 2018-2020  - PROPERTY OF TOBII AB
-------------------------------------
2018-2020 TOBII AB - KARLSROVAGEN 2D, DANDERYD 182 53, SWEDEN - All Rights Reserved.

NOTICE:  All information contained herein is, and remains, the property of Tobii AB and its suppliers, if any.
The intellectual and technical concepts contained herein are proprietary to Tobii AB and its suppliers and may be
covered by U.S.and Foreign Patents, patent applications, and are protected by trade secret or copyright law.
Dissemination of this information or reproduction of this material is strictly forbidden unless prior written
permission is obtained from Tobii AB.
*/

#pragma once

#ifdef __cplusplus
#include "../api/CallSignature.h"
#endif

typedef enum IL_FieldOfUse
{
    IL_FieldOfUse_Interactive = 1,
    IL_FieldOfUse_Analytical = 2
} IL_FieldOfUse;

#ifdef __cplusplus

namespace IL
{
    enum class FieldOfUse
    {
        Interactive = ::IL_FieldOfUse_Interactive,
        Analytical = ::IL_FieldOfUse_Analytical
    };
}

IL_API extern bool operator==(const IL_FieldOfUse& lhs, const IL::FieldOfUse& rhs);
IL_API bool operator==(const IL::FieldOfUse& lhs, const IL_FieldOfUse& rhs);

#endif
