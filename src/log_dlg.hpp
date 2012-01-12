/*
 * ====================================================================
 * Copyright (c) 2002-2012 The RapidSVN Group.  All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (in the file GPL.txt.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */

#ifndef _LOG_DLG_H_INCLUDED_
#define _LOG_DLG_H_INCLUDED_

// wxWidgets
#include "wx/dialog.h"

// svncpp
#include "svncpp/client.hpp"

// app
#include "rapidsvn_generated.h"

class LogDlg : public LogDlgBase
{
public:
  /**
   * constructor. the @a entries are NOT owned by
   * this class.
   *
   * @param parent parent window
   * @param path path of selected item
   * @param entries log entries
   */
  LogDlg(wxWindow * parent,
         const char * path,
         const svn::LogEntries * entries);

  /**
   * destructor
   */
  virtual ~LogDlg();

protected:  // events inherited from LogDlgBase
  void 
  OnGet(wxCommandEvent & event);

  void 
  OnView(wxCommandEvent & event);

  void 
  OnDiff(wxCommandEvent & event);

  void 
  OnMerge(wxCommandEvent & event);

  void 
  OnAnnotate(wxCommandEvent & event);

  void
  OnRevSelected(wxListEvent & event);

  void
  OnRevDeselected(wxListEvent & event);

private:
  /** hide implementation details */
  struct Data;
  Data * m;

  void CheckControls();
  void UpdateSelection();

};

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */
