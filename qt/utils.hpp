/*
 * ====================================================================
 * Copyright (c) 2002-2010 The RapidSVN Group.  All rights reserved.
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
#ifndef _RAPIDSVN_UTILS_H_INCLUDED_
#define _RAPIDSVN_UTILS_H_INCLUDED_

#define UNPORTED_TO_QT 0

#include <QVector>

// stl
#include "svncpp/string_wrapper.hpp"

// wx
//#include "wx/dynarray.h"

// svn
#include <svn_wc.h>

// apr
#include <apr_time.h>

// forward declarations
class QString;
class Tracer;
class QMenu;
class QMenuItem;
class QPushButton;
class QWidget;
class QCheckBox;

#if UNPORTED_TO_QT
class wxFileName;
class wxTextCtrl;
#endif

namespace svn
{
  class Status;
  class Path;
  class Context;
}

/**
 * declaration of an array with @a svn_revnum_t elements
 */
typedef QVector<svn_revnum_t> RevnumArray;


/**
 * Create pseudo-unix paths on windows for use with svn (reverse backslashes,
 * but leave the rest as it is)
 *
 * NOTE: Does nothing on non-windows platforms
 *
 * @param path Native path to convert
 * @return string with all backslashes converted to forward slashes
 */
QString &
UnixPath(QString & path);

/**
 * Trim whitespace at start and end of string
 * (Convenience function for trimming first left, then right)
 */
void
TrimString(QString & str);

/**
 * Post a menu command event with the given ID.
 *
 * Used for converting non-command events to command events so they'll move up
 * the GUI hierarchy.
 */
#if UNPORTED_TO_QT
bool
PostMenuEvent(wxEvtHandler *source, long id);
#endif

/**
 * Create a correctly sized button with an ellipsis (three dots)
 */
QPushButton *
CreateEllipsisButton(QWidget *parent, long id);

/**
 * Append entries for the "Modify" menu
 *
 * @param parentMenu menu that will receive the items
 */
void
AppendModifyMenu(QMenu * parentMenu);

/**
 * Append entries for the "Repository" menu
 *
 * @param parentMenu menu that will receive the items
 */
void
AppendBookmarksMenu(QMenu * parentMenu);

/**
 * Append entries for the "Query" menu
 *
 * @param parentMenu menu that will receive the items
 */
void
AppendQueryMenu(QMenu * parentMenu);


/**
 * Append entries for "verbs" (Win32 only).
 * Since this feature is context specific (based on
 * the selected file), @a status has to be passed.
 * Works only with one selected file
 *
 * @param parentMenu menu that will receive the items
 * @param status status instance of the selected item
 */
void
AppendVerbMenu(QMenu * parentMenu, svn::Status * status);


/**
 * Checks if the given string contains a valid
 * revision number
 *
 * @param revstring revision string
 * @return true if valid revision
 */
bool
CheckRevision(const QString & revstring);


/**
 * Creates a menu item for @a id (with whistles and bells, uh,
 * bitmaps)
 *
 * @param menu menu where the new item will be appended
 * @param id menu item to create
 */
QMenuItem *
AppendMenuItem(QMenu & menu, int id);


/**
 * Tries to interpret @a revstring a revision number
 *
 * @param revstring string with revision number
 * @param revnum revision number
 * @return success?
 * @retval true valid revision number
 */
bool
ParseRevision(const QString & revstring, svn_revnum_t & revnum);


/**
 * Format a date/time value to standard format
 *
 * @param data
 * @return formatted date/time string
 */
QString
FormatDateTime(apr_time_t date);


/**
 * beautify a path so drive letters (if existing) are uppercase
 *
 * Examples:
 * 1. Local Unix path (leave alone)
 *    Before:  /home/users/xela/work/rapidsvn/src/svncpp
 *    After:   /home/users/xela/work/rapidsvn/src/svncpp
 *
 * 2. Local Windows path (uppercase drive letter)
 *    Before:  d:\Documents and Settings\alex\Application Data
 *    After:   D:\Documents and Settings\alex\Application Data
 *
 * 3. Repository URL (lowercase url schema)
 *    Before:  https://svn.collab.net/repos/rapidsvn/trunk/src/svncpp
 *    After:   https://svn.collab.net/repos/rapidsvn/trunk/src/svncpp
 *
 * Jobs to do:
 * - Uppercase Windows drive letters
 * - Lowecase url schemas
 *
 * @param path input path
 * @return beatified path
 */
