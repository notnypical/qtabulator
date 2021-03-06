/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of Tabulator-Qt, <https://github.com/notnypical/tabulator-qt>.
 *
 * Tabulator-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tabulator-Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tabulator-Qt.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QAction>
#include <QByteArray>
#include <QCloseEvent>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QToolBar>

#include "document.h"
#include "keyboard_shortcuts_dialog.h"
#include "preferences.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setApplicationState(const QByteArray &state = QByteArray());
    QByteArray applicationState() const;

    void setApplicationGeometry(const QByteArray &geometry = QByteArray());
    QByteArray applicationGeometry() const;

    bool openDocument(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onActionAboutTriggered();
    void onActionColophonTriggered();
    void onActionPreferencesTriggered();

    void onActionNewTriggered();
    void onActionOpenTriggered();
    void onActionOpenRecentDocumentTriggered(const QString file = "");
    void onActionOpenRecentClearTriggered();
    void onActionCloseTriggered();
    void onActionCloseOtherTriggered();
    void onActionCloseAllTriggered();

    void onActionFullScreenTriggered();
    void onActionTitlebarFullPathTriggered();

    void onActionKeyboardShortcutsTriggered();
    void onDialogKeyboardShortcutsFinished();

    void onDocumentActivated(const QMdiSubWindow *window);
    void onDocumentClosed(const QString &canonicalName);

private:
    Preferences m_preferences;

    QStringList m_recentDocuments;

    QByteArray m_applicationState;
    QByteArray m_applicationGeometry;
    QByteArray m_aboutDialogGeometry;
    QByteArray m_colophonDialogGeometry;
    QByteArray m_keyboardShortcutsDialogGeometry;
    QByteArray m_preferencesDialogGeometry;

    void loadSettings();
    void saveSettings();

    QToolBar *m_toolbarApplication;
    QToolBar *m_toolbarDocument;
    QToolBar *m_toolbarEdit;
    QToolBar *m_toolbarTools;
    QToolBar *m_toolbarView;
    QToolBar *m_toolbarHelp;

    void createActions();
    void createMenus();
    void createToolBars();

    void updateActionFullScreen();
    void updateActionRecentDocuments();
    void updateMenus(const int cntWindows = 0);
    void updateMenuOpenRecent();

    QAction *m_actionAbout;
    QAction *m_actionColophon;
    QAction *m_actionPreferences;
    QAction *m_actionQuit;

    QAction *m_actionNew;
    QAction *m_actionOpen;
    QMenu *m_menuOpenRecent;
    QList<QAction *> m_actionRecentDocuments;
    QAction *m_actionOpenRecentClear;
    QAction *m_actionClose;
    QAction *m_actionCloseOther;
    QAction *m_actionCloseAll;

    QAction *m_actionFullScreen;
    QAction *m_actionTitlebarFullPath;
    QAction *m_actionToolbarApplication;
    QAction *m_actionToolbarDocument;
    QAction *m_actionToolbarEdit;
    QAction *m_actionToolbarTools;
    QAction *m_actionToolbarView;
    QAction *m_actionToolbarHelp;

    QAction *m_actionKeyboardShortcuts;

    QMdiArea *m_documentArea;

    Document *createDocument();
    int createDocumentIndex(const QString &canonicalName);
    QMdiSubWindow *findDocument(const QString &canonicalName) const;
    Document *activeDocument() const;
    bool loadDocument(const QString &canonicalName);

    void updateRecentDocuments(const QString &canonicalName);

    void updateApplicationTitle();

    KeyboardShortcutsDialog *m_keyboardShortcutsDialog;
};

#endif // MAIN_WINDOW_H
