// SPDX-License-Identifier: GPL-2.0-or-later

#include "CustomNMEA.hpp"

#include "InfoBoxes/Data.hpp"
#include "Interface.hpp"
#include "NMEA/Info.hpp"

void
InfoBoxContentCustomNMEA::Update(InfoBoxData &data) noexcept
{
  const NMEAInfo &info = CommonInterface::Basic();

  /*constexpr double TIMEOUT = 10.0;
  bool valid = false;

  if (info.custom_box_available) {
    auto age = (info.clock - info.custom_box_last_update).ToDoubleSeconds();
    if (age >= 0 && age <= TIMEOUT)
      valid = true;
  }*/
  bool valid = true;
  if (valid) {
    data.SetTitle(info.custom_box_title.c_str());
    data.SetValue(info.custom_box_value.c_str());
  } else {
    data.SetTitle("NMEA_Henrik");
    data.SetValue("+1");
  }
}
