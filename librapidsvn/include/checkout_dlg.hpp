/*
 * ====================================================================
 * Copyright (c) 2002-2018 The RapidSVN Group.  All rights reserved.
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
 * along with this program (in the file GPL.txt).
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */
#ifndef _CHECKOUT_DLG_H_INCLUDED_
#define _CHECKOUT_DLG_H_INCLUDED_

// app
#include "checkout_data.hpp"
#include "rapidsvn_generated.h"

// svncpp
namespace svn
{
  class Path;
}

class CheckoutDlg : public CheckoutDlgBase
{
public:
  /**
   * Constructor
   *
   * @param parent parent window
   * @param selectedUrl pre-fills the URL field with
   *                    this URL
   */
  CheckoutDlg(wxWindow * parent, const svn::Path & selectedUrl);

  /**
   * destructor
   */
  virtual ~CheckoutDlg();

  /**
   * returns the checkout data
   */
  const CheckoutData &
  GetData() const;

protected: // Events inherited from CheckoutDlgBase
  virtual void
  OnBrowse(wxCommandEvent & event);

  virtual void
  OnText(wxCommandEvent & event);

  virtual void
  OnCheckBox(wxCommandEvent & event);

  virtual void
  OnHelp(wxCommandEvent & event);

private:
  /** hide implementation details */
  struct Data;
  Data * m;

  void CheckControls();
};

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */
