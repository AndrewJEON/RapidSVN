/*
 * ====================================================================
 * Copyright (c) 2002, 2003 The RapidSvn Group.  All rights reserved.
 *
 * This software is licensed as described in the file LICENSE.txt,
 * which you should have received as part of this distribution.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */
#ifndef _RAPIDSVN_FRAME_HEADER_H_INCLUDED_
#define _RAPIDSVN_FRAME_HEADER_H_INCLUDED_

// wxwindows
#include "wx/frame.h"
#include "wx/textctrl.h"
#include "wx/toolbar.h"
#include "wx/splitter.h"

// app
#include "simple_worker.hpp"
#include "tracer.hpp"
#include "log_action.hpp"
#include "filelist_ctrl.hpp"
#include "folder_browser.hpp"
#include "utils.hpp"

#define SPLITTER_WINDOW   100

typedef enum
{
  ACTION_TYPE_NONE,
  ACTION_TYPE_UPDATE,
  ACTION_TYPE_COMMIT,
  ACTION_TYPE_CHECKOUT,
  ACTION_TYPE_IMPORT,
  ACTION_TYPE_ADD,
  ACTION_TYPE_DEL,
  ACTION_TYPE_REVERT,
  ACTION_TYPE_RESOLVE,
  ACTION_TYPE_COPY,
  ACTION_TYPE_MKDIR,
  ACTION_TYPE_MERGE,
  ACTION_TYPE_CLEANUP,
  ACTION_TYPE_PROPERTY,
  ACTION_TYPE_LOG,
  ACTION_TYPE_DELETE
}
ActionType;

typedef enum
{
  ACTIVEPANE_FOLDER_BROWSER,
  ACTIVEPANE_FILELIST
}
ActivePane;


// forward declarations
class svn::Targets;
class wxFrame;

/**
* Panel holding the splitter with the folder browser
* and the file list.
*/
class InfoPanel:public wxPanel
{
public:
  InfoPanel (wxWindow * parent);
};

class LogTracer:public wxTextCtrl, public Tracer
{

public:
  LogTracer (wxWindow * parent);
  void Trace (const wxString & str);
};

class RapidSvnFrame:public wxFrame
{
public:
  RapidSvnFrame (const wxString & title);
  virtual ~RapidSvnFrame ();

private:
  void OnSize (wxSizeEvent & event);

  // File menu
  void OnAddProject (wxCommandEvent & event);
  void OnRemoveProject (wxCommandEvent & event);
  void OnQuit (wxCommandEvent & event);

  // View menu
  void OnPreferences (wxCommandEvent & event);
  void OnRefresh (wxCommandEvent & event);

  // Query menu
  void OnLog (wxCommandEvent & event);
  void OnInfo (wxCommandEvent & event);

  // Modify menu
  void OnFileCommand (wxCommandEvent & event);

  // Extras menu
  void OnCleanup (wxCommandEvent & event);

  // Help menu
  void OnContents (wxCommandEvent & event);
  void OnAbout (wxCommandEvent & event);

  // toolbar administration
  void LayoutChildren ();
  void RecreateToolbar ();
  void AddActionTools ();
  void AddInfoTools ();

  // menu stuff
  void InitializeMenu ();

  // toolbar events
  void OnToolEnter (wxCommandEvent & event);
  void OnToolLeftClick (wxCommandEvent & event);

  // Events from action threads
  void OnActionEvent (wxCommandEvent & event);

  // Folder Browser
  void InitFolderBrowser ();
  void AddProject ();
  void RemoveProject ();
  void OnFolderBrowserSelChanged (wxTreeEvent & event);
  void OnFolderBrowserKeyDown (wxTreeEvent & event);
  void OnFileListSelected (wxListEvent & event);

  void UpdateCurrentPath ();

  // list control
  void UpdateFileList ();

  // utility functions
  void ShowLog ();
  void ShowInfo ();

  const svn::Targets GetActionTargets() const;

  void DelEntries ();
  void MakeRevert ();
  void MakeResolve ();

  void MakeCopy ();
  void Rename ();
  void Mkdir ();
  void Merge ();
  void Contents ();
  void Preferences ();

  FileListCtrl *GetFileList ()
  {
    return m_listCtrl;
  }

  FolderBrowser *GetFolderBrowser ()
  {
    return m_folder_browser;
  }

  void Perform (ActionType type, Action * action);


private:
  ActionWorker * m_actionWorker;

  FolderBrowser * m_folder_browser;
  FileListCtrl *m_listCtrl;

  wxSplitterWindow *m_horiz_splitter;
  wxSplitterWindow *m_vert_splitter;

  InfoPanel *m_info_panel;

  wxTextCtrl *m_log;
  EventTracer *m_logTracer;

  wxToolBar *m_tbar;
  size_t m_toolbar_rows;        // 1 or 2 only (toolbar rows)

  ActionType m_lastAction;
  wxString m_currentPath;
  wxString m_title;
  svn::Context * m_context;
  ActivePane m_activePane;

private:
  DECLARE_EVENT_TABLE ()
};

const int ID_TOOLBAR = 500;

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */