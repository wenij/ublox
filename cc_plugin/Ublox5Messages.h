//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include <tuple>
#include "cc_plugin/Message.h"

#include "cc_plugin/message/NavPosecef.h"
#include "cc_plugin/message/NavPosecefPoll.h"
#include "cc_plugin/message/NavPosllh.h"
#include "cc_plugin/message/NavPosllhPoll.h"
#include "cc_plugin/message/NavStatus.h"
#include "cc_plugin/message/NavStatusPoll.h"
#include "cc_plugin/message/NavDop.h"
#include "cc_plugin/message/NavDopPoll.h"
#include "cc_plugin/message/NavSol.h"
#include "cc_plugin/message/NavSolPoll.h"
#include "cc_plugin/message/NavVelecef.h"
#include "cc_plugin/message/NavVelecefPoll.h"
#include "cc_plugin/message/NavVelned.h"
#include "cc_plugin/message/NavVelnedPoll.h"
#include "cc_plugin/message/NavTimegps.h"
#include "cc_plugin/message/NavTimegpsPoll.h"
#include "cc_plugin/message/NavTimeutc.h"
#include "cc_plugin/message/NavTimeutcPoll.h"
#include "cc_plugin/message/NavClock.h"
#include "cc_plugin/message/NavClockPoll.h"
#include "cc_plugin/message/NavSvinfo.h"
#include "cc_plugin/message/NavSvinfoPoll.h"
#include "cc_plugin/message/NavSbas.h"
#include "cc_plugin/message/NavSbasPoll.h"

#include "cc_plugin/message/RxmSvsi.h"
#include "cc_plugin/message/RxmSvsiPoll.h"

#include "cc_plugin/message/InfError.h"
#include "cc_plugin/message/InfWarning.h"
#include "cc_plugin/message/InfNotice.h"
#include "cc_plugin/message/InfTest.h"
#include "cc_plugin/message/InfDebug.h"

#include "cc_plugin/message/AckNak.h"
#include "cc_plugin/message/AckAck.h"

#include "cc_plugin/message/CfgPrtUart.h"
#include "cc_plugin/message/CfgPrtUsb.h"
#include "cc_plugin/message/CfgPrtSpi.h"
#include "cc_plugin/message/CfgPrtDdc.h"
#include "cc_plugin/message/CfgPrtPollPort.h"
#include "cc_plugin/message/CfgPrtPoll.h"
#include "cc_plugin/message/CfgMsg.h"
#include "cc_plugin/message/CfgMsgCurrent.h"
#include "cc_plugin/message/CfgMsgPoll.h"
#include "cc_plugin/message/CfgInf.h"
#include "cc_plugin/message/CfgInfPoll.h"
#include "cc_plugin/message/CfgRst.h"
#include "cc_plugin/message/CfgDat.h"
#include "cc_plugin/message/CfgDatUser.h"
#include "cc_plugin/message/CfgDatStandard.h"
#include "cc_plugin/message/CfgDatPoll.h"
#include "cc_plugin/message/CfgTp.h"
#include "cc_plugin/message/CfgTpPoll.h"
#include "cc_plugin/message/CfgRate.h"
#include "cc_plugin/message/CfgRatePoll.h"
#include "cc_plugin/message/CfgCfg.h"
#include "cc_plugin/message/CfgRxm.h"
#include "cc_plugin/message/CfgRxmPoll.h"
#include "cc_plugin/message/CfgAnt.h"
#include "cc_plugin/message/CfgAntPoll.h"
#include "cc_plugin/message/CfgSbas.h"
#include "cc_plugin/message/CfgSbasPoll.h"
#include "cc_plugin/message/CfgNmea.h"
#include "cc_plugin/message/CfgNmeaPoll.h"
#include "cc_plugin/message/CfgUsb.h"
#include "cc_plugin/message/CfgUsbPoll.h"
#include "cc_plugin/message/CfgTmode.h"
#include "cc_plugin/message/CfgTmodePoll.h"
#include "cc_plugin/message/CfgNavx5.h"
#include "cc_plugin/message/CfgNavx5Poll.h"
#include "cc_plugin/message/CfgNav5.h"
#include "cc_plugin/message/CfgNav5Poll.h"

#include "cc_plugin/message/MonIo.h"
#include "cc_plugin/message/MonIoPoll.h"
#include "cc_plugin/message/MonVer.h"
#include "cc_plugin/message/MonVerPoll.h"
#include "cc_plugin/message/MonMsgpp.h"
#include "cc_plugin/message/MonMsgppPoll.h"
#include "cc_plugin/message/MonRxbuf.h"
#include "cc_plugin/message/MonRxbufPoll.h"
#include "cc_plugin/message/MonTxbuf.h"
#include "cc_plugin/message/MonTxbufPoll.h"
#include "cc_plugin/message/MonHw.h"
#include "cc_plugin/message/MonHwPoll.h"

#include "cc_plugin/message/AidReq.h"
#include "cc_plugin/message/AidIni.h"
#include "cc_plugin/message/AidIniPoll.h"
#include "cc_plugin/message/AidHui.h"
#include "cc_plugin/message/AidHuiPoll.h"
#include "cc_plugin/message/AidData.h"
#include "cc_plugin/message/AidAlm.h"
#include "cc_plugin/message/AidAlmPollSv.h"
#include "cc_plugin/message/AidAlmPoll.h"
#include "cc_plugin/message/AidEph.h"
#include "cc_plugin/message/AidEphPollSv.h"
#include "cc_plugin/message/AidEphPoll.h"
#include "cc_plugin/message/AidAlpsrv.h"
#include "cc_plugin/message/AidAlpsrvUpdate.h"
#include "cc_plugin/message/AidAlp.h"
#include "cc_plugin/message/AidAlpStatus.h"
#include "cc_plugin/message/AidAlpData.h"

