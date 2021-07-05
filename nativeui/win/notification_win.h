// Copyright 2021 Cheng Zhao. All rights reserved.
// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE.chromium file.

#ifndef NATIVEUI_WIN_NOTIFICATION_WIN_H_
#define NATIVEUI_WIN_NOTIFICATION_WIN_H_

#include <memory>
#include <string>
#include <vector>

#include "nativeui/notification.h"
#include "nativeui/win/notifications/winrt_util.h"

namespace nu {

class ToastEventHandler;

struct NotificationImpl {
  base::Optional<std::wstring> xml;

  std::wstring title;
  std::wstring body;
  std::wstring info;
  bool has_reply_button = false;
  std::wstring reply_placeholder;
  base::Optional<std::wstring> image;
  base::Optional<std::wstring> image_placement;
  bool silent = false;
  std::vector<Notification::Action> actions;

  mswr::ComPtr<IToastNotification> toast;
  std::unique_ptr<ToastEventHandler> event_handler;
};

}  // namespace nu

#endif  // NATIVEUI_WIN_NOTIFICATION_WIN_H_
