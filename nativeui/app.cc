// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include "nativeui/app.h"

#include <utility>

#include "nativeui/menu_bar.h"
#include "nativeui/state.h"

namespace nu {

// static
App* App::GetCurrent() {
  return State::GetCurrent()->GetApp();
}

App::App() : weak_factory_(this) {
}

App::~App() = default;

void App::SetName(base::Optional<std::string> name) {
  name_override_ = std::move(name);
}

std::string App::GetName() const {
  if (name_override_)
    return *name_override_;
  return PlatformGetName();
}

}  // namespace nu