QString
BeautifyPath(const QString & path);


/**
 * creates a textual description for a status value
 *
 * @param kind
 * @return brief textual description
 */
QString
StatusDescription(const svn_wc_status_kind kind);


/**
 * converts a string from local encoding (like Ansi on
 * Windows) to utf8
 *
 * @see Utf8ToLocal
 *
 * @param srcLocal string in local encoding
 * @return string in utf8 encoding
 */
std::string
LocalToUtf8(const QString & srcLocal);

/**
 * converts a string from local encoding (like Ansi on
 * Windows) to utf8
 *
 * @see Utf8ToLocal
 *
 * @param srcLocal string in local encoding
 * @param dstUtf8 string in utf8 encoding
 */
void
LocalToUtf8(const QString & srcLocal, std::string & dstUtf8);

/**
 * converts a string from local encoding to a utf8 path.
 * Urls get escaped
 *
 * @param path path string in local encoding
 * @return path in utf8
 */
svn::Path
PathUtf8(const QString & path);


/**
 * converts an utf8 path to a string in local encoding
 * with native path separators
 *
 * @param path source
 * @param path string in local encoding
 */
QString
PathToNative(const svn::Path & path);

/**
 * converts a string from utf to the local encoding
 * (like Ansi on Windows)
 *
 * @see LocalToUtf8
 *
 * @param srcUtf8 string in utf8 encoding
 * @return string in local encoding
 */
QString
Utf8ToLocal(const char* srcUtf8);

/**
 * converts a string from utf to the local encoding
 * (like Ansi on Windows)
 *
 * @see LocalToUtf8
 *
 * @param srcUtf8 string in utf8 encoding
 * @return string in local encoding
 */
QString
Utf8ToLocal(const std::string & srcUtf8);

/**
 * Opens a webpage in the default Browser.
 *
 * @param url URL to open
 */
void
OpenURL(const QString & url);

/**
 * Converts svn::Path to native full path expression
 * (e.g. C:\foo\bar) using view mode and current folder
 * selection status.
 *
 * [Path Type / Flat Mode]
 * URL /  -  : Outputs URL always.
 * WS  / No  : Input path may be relative (if reflesh with update
 *             checed), but all files must be in FolderBrowser
 *             selected path.
 * WS  / Yes : FolderBrowser selection is not reliable because
 *             various pathes are shown in file list. But input
 *             path is always full path in this mode.
 *
 * @param target svn::Path formatted path object
 * @param base path of current selection status in FolderBrowser
 * @param flat true if flat mode is selected
 *
 * @return native file path (if in WS) or URL (if in repository)
 */
QString
FullNativePath(const svn::Path & target, const QString & base, bool flat);

/**
  * Checks that folder on path contents a modified child/children.
  *
  * @param path path to folder
  * @param context pointer to current context
  *
  * @return true if folder contents modified children,
  *         otherwise false
  */
bool
HasModifiedChildren(const svn::Path & path, svn::Context * context);

/**
 * Checks whether @a executable can be found path and returns the
 * absolute path
 */
QString
FindExecutableInPath(const QString & executable);


/**
 * This works almost like @ref ::wxDirExists, but in extension of
 * @ref wxDirExists this call expands ~ (home dir) and environment
 * variable before checking the existence
 *
 * @param dir
 */
bool
IsValidDir(const QString & dir);


/**
 * Helper function that enables/disables a control only if
 * the enable status differs.
 * This avoids flickering on some platforms.
 *
 * @param ctrl
 * @param enable
 */
void
EnableCtrl(QWidget * ctrl, bool enable);


/** Updates the value of a checkbox flicker-free */
void
UpdateValue(QCheckBox * ctrl, bool value);

#if UNPORTED_TO_QT
void
UpdateValue(wxTextCtrl * ctrl, const QString & value);
#endif

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */
