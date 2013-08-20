// Aseprite UI Library
// Copyright (C) 2001-2013  David Capello
//
// This source file is distributed under MIT license,
// please read LICENSE.txt for more information.


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ui/link_label.h"

#include "base/launcher.h"
#include "ui/message.h"
#include "ui/system.h"
#include "ui/theme.h"

namespace ui {

LinkLabel::LinkLabel(const char* urlOrText)
  : CustomLabel(urlOrText)
  , m_url(urlOrText)
{
}

LinkLabel::LinkLabel(const char* url, const char* text)
  : CustomLabel(text)
  , m_url(url)
{
}

void LinkLabel::setUrl(const char* url)
{
  m_url = url;
}

bool LinkLabel::onProcessMessage(Message* msg)
{
  switch (msg->type()) {

    case kSetCursorMessage:
      // TODO theme stuff
      if (isEnabled()) {
        jmouse_set_cursor(kHandCursor);
        return true;
      }
      break;

    case kMouseEnterMessage:
    case kMouseLeaveMessage:
      // TODO theme stuff
      if (isEnabled())
        invalidate();
      break;

    case kMouseUpMessage:
      if (isEnabled()) {
        if (!m_url.empty())
          base::launcher::open_url(m_url);
        Click();
      }
      break;
  }

  return CustomLabel::onProcessMessage(msg);
}

void LinkLabel::onPaint(PaintEvent& ev)
{
  getTheme()->paintLinkLabel(ev);
}

} // namespace ui
