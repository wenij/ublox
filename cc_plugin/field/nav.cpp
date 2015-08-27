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

#include "nav.h"

#include "comms_champion/comms_champion.h"
#include "ublox/field/nav.h"
#include "common.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace nav
{

namespace
{

QVariantMap createProps_ecef(const char* dir)
{
    return cc::Property::createPropertiesMap(QString("ecef%1").arg(dir));
}

QVariantMap createProps_gpsFix()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "no fix");
    cc::Property::appendEnumValue(enumValues, "dead reckoning only");
    cc::Property::appendEnumValue(enumValues, "2D-fix");
    cc::Property::appendEnumValue(enumValues, "3D-fix");
    cc::Property::appendEnumValue(enumValues, "GPS + dead reckoning combined");
    cc::Property::appendEnumValue(enumValues, "time only fix");

    return cc::Property::createPropertiesMap("gpsFix", std::move(enumValues));
}

QVariantMap createProps_lon()
{
    auto props = cc::Property::createPropertiesMap("lon");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 7);
    return props;
}

QVariantMap createProps_lat()
{
    auto props = cc::Property::createPropertiesMap("lat");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 7);
    return props;
}

QVariantMap createProps_heading()
{
    auto props = cc::Property::createPropertiesMap("heading");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 5);
    return props;
}


// TODO: remove

QVariantMap createNameOnlyProperties(const char* name)
{
    return cc::Property::createPropertiesMap(name);
}

QVariantMap createEcefProperties(const char* dir)
{
    return cc::Property::createPropertiesMap(QString("ECEF%1").arg(dir));
}

QVariantMap createHemProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "North");
    cc::Property::appendEnumValue(enumValues, "South");
    return cc::Property::createPropertiesMap("HEM", std::move(enumValues));
}

QVariantMap createDopProperties(char letter)
{
    static const QString Suffix("DOP");
    QString str(letter);
    str.append(Suffix);
    return cc::Property::createPropertiesMap(str);
}

QVariantMap createGpsFixProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "no fix");
    cc::Property::appendEnumValue(enumValues, "dead reckoning only");
    cc::Property::appendEnumValue(enumValues, "2D-fix");
    cc::Property::appendEnumValue(enumValues, "3D-fix");
    cc::Property::appendEnumValue(enumValues, "GPS + dead reckoning combined");
    cc::Property::appendEnumValue(enumValues, "time only fix");

    return cc::Property::createPropertiesMap("GPSfix", std::move(enumValues));
}

QVariantMap createFlagsProperties()
{
    QVariantList bitNames;
    bitNames.append("GPSfixOK");
    bitNames.append("DiffSoln");
    bitNames.append("WKNSET");
    bitNames.append("TOWSET");
    return cc::Property::createPropertiesMap("Flags", std::move(bitNames));
}

QVariantMap createDiffStatusProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "none");
    cc::Property::appendEnumValue(enumValues, "PR+PRR Correction");
    cc::Property::appendEnumValue(enumValues, "PR+PRR+CP Correction");
    cc::Property::appendEnumValue(enumValues, "High accuracy PR+PRR+CP Correction");
    return cc::Property::createPropertiesMap("DiffS", std::move(enumValues));
}

QVariantMap createVelProperties(const char* dir)
{
    QString str("VEL_");
    str.append(QString(dir));
    return cc::Property::createPropertiesMap(str);
}

QVariantMap createTimeValidProperties()
{
    QVariantList bitNames;
    bitNames.append("Valid Time of Week");
    bitNames.append("Valid Week Number");
    bitNames.append("Valid UTC");
    return cc::Property::createPropertiesMap("Valid", std::move(bitNames));
}

QVariantMap createNchProperties()
{
    auto props = cc::Property::createPropertiesMap("NCH");
    cc::Property::setReadOnly(props);
    return props;
}

QVariantMap createInfoFlagsProperties()
{
    QVariantList bitNames;
    bitNames.append("SV is used for navigation");
    bitNames.append("Diff correction data is available");
    bitNames.append("Orbit info is available");
    bitNames.append("Orbit info is Ephemeris");
    bitNames.append("SV is unhealthy");
    return cc::Property::createPropertiesMap("Flags", std::move(bitNames));
}

