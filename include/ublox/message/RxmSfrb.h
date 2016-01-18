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

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

using RxmSfrbField_chn = field::common::U1;
using RxmSfrbField_svid = field::rxm::svid;
using RxmSfrbField_dword =
    field::common::ListT<
        field::common::U4,
        comms::option::SequenceFixedSize<10>
    >;

using RxmSfrbFields = std::tuple<
    RxmSfrbField_chn,
    RxmSfrbField_svid,
    RxmSfrbField_dword
>;

template <typename TMsgBase = Message>
class RxmSfrb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SFRB>,
        comms::option::FieldsImpl<RxmSfrbFields>,
        comms::option::DispatchImpl<RxmSfrb<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SFRB>,
        comms::option::FieldsImpl<RxmSfrbFields>,
        comms::option::DispatchImpl<RxmSfrb<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_chn,
        FieldIdx_svid,
        FieldIdx_dwrd,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    RxmSfrb() = default;

    /// @brief Copy constructor
    RxmSfrb(const RxmSfrb&) = default;

    /// @brief Move constructor
    RxmSfrb(RxmSfrb&& other) = default;

    /// @brief Destructor
    virtual ~RxmSfrb() = default;

    /// @brief Copy assignment
    RxmSfrb& operator=(const RxmSfrb&) = default;

    /// @brief Move assignment
    RxmSfrb& operator=(RxmSfrb&&) = default;

};


}  // namespace message

}  // namespace ublox





