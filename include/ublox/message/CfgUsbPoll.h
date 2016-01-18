//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"

namespace ublox
{

namespace message
{

using CfgUsbPollFields = std::tuple<>;

template <typename TMsgBase = Message>
class CfgUsbPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_USB>,
        comms::option::FieldsImpl<CfgUsbPollFields>,
        comms::option::DispatchImpl<CfgUsbPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_USB>,
        comms::option::FieldsImpl<CfgUsbPollFields>,
        comms::option::DispatchImpl<CfgUsbPoll<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgUsbPoll() = default;

    /// @brief Copy constructor
    CfgUsbPoll(const CfgUsbPoll&) = default;

    /// @brief Move constructor
    CfgUsbPoll(CfgUsbPoll&& other) = default;

    /// @brief Destructor
    virtual ~CfgUsbPoll() = default;

    /// @brief Copy assignment
    CfgUsbPoll& operator=(const CfgUsbPoll&) = default;

    /// @brief Move assignment
    CfgUsbPoll& operator=(CfgUsbPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