QVariantMap createQiProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Idle");
    cc::Property::appendEnumValue(enumValues, "Searching");
    cc::Property::appendEnumValue(enumValues, "Searching (2)");
    cc::Property::appendEnumValue(enumValues, "Signal detected, unusable");
    cc::Property::appendEnumValue(enumValues, "Code Lock on Signal");
    cc::Property::appendEnumValue(enumValues, "Code and Carrier locked");
    cc::Property::appendEnumValue(enumValues, "Code and Carrier locked (2)");
    cc::Property::appendEnumValue(enumValues, "Code and Carrier locked, 50bps data");
    return cc::Property::createPropertiesMap("QI", std::move(enumValues));
}

QVariantMap createDgpsStatusProperties()
{
    auto props = createDiffStatusProperties();
    cc::Property::setName(props, "STATUS");
    return props;
}

QVariantMap createDgpsFlagsProperties()
{
    QVariantList bitNames;
    bitNames.append("DGPS is used");
    auto flagsProps = cc::Property::createPropertiesMap("Flags", std::move(bitNames));
    cc::Property::setSerialisedHidden(flagsProps);

    auto chNumProps = chNumProperties();
    cc::Property::setSerialisedHidden(chNumProps);

    QVariantList membersData;
    membersData.append(std::move(chNumProps));
    membersData.append(std::move(flagsProps));
    QVariantMap props;
    cc::Property::setData(props, std::move(membersData));
    return props;
}

QVariantMap createModeProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Disabled", (int)ublox::field::nav::SbasMode::Disabled);
    cc::Property::appendEnumValue(enumValues, "Enabled Integrity", (int)ublox::field::nav::SbasMode::EnabledIntegrity);
    cc::Property::appendEnumValue(enumValues, "Enabled Testmode", (int)ublox::field::nav::SbasMode::EnabledTestmode);
    return cc::Property::createPropertiesMap("MODE", std::move(enumValues));
}

QVariantMap createSysProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Unknown", (int)ublox::field::nav::SbasSys::Unknown);
    cc::Property::appendEnumValue(enumValues, "WAAS", (int)ublox::field::nav::SbasSys::WAAS);
    cc::Property::appendEnumValue(enumValues, "EGNOS", (int)ublox::field::nav::SbasSys::EGNOS);
    cc::Property::appendEnumValue(enumValues, "MSAS", (int)ublox::field::nav::SbasSys::MSAS);
    cc::Property::appendEnumValue(enumValues, "GPS", (int)ublox::field::nav::SbasSys::GPS);
    return cc::Property::createPropertiesMap("SYS", std::move(enumValues));
}

QVariantMap createServiceProperties()
{
    QVariantList bitNames;
    bitNames.append("Ranging");
    bitNames.append("Corrections");
    bitNames.append("Integrity");
    bitNames.append("Testmode");
    return cc::Property::createPropertiesMap("SERVICE", std::move(bitNames));
}

QVariantMap createCntProperties()
{
    auto props = cc::Property::createPropertiesMap("CNT");
    cc::Property::setReadOnly(props);
    return props;
}

QVariantMap createCalibStatusProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "no calibration");
    cc::Property::appendEnumValue(enumValues, "calibrating");
    cc::Property::appendEnumValue(enumValues, "coarse calibration");
    cc::Property::appendEnumValue(enumValues, "fine calibration");

    auto tachoProps = cc::Property::createPropertiesMap("Tacho", QVariant::fromValue(enumValues));
    cc::Property::setSerialisedHidden(tachoProps);
    auto gyroProps = cc::Property::createPropertiesMap("Gyro", QVariant::fromValue(enumValues));
    cc::Property::setSerialisedHidden(gyroProps);
    auto biasGyroProps = cc::Property::createPropertiesMap("Bias Gyro", std::move(enumValues));
    cc::Property::setSerialisedHidden(biasGyroProps);
    QVariantMap notUsedBits;
    cc::Property::setFieldHidden(notUsedBits);

    QVariantList membersData;
    membersData.append(std::move(tachoProps));
    membersData.append(std::move(gyroProps));
    membersData.append(std::move(biasGyroProps));
    membersData.append(std::move(notUsedBits));

    return cc::Property::createPropertiesMap("calib_status", std::move(membersData));
}

