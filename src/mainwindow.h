/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf
*   This software is subject to, and may be distributed under, the
*   GNU General Public License, either version 2 of the license,
*   or (at your option) any later version. The license should have
*   accompanied the software or you may obtain a copy of the license
*   from the Free Software Foundation at http://www.fsf.org .

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "recentfiles.h"

class Blit;
class QDjVuContext;
class QDjVuDocument;
class HelpDialog;

class MainWindow : public QMainWindow
{
	  Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
private slots:
	/** Open given file. */
	void openFile(const QString& file);
	/** Select file to display. */
	void selectFileToOpen();
	/** Display information about the program. */
	void showAboutDialog();
	/** Document loaded. */
	void documentLoaded();
	/** Show progress. */
	void progress(int percentage);
	/** Export selected pixmaps. */
	void exportPixmaps();
	/** Configure program. */
	void configure();
	/** Show blit in main document. */
	void showBlit(const Blit& blit);
	/** Show blit in external document. */
	void launchDjview(const Blit& blit);
	/** Toggle help. */
	void toggleHelp();
protected:
	 /** Confirm quitting. */
	 void closeEvent(QCloseEvent* event);
	 /** Help dialog. */
	 HelpDialog* helpDialog();

	 /** Connect actions. */
	 void setupActions();
	 /** Read configuration. */
	 void restoreSettings();
	 /** Save settings. */
	 void saveSettings();
	 /** Check if the data is saved. */
	 bool queryClose();

	 Ui::MainWindow ui;
	 static const QString m_applicationName;

	 RecentFiles m_recentFiles;
	 QDjVuDocument* m_document;
	 QDjVuContext* m_context;
	 QString m_filename;

	 HelpDialog* m_helpDialog;
};

#endif // MAINWINDOW_H

