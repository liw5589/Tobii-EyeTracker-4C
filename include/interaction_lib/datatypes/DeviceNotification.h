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

typedef enum IL_DeviceNotification
{
    IL_DeviceNotification_None = 0,
    IL_DeviceNotification_UpdatedStreamsAvailable = 1,
    IL_DeviceNotification_UpdatedConfig = 2
} IL_DeviceNotification;

#ifdef __cplusplus
namespace IL
{
    enum class DeviceNotification
    {
        None = ::IL_DeviceNotification_None,
        UpdatedStreamsAvailable = ::IL_DeviceNotification_UpdatedStreamsAvailable,
        UpdatedConfig = ::IL_DeviceNotification_UpdatedConfig
    };
}
#endif