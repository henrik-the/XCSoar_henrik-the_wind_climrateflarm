// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright

#pragma once

#include "InfoBoxes/Content/Base.hpp"

class InfoBoxContentCustomNMEA : public InfoBoxContent
{
public:
  /* Keine Panels nötig */
  const InfoBoxPanel *GetDialogContent() noexcept override {
    return nullptr;
  }

  void Update(InfoBoxData &data) noexcept override;
};
