/**
 * Copyright 2020 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of Tabulator-Qt.
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

#include "document_table.h"
#include "keyboard_shortcuts_dialog.h"
#include "settings.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setApplicationGeometry(const QByteArray &geometry = QByteArray());
    QByteArray applicationGeometry() const;

    void setApplicationState(const QByteArray &state = QByteArray());
    QByteArray applicationState() const;

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

    void onActionFullScreenTriggered();

    void onActionKeyboardShortcutsTriggered();
    void onDialogKeyboardShortcutsFinished();

private:
    QMdiArea *m_documentArea;

    void createActions();
    void createMenus();
    void createToolbars();

    void updateActionRecentDocuments();
    void updateActionFullScreen();
    void updateMenuOpenRecent();
    void updateMenuOpenRecentItems();

    QAction *m_actionAbout;
    QAction *m_actionColophon;
    QAction *m_actionPreferences;
    QAction *m_actionQuit;

    QAction *m_actionNew;
    QAction *m_actionOpen;
    QMenu *m_menuOpenRecent;
    QList<QAction *> m_actionRecentDocuments;
    QAction *m_actionOpenRecentClear;

    QAction *m_actionFullScreen;
    QAction *m_actionToolbarApplication;
    QAction *m_actionToolbarDocument;
    QAction *m_actionToolbarEdit;
    QAction *m_actionToolbarTools;
    QAction *m_actionToolbarView;

    QToolBar *m_toolbarApplication;
    QToolBar *m_toolbarDocument;
    QToolBar *m_toolbarEdit;
    QToolBar *m_toolbarTools;
    QToolBar *m_toolbarView;

    QAction *m_actionKeyboardShortcuts;

    Settings m_settings;
    void readSettings();
    void writeSettings();

    QByteArray m_aboutDialogGeometry;
    QByteArray m_colophonDialogGeometry;
    QByteArray m_keyboardShortcutsDialogGeometry;
    QByteArray m_preferencesDialogGeometry;

    DocumentTable *createDocumentChild();
    QMdiSubWindow *findDocumentChild(const QString &file) const;
    DocumentTable *activeDocumentChild() const;

    QStringList m_recentDocuments;
    bool loadDocument(const QString &file);
    void updateRecentDocuments(const QString &file);

    KeyboardShortcutsDialog *m_keyboardShortcutsDialog;
};

#endif // MAIN_WINDOW_H
