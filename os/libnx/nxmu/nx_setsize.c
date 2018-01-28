/****************************************************************************
 * libnx/nxmu/nx_setsize.c
 *
 *   Copyright (C) 2008-2009, 2011-2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>

#include <errno.h>
#include <debug.h>

#include <tinyara/nx/nx.h>
#include <tinyara/nx/nxbe.h>
#include <tinyara/nx/nxmu.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nx_setsize
 *
 * Description:
 *  Set the size of the selected window
 *
 * Input Parameters:
 *   hwnd   - The window handle
 *   size   - The new size of the window.
 *
 * Return:
 *   OK on success; ERROR on failure with errno set appropriately
 *
 ****************************************************************************/

int nx_setsize(NXWINDOW hwnd, FAR const struct nxgl_size_s *size)
{
  FAR struct nxbe_window_s *wnd = (FAR struct nxbe_window_s *)hwnd;
  struct nxsvrmsg_setsize_s outmsg;

#ifdef CONFIG_DEBUG_FEATURES
  if (!wnd || !size)
    {
      set_errno(EINVAL);
      return ERROR;
    }
#endif

  /* Then inform the server of the changed position */

  outmsg.msgid  = NX_SVRMSG_SETSIZE;
  outmsg.wnd    = wnd;
  outmsg.size.w = size->w;
  outmsg.size.h = size->h;

  return nxmu_sendwindow(wnd, &outmsg, sizeof(struct nxsvrmsg_setsize_s));
}
