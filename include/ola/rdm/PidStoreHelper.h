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
 * PidStoreHelper.h
 * Provides helper methods for loading / accessing the pid store, and dealing
 * with pids.
 * Copyright (C) 2011 Simon Newton
 */

/**
 * @addtogroup rdm_pids
 * @{
 * @file PidStoreHelper.h
 * @brief Provices helper methods for loading / accessing the pid store, and
 * dealing with pids.
 * @}
 */

#ifndef INCLUDE_OLA_RDM_PIDSTOREHELPER_H_
#define INCLUDE_OLA_RDM_PIDSTOREHELPER_H_

#include <stdint.h>
#include <ola/messaging/Descriptor.h>
#include <ola/messaging/SchemaPrinter.h>
#include <ola/rdm/MessageDeserializer.h>
#include <ola/rdm/MessageSerializer.h>
#include <ola/rdm/PidStore.h>
#include <ola/rdm/RDMMessagePrinters.h>
#include <ola/rdm/StringMessageBuilder.h>

#include <string>
#include <vector>


namespace ola {
namespace rdm {

using std::string;
using std::vector;


class PidStoreHelper {
  public:
    explicit PidStoreHelper(const string &pid_location,
                            unsigned int initial_indent = 0);
    ~PidStoreHelper();

    bool Init();

    const ola::rdm::PidDescriptor *GetDescriptor(
        const string &pid_name,
        uint16_t manufacturer_id) const;
    const ola::rdm::PidDescriptor *GetDescriptor(
        uint16_t param_id,
        uint16_t manufacturer_id) const;

    const ola::messaging::Message *BuildMessage(
        const ola::messaging::Descriptor *descriptor,
        const vector<string> &inputs);

    const uint8_t *SerializeMessage(const ola::messaging::Message *message,
                                    unsigned int *data_length);

    const ola::messaging::Message *DeserializeMessage(
        const ola::messaging::Descriptor *descriptor,
        const uint8_t *data,
        unsigned int data_length);

    const string MessageToString(const ola::messaging::Message *message);

    const string PrettyPrintMessage(
        uint16_t manufacturer_id,
        bool is_set,
        uint16_t pid,
        const ola::messaging::Message *message);

    const string SchemaAsString(const ola::messaging::Descriptor *descriptor);

    void SupportedPids(uint16_t manufacturer_id,
                       vector<string> *pid_names) const;

    void SupportedPids(
        uint16_t manufacturer_id,
        vector<const ola::rdm::PidDescriptor*> *descriptors) const;

  private:
    const string m_pid_location;
    const ola::rdm::RootPidStore *m_root_store;
    ola::rdm::StringMessageBuilder m_string_builder;
    ola::rdm::MessageSerializer m_serializer;
    ola::rdm::MessageDeserializer m_deserializer;
    ola::rdm::RDMMessagePrinter m_message_printer;
    ola::messaging::SchemaPrinter m_schema_printer;
};
}  // namespace rdm
}  // namespace ola
#endif  // INCLUDE_OLA_RDM_PIDSTOREHELPER_H_
