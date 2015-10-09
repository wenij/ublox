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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

using AidAlmField_svid = field::aid::svid_ext;
using AidAlmField_week = field::common::U4;
using AidAlmField_dwrd =
    comms::field::Optional<
        comms::field::ArrayList<
            field::common::FieldBase,
            field::common::U4,
            comms::option::SequenceFixedSize<8>
        >
    >;

using AidAlmFields = std::tuple<
    AidAlmField_svid,
    AidAlmField_week,
    AidAlmField_dwrd
>;

template <typename TMsgBase = Message>
class AidAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmFields>,
        comms::option::DispatchImpl<AidAlm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmFields>,
        comms::option::DispatchImpl<AidAlm<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_svid,
        FieldIdx_week,
        FieldIdx_dwrd,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    AidAlm()
    {
        auto& allFields = Base::fields();
        auto& dataField = std::get<FieldIdx_dwrd>(allFields);
        dataField.setMode(comms::field::OptionalMode::Missing);
    }
    AidAlm(const AidAlm&) = default;
    AidAlm(AidAlm&& other) = default;
    virtual ~AidAlm() = default;

    AidAlm& operator=(const AidAlm&) = default;
    AidAlm& operator=(AidAlm&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_dwrd>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& weekField = std::get<FieldIdx_week>(allFields);
        auto dataMode = comms::field::OptionalMode::Exists;
        if (weekField.value() == 0U) {
            dataMode = comms::field::OptionalMode::Missing;
        }

        auto& dataField = std::get<FieldIdx_dwrd>(allFields);
        dataField.setMode(dataMode);
        return Base::template readFieldsFrom<FieldIdx_dwrd>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& weekField = std::get<FieldIdx_week>(allFields);
        auto expectedMode = comms::field::OptionalMode::Exists;
        if (weekField.value() == 0U) {
            expectedMode = comms::field::OptionalMode::Missing;
        }

        auto& dataField = std::get<FieldIdx_dwrd>(allFields);
        if (dataField.getMode() == expectedMode) {
            return false;
        }

        dataField.setMode(expectedMode);
        return true;
    }

};


}  // namespace message

}  // namespace ublox




