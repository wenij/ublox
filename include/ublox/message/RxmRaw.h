//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

/// @file
/// @brief Contains definition of RXM-RAW message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-RAW message fields.
/// @see RxmRaw
struct RxmRawFields
{
    /// @brief Use this enumeration to access member fields of @ref block bundle.
    enum
    {
        block_cpMes, ///< index of @ref cpMes member field
        block_prMes, ///< index of @ref prMes member field
        block_doMes, ///< index of @ref doMes member field
        block_sv, ///< index of @ref sv member field
        block_mesQI, ///< index of @ref mesQI member field
        block_cno, ///< index of @ref cno member field
        block_lli, ///< index of @ref lli member field
        block_numOfValues ///< number of available member fields
    };

    /// @brief Definition of "rcvTow" field.
    using rcvTow = field::common::I4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "week" field.
    using week = field::rxm::week;

    /// @brief Definition of "numSV" field.
    using numSV = field::rxm::numSV;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "cpMes" field.
    using cpMes = field::common::R8;

    /// @brief Definition of "prMes" field.
    using prMes = field::common::R8;

    /// @brief Definition of "doMes" field.
    using doMes = field::common::R4;

    /// @brief Definition of "sv" field.
    using sv = field::common::U1;

    /// @brief Definition of "mesQI" field.
    using mesQI = field::common::I1;

    /// @brief Definition of "cno" field.
    using cno = field::common::I1;

    /// @brief Definition of "lli" field.
    using lli = field::common::U1;

    /// @brief Definition of a single block of @ref data
    using block =
        field::common::BundleT<
            std::tuple<
                cpMes,
                prMes,
                doMes,
                sv,
                mesQI,
                cno,
                lli
            >
        >;

    /// @brief Definition of the list of blocks (@ref block)
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        rcvTow,
        week,
        numSV,
        reserved1,
        data
    >;
};

/// @brief Definition of RXM-RAW message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmRawFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmRaw : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RAW>,
        comms::option::FieldsImpl<RxmRawFields::All>,
        comms::option::MsgType<RxmRaw<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RAW>,
        comms::option::FieldsImpl<RxmRawFields::All>,
        comms::option::MsgType<RxmRaw<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_rcvTow, ///< @b rcvTow field, see @ref RxmRawFields::rcvTow
        FieldIdx_week, ///< @b week field, see @ref RxmRawFields::week
        FieldIdx_numSV, ///< @b numSV field, see @ref RxmRawFields::numSV
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref RxmRawFields::reserved1
        FieldIdx_data, ///< @b data field, see @ref RxmRawFields::data
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        RxmRawFields::rcvTow& rcvTow; ///< @b rcvTow field, see @ref RxmRawFields::rcvTow
        RxmRawFields::week& week; ///< @b week field, see @ref RxmRawFields::week
        RxmRawFields::numSV& numSV; ///< @b numSV field, see @ref RxmRawFields::numSV
        RxmRawFields::reserved1& reserved1; ///< @b reserved1 field, see @ref RxmRawFields::reserved1
        RxmRawFields::data& data; ///< @b data field, see @ref RxmRawFields::data
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const RxmRawFields::rcvTow& rcvTow; ///< @b rcvTow field, see @ref RxmRawFields::rcvTow
        const RxmRawFields::week& week; ///< @b week field, see @ref RxmRawFields::week
        const RxmRawFields::numSV& numSV; ///< @b numSV field, see @ref RxmRawFields::numSV
        const RxmRawFields::reserved1& reserved1; ///< @b reserved1 field, see @ref RxmRawFields::reserved1
        const RxmRawFields::data& data; ///< @b data field, see @ref RxmRawFields::data
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, rcvTow, week, numSV, reserved1, data);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY


    /// @brief Default constructor
    RxmRaw() = default;

    /// @brief Copy constructor
    RxmRaw(const RxmRaw&) = default;

    /// @brief Move constructor
    RxmRaw(RxmRaw&& other) = default;

    /// @brief Destructor
    virtual ~RxmRaw() = default;

    /// @brief Copy assignment
    RxmRaw& operator=(const RxmRaw&) = default;

    /// @brief Move assignment
    RxmRaw& operator=(RxmRaw&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref RxmRawFields::data) list
    ///     is determined by the value of @b numSV (@ref RxmRawFields::numSV) field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& numSvField = std::get<FieldIdx_numSV>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(numSvField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numSV (@ref RxmRawFields::numSV) field is determined
    ///     by the amount of blocks stored in @b data (@ref RxmRawFields::data) list.
    /// @return @b true in case the value of "numSV" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& numSvField = std::get<FieldIdx_numSV>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (numSvField.value() == dataField.value().size()) {
            return false;
        }

        numSvField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





