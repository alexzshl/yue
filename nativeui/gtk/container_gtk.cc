// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include "nativeui/container.h"

#include <gtk/gtk.h>

#include "nativeui/gtk/nu_container.h"

namespace nu {

void Container::PlatformInit() {
  TakeOverView(nu_container_new(this));
}

void Container::PlatformDestroy() {
  // The widget relies on Container to get children, so we must ensure the
  // widget is destroyed before this class.
  View::PlatformDestroy();
}

void Container::PlatformInstallMouseClickEvents() {
  View::PlatformInstallMouseClickEvents();
  nu_container_add_event_mask(
      NU_CONTAINER(GetNative()),
      GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
}

void Container::PlatformInstallMouseMoveEvents() {
  View::PlatformInstallMouseMoveEvents();
  nu_container_add_event_mask(
      NU_CONTAINER(GetNative()),
      GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK |
      GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
}

void Container::PlatformInstallKeyEvents() {
  View::PlatformInstallKeyEvents();
  nu_container_add_event_mask(
      NU_CONTAINER(GetNative()),
      GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK);
}

void Container::PlatformAddChildView(View* child) {
  // If we are adding a radio button, we check whether there is already a radio
  // button in the container, and join radio group if so.
  if (GTK_IS_RADIO_BUTTON(child->GetNative())) {
    for (int i = 0; i < ChildCount(); ++i) {
      GtkWidget* widget = ChildAt(i)->GetNative();
      if (GTK_IS_RADIO_BUTTON(widget)) {
        gtk_radio_button_join_group(GTK_RADIO_BUTTON(child->GetNative()),
                                    GTK_RADIO_BUTTON(widget));
        break;
      }
    }
  }

  gtk_container_add(GTK_CONTAINER(GetNative()), child->GetNative());
}

void Container::PlatformRemoveChildView(View* child) {
  gtk_container_remove(GTK_CONTAINER(GetNative()), child->GetNative());
}

}  // namespace nu
