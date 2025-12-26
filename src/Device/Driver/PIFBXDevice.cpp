// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The XCSoar Project

#include "Device/Driver/PIFBXDevice.hpp"

#include "Device/Driver.hpp"
#include "NMEA/Info.hpp"
#include "NMEA/InputLine.hpp"
#include "NMEA/Checksum.hpp"

#include <string_view>

using std::string_view_literals::operator""sv;

/*
 * Erwartetes Format:
 *
 *   $PIFBX,<title>,<value>*CHECKSUM
 *
 * Beispiele:
 *   $PIFBX,Flap,+1*CS
 *   $PIFBX,Temp,25.3*CS
 */

static bool
ParsePIFBX(NMEAInputLine &line, NMEAInfo &info)
{
  const auto title = line.ReadView();
  const auto value = line.ReadView();

  if (title.empty() || value.empty())
    return false;

  info.custom_box_title = title;
  info.custom_box_value = value;
  info.custom_box_available.Update(info.clock);
  //info.custom_box_last_update = info.clock; // clock kommt aus NMEAInfo

  return true;
}

class PIFBXDevice final : public AbstractDevice {
  Port &port;

public:
  PIFBXDevice(Port &_port): port(_port) {(void)port;}

  bool ParseNMEA(const char *line, NMEAInfo &info) override;
};

bool
PIFBXDevice::ParseNMEA(const char *_line, NMEAInfo &info)
{
  if (!VerifyNMEAChecksum(_line))
    return false;

  NMEAInputLine line(_line);

  if (line.ReadCompare("$PIFBX"))
    return ParsePIFBX(line, info);

  return false;
}

static Device *
PIFBXCreateOnPort([[maybe_unused]] const DeviceConfig &config, Port &com_port)
{
  return new PIFBXDevice(com_port);
}

const struct DeviceRegister pifbx_driver = {
  _T("PIFBX"),
  _T("PIFBX Generic Infobox"),
  DeviceRegister::RECEIVE_SETTINGS,
  PIFBXCreateOnPort,
};
