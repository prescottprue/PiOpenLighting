/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * RDMHelper.h
 * Various misc RDM functions.
 * Copyright (C) 2005-2010 Simon Newton
 */

/**
 * @addtogroup rdm_helpers
 * @{
 * @file RDMHelper.h
 * @brief Various misc RDM functions
 * @}
 */

#ifndef INCLUDE_OLA_RDM_RDMHELPER_H_
#define INCLUDE_OLA_RDM_RDMHELPER_H_

#include <stdint.h>
#include <ola/rdm/RDMEnums.h>
#include <ola/rdm/RDMResponseCodes.h>
#include <string>

namespace ola {
namespace rdm {

using std::string;

string ResponseCodeToString(rdm_response_code status);

string DataTypeToString(uint8_t type);
string LampModeToString(uint8_t lamp_mode);
string LampStateToString(uint8_t lamp_state);
string NackReasonToString(uint16_t reason);
string PowerStateToString(uint8_t power_state);
bool UIntToPowerState(uint8_t state, rdm_power_state *power_state);
string PrefixToString(uint8_t prefix);
string ProductCategoryToString(uint16_t category);
string ProductDetailToString(uint16_t detail);
string ResetDeviceToString(uint8_t reset_device);
bool UIntToResetDevice(uint8_t state, rdm_reset_device_mode *reset_device);
string SensorTypeToString(uint8_t type);
string SensorSupportsRecordingToString(uint8_t supports_recording);
string SlotInfoToString(uint8_t slot_type, uint16_t slot_label);
string StatusMessageIdToString(uint16_t message_id,
                               int16_t data1,
                               int16_t data2);
string StatusTypeToString(uint8_t status_type);
string UnitToString(uint8_t unit);
}  // namespace rdm
}  // namespace ola
#endif  // INCLUDE_OLA_RDM_RDMHELPER_H_
