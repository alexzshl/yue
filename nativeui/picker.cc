// Copyright 2019 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include "nativeui/picker.h"

namespace nu {

// static
const char Picker::kClassName[] = "Picker";

Picker::~Picker() = default;

const char* Picker::GetClassName() const {
  return kClassName;
}

}  // namespace nu