QVariantMap createMeasUsedProperties()
{
    QVariantList bitNames;
    bitNames.append("Tacho pulse used");
    bitNames.append("Forward/Backward pulse used");
    bitNames.append("Gyro used");
    bitNames.append("Temperature used");
    bitNames.append("GPS Position used");
    bitNames.append("GPS Velocity used");
    bitNames.append("GYRO sensor inconsistency");
    bitNames.append("Speed pulse sensor inconsistency");

    return cc::Property::createPropertiesMap("meas_used", std::move(bitNames));
}


}  // namespace

const QVariantMap& props_iTOW()
{
    return common::props_iTOW();
}

const QVariantMap& props_fTOW()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("fTOW");
    return Props;
}

const QVariantMap& props_ecefX()
{
    static const QVariantMap Props = createProps_ecef("X");
    return Props;
}

const QVariantMap& props_ecefY()
{
    static const QVariantMap Props = createProps_ecef("Y");
    return Props;
}

const QVariantMap& props_ecefZ()
{
    static const QVariantMap Props = createProps_ecef("Z");
    return Props;
}

const QVariantMap& props_ecefVX()
{
    static const QVariantMap Props = createProps_ecef("VX");
    return Props;
}

const QVariantMap& props_ecefVY()
{
    static const QVariantMap Props = createProps_ecef("VY");
    return Props;
}

const QVariantMap& props_ecefVZ()
{
    static const QVariantMap Props = createProps_ecef("VZ");
    return Props;
}

const QVariantMap& props_pAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("pAcc");
    return Props;
}

const QVariantMap& props_sAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("sAcc");
    return Props;
}

const QVariantMap& props_lon()
{
    static const QVariantMap Props = createProps_lon();
    return Props;
}

const QVariantMap& props_lat()
{
    static const QVariantMap Props = createProps_lat();
    return Props;
}

const QVariantMap& props_height()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("height");
    return Props;
}

const QVariantMap& props_hMSL()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("hMSL");
    return Props;
}

const QVariantMap& props_hAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("hAcc");
    return Props;
}

const QVariantMap& props_vAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("vAcc");
    return Props;
}

const QVariantMap& props_gpsFix()
{
    static const QVariantMap Props = createProps_gpsFix();
    return Props;
}

QVariantMap createProps_xDOP(char prefix)
{
    auto props = cc::Property::createPropertiesMap(QString("%1DOP").arg(prefix));
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 2);
    return props;
}

const QVariantMap& props_pDOP()
{
    static const auto Props = createProps_xDOP('p');
    return Props;
}

const QVariantMap& props_week()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("week");
    return Props;
}

const QVariantMap& props_numSV()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("numSV");
    return Props;
}

const QVariantMap& props_year()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("year");
    return Props;
}

const QVariantMap& props_month()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("month");
    return Props;
}

const QVariantMap& props_day()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("day");
    return Props;
}

const QVariantMap& props_hour()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("hour");
    return Props;
}

const QVariantMap& props_min()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("min");
    return Props;
}

const QVariantMap& props_sec()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("sec");
    return Props;
}

const QVariantMap& props_tAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("tAcc");
    return Props;
}

const QVariantMap& props_nano()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("nano");
    return Props;
}

const QVariantMap& props_gSpeed()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("gSpeed");
    return Props;
}

const QVariantMap& props_heading()
{
    static const QVariantMap Props = createProps_heading();
    return Props;
}

// TODO: remove
const QVariantMap& itowProperties()
{
    return common::itowProperties();
}

const QVariantMap& ecefPropertiesX()
{
    static const QVariantMap Props = createEcefProperties("_X");
    return Props;
}

