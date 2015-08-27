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

#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgMsgFields = std::tuple<
    comms::field::ArrayList<
        ublox::field::common::FieldBase,
        comms::field::Bundle<
            std::tuple<
                ublox::field::MsgId,
                ublox::field::cfg::Rate,
                ublox::field::cfg::Rate,
                ublox::field::cfg::Rate,
                ublox::field::cfg::Rate
            >
        >
    >
>;


template <typename TMsgBase = Message>
class CfgMsg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgFields>,
        comms::option::DispatchImpl<CfgMsg<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgFields>,
        comms::option::DispatchImpl<CfgMsg<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_List,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgMsg() = default;
    CfgMsg(const CfgMsg&) = default;
    CfgMsg(CfgMsg&& other) = default;
    virtual ~CfgMsg() = default;

    CfgMsg& operator=(const CfgMsg&) = default;
    CfgMsg& operator=(CfgMsg&&) = default;
};


}  // namespace message

}  // namespace ublox