#include "cc_plugin/message/TimTp.h"
#include "cc_plugin/message/TimTpPoll.h"
#include "cc_plugin/message/TimTm2.h"
#include "cc_plugin/message/TimTm2Poll.h"
#include "cc_plugin/message/TimSvin.h"
#include "cc_plugin/message/TimSvinPoll.h"

namespace ublox
{

namespace cc_plugin
{

using Ublox5Messages = std::tuple<
    cc_plugin::message::NavPosecef,
    cc_plugin::message::NavPosecefPoll,
    cc_plugin::message::NavPosllh,
    cc_plugin::message::NavPosllhPoll,
    cc_plugin::message::NavStatus,
    cc_plugin::message::NavStatusPoll,
    cc_plugin::message::NavDop,
    cc_plugin::message::NavDopPoll,
    cc_plugin::message::NavSol,
    cc_plugin::message::NavSolPoll,
    cc_plugin::message::NavVelecef,
    cc_plugin::message::NavVelecefPoll,
    cc_plugin::message::NavVelned,
    cc_plugin::message::NavVelnedPoll,
    cc_plugin::message::NavTimegps,
    cc_plugin::message::NavTimegpsPoll,
    cc_plugin::message::NavTimeutc,
    cc_plugin::message::NavTimeutcPoll,
    cc_plugin::message::NavClock,
    cc_plugin::message::NavClockPoll,
    cc_plugin::message::NavSvinfo,
    cc_plugin::message::NavSvinfoPoll,
    cc_plugin::message::NavSbas,
    cc_plugin::message::NavSbasPoll,
    cc_plugin::message::RxmSvsi,
    cc_plugin::message::RxmSvsiPoll,
    cc_plugin::message::InfError,
    cc_plugin::message::InfWarning,
    cc_plugin::message::InfNotice,
    cc_plugin::message::InfTest,
    cc_plugin::message::InfDebug,
    cc_plugin::message::AckNak,
    cc_plugin::message::AckAck,
    cc_plugin::message::CfgPrtUart,
    cc_plugin::message::CfgPrtUsb,
    cc_plugin::message::CfgPrtSpi,
    cc_plugin::message::CfgPrtDdc,
    cc_plugin::message::CfgPrtPollPort,
    cc_plugin::message::CfgPrtPoll,
    cc_plugin::message::CfgMsg,
    cc_plugin::message::CfgMsgCurrent,
    cc_plugin::message::CfgMsgPoll,
    cc_plugin::message::CfgInf,
    cc_plugin::message::CfgInfPoll,
    cc_plugin::message::CfgRst,
    cc_plugin::message::CfgDat,
    cc_plugin::message::CfgDatUser,
    cc_plugin::message::CfgDatStandard,
    cc_plugin::message::CfgDatPoll,
    cc_plugin::message::CfgTp,
    cc_plugin::message::CfgTpPoll,
    cc_plugin::message::CfgRate,
    cc_plugin::message::CfgRatePoll,
    cc_plugin::message::CfgCfg,
    cc_plugin::message::CfgRxm,
    cc_plugin::message::CfgRxmPoll,
    cc_plugin::message::CfgAnt,
    cc_plugin::message::CfgAntPoll,
    cc_plugin::message::CfgSbas,
    cc_plugin::message::CfgSbasPoll,
    cc_plugin::message::CfgNmea,
    cc_plugin::message::CfgNmeaPoll,
    cc_plugin::message::CfgUsb,
    cc_plugin::message::CfgUsbPoll,
    cc_plugin::message::CfgTmode,
    cc_plugin::message::CfgTmodePoll,
    cc_plugin::message::CfgNavx5,
    cc_plugin::message::CfgNavx5Poll,
    cc_plugin::message::CfgNav5,
    cc_plugin::message::CfgNav5Poll,
    cc_plugin::message::MonIo,
    cc_plugin::message::MonIoPoll,
    cc_plugin::message::MonVer,
    cc_plugin::message::MonVerPoll,
    cc_plugin::message::MonMsgpp,
    cc_plugin::message::MonMsgppPoll,
    cc_plugin::message::MonRxbuf,
    cc_plugin::message::MonRxbufPoll,
    cc_plugin::message::MonTxbuf,
    cc_plugin::message::MonTxbufPoll,
    cc_plugin::message::MonHw,
    cc_plugin::message::MonHwPoll,
    cc_plugin::message::AidReq,
    cc_plugin::message::AidIni,
    cc_plugin::message::AidIniPoll,
    cc_plugin::message::AidHui,
    cc_plugin::message::AidHuiPoll,
    cc_plugin::message::AidData,
    cc_plugin::message::AidAlm,
    cc_plugin::message::AidAlmPollSv,
    cc_plugin::message::AidAlmPoll,
    cc_plugin::message::AidEph,
    cc_plugin::message::AidEphPollSv,
    cc_plugin::message::AidEphPoll,
    cc_plugin::message::AidAlpsrv,
    cc_plugin::message::AidAlpsrvUpdate,
    cc_plugin::message::AidAlp,
    cc_plugin::message::AidAlpStatus,
    cc_plugin::message::AidAlpData,
    cc_plugin::message::TimTp,
    cc_plugin::message::TimTpPoll,
    cc_plugin::message::TimTm2,
    cc_plugin::message::TimTm2Poll,
    cc_plugin::message::TimSvin,
    cc_plugin::message::TimSvinPoll
>;

}  // namespace cc_plugin

}  // namespace ublox