const QVariantMap& ecefPropertiesY()
{
    static const QVariantMap Props = createEcefProperties("_Y");
    return Props;
}

const QVariantMap& ecefPropertiesZ()
{
    static const QVariantMap Props = createEcefProperties("_Z");
    return Props;
}

const QVariantMap& ecefPropertiesVX()
{
    static const QVariantMap Props = createEcefProperties("VX");
    return Props;
}

const QVariantMap& ecefPropertiesVY()
{
    static const QVariantMap Props = createEcefProperties("VY");
    return Props;
}

const QVariantMap& ecefPropertiesVZ()
{
    static const QVariantMap Props = createEcefProperties("VZ");
    return Props;
}

const QVariantMap& paccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Pacc");
    return Props;
}

const QVariantMap& lonProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("LON");
    return Props;
}

const QVariantMap& latProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("LAT");
    return Props;
}

const QVariantMap& heightProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("HEIGHT");
    return Props;
}

const QVariantMap& hmslProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("HMSL");
    return Props;
}

const QVariantMap& haccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Hacc");
    return Props;
}

const QVariantMap& vaccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Vacc");
    return Props;
}

const QVariantMap& eastProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("EAST");
    return Props;
}

const QVariantMap& northProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("NORTH");
    return Props;
}

const QVariantMap& altProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("ALT");
    return Props;
}

const QVariantMap& zoneProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("ZONE");
    return Props;
}

const QVariantMap& hemProperties()
{
    static const QVariantMap Props = createHemProperties();
    return Props;
}

const QVariantMap& gdopProperties()
{
    static const QVariantMap Props = createDopProperties('G');
    return Props;
}

const QVariantMap& pdopProperties()
{
    static const QVariantMap Props = createDopProperties('P');
    return Props;
}

const QVariantMap& tdopProperties()
{
    static const QVariantMap Props = createDopProperties('T');
    return Props;
}

const QVariantMap& vdopProperties()
{
    static const QVariantMap Props = createDopProperties('V');
    return Props;
}

const QVariantMap& hdopProperties()
{
    static const QVariantMap Props = createDopProperties('H');
    return Props;
}

const QVariantMap& ndopProperties()
{
    static const QVariantMap Props = createDopProperties('N');
    return Props;
}

const QVariantMap& edopProperties()
{
    static const QVariantMap Props = createDopProperties('E');
    return Props;
}

const QVariantMap& gpsFixProperties()
{
    static const QVariantMap Props = createGpsFixProperties();
    return Props;
}

const QVariantMap& flagsProperties()
{
    static const QVariantMap Props = createFlagsProperties();
    return Props;
}

const QVariantMap& diffStatusProperties()
{
    static const QVariantMap Props = createDiffStatusProperties();
    return Props;
}

const QVariantMap& ttffProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("TTFF");
    return Props;
}

const QVariantMap& msssProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("MSSS");
    return Props;
}

const QVariantMap& fracProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Frac");
    return Props;
}

const QVariantMap& weekProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("week");
    return Props;
}

const QVariantMap& saccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("SAcc");
    return Props;
}

const QVariantMap& numSvProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("numSV");
    return Props;
}

const QVariantMap& velPropertiesN()
{
    static const QVariantMap Props = createVelProperties("N");
    return Props;
}

const QVariantMap& velPropertiesE()
{
    static const QVariantMap Props = createVelProperties("E");
    return Props;
}

const QVariantMap& velPropertiesD()
{
    static const QVariantMap Props = createVelProperties("D");
    return Props;
}

const QVariantMap& speedProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Speed");
    return Props;
}

const QVariantMap& groundSpeedProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("GSpeed");
    return Props;
}

const QVariantMap& headingProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Heading");
    return Props;
}

const QVariantMap& caccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CAcc");
    return Props;
}

const QVariantMap& leapSecProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("LeapS");
    return Props;
}

const QVariantMap& timeValidProperties()
{
    static const QVariantMap Props = createTimeValidProperties();
    return Props;
}

const QVariantMap& taccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("TAcc");
    return Props;
}

const QVariantMap& nanoProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Nano");
    return Props;
}

const QVariantMap& yearProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Year");
    return Props;
}

const QVariantMap& monthProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Month");
    return Props;
}

const QVariantMap& dayProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Day");
    return Props;
}

const QVariantMap& hourProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Hour");
    return Props;
}

const QVariantMap& minProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Min");
    return Props;
}

const QVariantMap& secProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Sec");
    return Props;
}

const QVariantMap& clkbProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CLKB");
    return Props;
}

const QVariantMap& clkdProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CLKD");
    return Props;
}

const QVariantMap& faccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("FAcc");
    return Props;
}

const QVariantMap& nchProperties()
{
    static const QVariantMap Props = createNchProperties();
    return Props;
}

const QVariantMap& svidProperties()
{
    return common::svidProperties();
}

const QVariantMap& chNumProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("chn");
    return Props;
}

const QVariantMap& infoFlagsProperties()
{
    static const QVariantMap Props = createInfoFlagsProperties();
    return Props;
}

const QVariantMap& qiProperties()
{
    static const QVariantMap Props = createQiProperties();
    return Props;
}

const QVariantMap& cnoProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CNO");
    return Props;
}

const QVariantMap& elevProperties()
{
    return common::elevProperties();
}

const QVariantMap& azimProperties()
{
    return common::azimProperties();
}

const QVariantMap& prresProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("PRRes");
    return Props;
}

const QVariantMap& ageProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("AGE");
    return Props;
}

const QVariantMap& baseIdProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("BASEID");
    return Props;
}

const QVariantMap& baseHealthProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("BASEHLTH");
    return Props;
}

const QVariantMap& dgpsStatusProperties()
{
    static const QVariantMap Props = createDgpsStatusProperties();
    return Props;
}

const QVariantMap& dgpsFlagsProperties()
{
    static const QVariantMap Props = createDgpsFlagsProperties();
    return Props;
}

const QVariantMap& agechProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("AGECH");
    return Props;
}

const QVariantMap& prcProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("PRC");
    return Props;
}

const QVariantMap& prrcProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("PRRC");
    return Props;
}

const QVariantMap& geoProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("GEO");
    return Props;
}

const QVariantMap& modeProperties()
{
    static const QVariantMap Props = createModeProperties();
    return Props;
}

const QVariantMap& sysProperties()
{
    static const QVariantMap Props = createSysProperties();
    return Props;
}

const QVariantMap& serviceProperties()
{
    static const QVariantMap Props = createServiceProperties();
    return Props;
}

const QVariantMap& cntProperties()
{
    static const QVariantMap Props = createCntProperties();
    return Props;
}

const QVariantMap& udreProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("UDRE");
    return Props;
}

const QVariantMap& icProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("IC");
    return Props;
}

const QVariantMap& pulsesProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("pulses");
    return Props;
}

const QVariantMap& periodProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("period");
    return Props;
}

const QVariantMap& gyromeanProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("gyromean");
    return Props;
}

const QVariantMap& temperatureProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("temperature");
    return Props;
}

const QVariantMap& directionProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("direction");
    return Props;
}

const QVariantMap& calibStatusProperties()
{
    static const QVariantMap Props = createCalibStatusProperties();
    return Props;
}

const QVariantMap& pulseScaleProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("pulse_scale");
    return Props;
}

const QVariantMap& gyroBiasProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("gyro_bias");
    return Props;
}

const QVariantMap& gyroScaleProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("gyro_scale");
    return Props;
}

const QVariantMap& accPulseScaleProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("acc_pulse_scale");
    return Props;
}

const QVariantMap& accGyroBiasProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("acc_gyro_bias");
    return Props;
}

const QVariantMap& accGyroScaleProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("acc_gyro_scale");
    return Props;
}

const QVariantMap& measUsedProperties()
{
    static const QVariantMap Props = createMeasUsedProperties();
    return Props;
}



}  // namespace nav

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

