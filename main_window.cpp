/**
 * Copyright 2020 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of qTabulator.
 *
 * qTabulator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * qTabulator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with qTabulator.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "main_window.h"
#include "about_dialog.h"
#include "colophon_dialog.h"
#include "keyboard_shortcuts_dialog.h"
#include "preferences_dialog.h"

#include <QApplication>
#include <QMenuBar>
#include <QScreen>
#include <QSettings>
#include <QStatusBar>
#include <QToolBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    documentArea(new QMdiArea)
{
    // Central widget
    documentArea->setViewMode(QMdiArea::TabbedView);
    documentArea->setTabsMovable(true);
    documentArea->setTabsClosable(true);
    setCentralWidget(documentArea);

    setupUI();

    readSettings();
}


MainWindow::~MainWindow()
{
}


/**
 * Sets up the user interface.
 */
void MainWindow::setupUI()
{
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/22/tabulator.svg")));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
}


/**
 * Creates user interface actions.
 */
void MainWindow::createActions()
{
    // Actions: Application
    actionAbout = new QAction(QStringLiteral("About %1").arg(QApplication::applicationName()), this);
    actionAbout->setIcon(QIcon(QStringLiteral(":/icons/apps/16/tabulator.svg")));
    actionAbout->setStatusTip(QStringLiteral("Brief description of the application"));
    actionAbout->setToolTip(QStringLiteral("Brief description of the application"));
    connect(actionAbout, &QAction::triggered, this, &MainWindow::onActionAboutTriggered);

    actionColophon = new QAction(QStringLiteral("Colophon"), this);
    actionColophon->setStatusTip(QStringLiteral("Lengthy description of the application"));
    actionColophon->setToolTip(QStringLiteral("Lengthy description of the application"));
    connect(actionColophon, &QAction::triggered, this, &MainWindow::onActionColophonTriggered);

    actionPreferences = new QAction(QStringLiteral("Preferences…"), this);
    actionPreferences->setIcon(QIcon::fromTheme(QStringLiteral("configure"), QIcon(QStringLiteral(":/icons/actions/16/configure.svg"))));
    actionPreferences->setStatusTip(QStringLiteral("Customize the appearance and behavior of the application"));
    actionPreferences->setToolTip(QStringLiteral("Customize the appearance and behavior of the application"));
    connect(actionPreferences, &QAction::triggered, this, &MainWindow::onActionPreferencesTriggered);

    actionQuit = new QAction(QStringLiteral("Quit"), this);
    actionQuit->setIcon(QIcon::fromTheme(QStringLiteral("application-exit"), QIcon(QStringLiteral(":/icons/actions/16/application-exit.svg"))));
    actionQuit->setShortcut(QKeySequence::Quit);
    actionQuit->setStatusTip(QStringLiteral("Quit the application"));
    actionQuit->setToolTip(QStringLiteral("Quit the application"));
    connect(actionQuit, &QAction::triggered, this, &MainWindow::onActionQuitTriggered);

    // Actions: Document
    actionNew = new QAction(QStringLiteral("New"), this);
    actionNew->setIcon(QIcon::fromTheme(QStringLiteral("document-new"), QIcon(QStringLiteral(":/icons/actions/16/document-new.svg"))));
    actionNew->setShortcut(QKeySequence::New);
    actionNew->setStatusTip(QStringLiteral("Create new document"));
    actionNew->setToolTip(QStringLiteral("Create new document"));
    connect(actionNew, &QAction::triggered, this, &MainWindow::onActionNewTriggered);

    // Actions: View
    actionFullScreen = new QAction(this);
    actionFullScreen->setCheckable(true);
    actionFullScreen->setShortcuts(QList<QKeySequence>() << QKeySequence(Qt::Key_F11) << QKeySequence::FullScreen);
    connect(actionFullScreen, &QAction::triggered, this, &MainWindow::onActionFullScreenTriggered);

    updateActionFullScreen();

    // Actions: Help
    actionKeyboardShortcuts = new QAction(QStringLiteral("Keyboard Shortcuts"), this);
    actionKeyboardShortcuts->setIcon(QIcon::fromTheme(QStringLiteral("help-keyboard-shortcuts"), QIcon(QStringLiteral(":/icons/actions/16/help-keyboard-shortcuts.svg"))));
    actionKeyboardShortcuts->setStatusTip(QStringLiteral("List of all keyboard shortcuts"));
    actionKeyboardShortcuts->setToolTip(QStringLiteral("List of all keyboard shortcuts"));
    connect(actionKeyboardShortcuts, &QAction::triggered, this, &MainWindow::onActionKeyboardShortcutsTriggered);
}


/**
 * Updates the full screen action, depending on the current screen-occupation state.
 */
void MainWindow::updateActionFullScreen()
{
    if (!isFullScreen()) {
        actionFullScreen->setText(QStringLiteral("Full Screen Mode"));
        actionFullScreen->setIcon(QIcon::fromTheme(QStringLiteral("view-fullscreen"), QIcon(QStringLiteral(":/icons/actions/16/view-fullscreen.svg"))));
        actionFullScreen->setChecked(false);
        actionFullScreen->setStatusTip(QStringLiteral("Display the window in full screen"));
        actionFullScreen->setToolTip(QStringLiteral("Display the window in full screen"));
    }
    else {
        actionFullScreen->setText(QStringLiteral("Exit Full Screen Mode"));
        actionFullScreen->setIcon(QIcon::fromTheme(QStringLiteral("view-restore"), QIcon(QStringLiteral(":/icons/actions/16/view-restore.svg"))));
        actionFullScreen->setChecked(true);
        actionFullScreen->setStatusTip(QStringLiteral("Exit the full screen mode"));
        actionFullScreen->setToolTip(QStringLiteral("Exit the full screen mode"));
    }
}


/**
 * Creates groups of menu items.
 */
void MainWindow::createMenus()
{
    // Menu: Application
    QMenu *menuApplication = menuBar()->addMenu(QStringLiteral("Application"));
    menuApplication->addAction(actionAbout);
    menuApplication->addAction(actionColophon);
    menuApplication->addSeparator();
    menuApplication->addAction(actionPreferences);
    menuApplication->addSeparator();
    menuApplication->addAction(actionQuit);

    // Menu: Document
    QMenu *menuDocument = menuBar()->addMenu(QStringLiteral("Document"));
    menuDocument->addAction(actionNew);

    // Menu: Edit
    QMenu *menuEdit = menuBar()->addMenu(QStringLiteral("Edit"));

    // Menu: Tools
    QMenu *menuTools = menuBar()->addMenu(QStringLiteral("Tools"));

    // Menu: View
    QMenu *menuView = menuBar()->addMenu(QStringLiteral("View"));
    menuView->addAction(actionFullScreen);

    // Menu: Help
    QMenu *menuHelp = menuBar()->addMenu(QStringLiteral("Help"));
    menuHelp->addAction(actionKeyboardShortcuts);
}


/**
 * Creates groups of tool bar items.
 */
void MainWindow::createToolBars()
{
    // Tool bar: Document
    QToolBar *toolbarDocument = addToolBar(QStringLiteral("Document"));
    toolbarDocument->setObjectName(QStringLiteral("documentToolBar"));
    toolbarDocument->addAction(actionNew);

    // Tool bar: Edit
    QToolBar *toolbarEdit = addToolBar(QStringLiteral("Edit"));
    toolbarEdit->setObjectName(QStringLiteral("editToolBar"));

    // Tool bar: Tools
    QToolBar *toolbarTools = addToolBar(QStringLiteral("Tools"));
    toolbarTools->setObjectName(QStringLiteral("toolsToolBar"));

    // Tool bar: View
    QToolBar *toolbarView = addToolBar(QStringLiteral("View"));
    toolbarView->setObjectName(QStringLiteral("viewToolBar"));
    toolbarView->addAction(actionFullScreen);
}


/**
 * Creates the status bar.
 */
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(QStringLiteral("Welcome to %1").arg(QApplication::applicationName()), 3000);
}


/**
 * Restores user preferences and other application properties.
 */
void MainWindow::readSettings()
{
    QSettings settings;

    // Application: Appearance
    m_settings.restoreWindowGeometry = settings.value(QStringLiteral("Settings/restoreWindowGeometry"), m_settings.restoreWindowGeometry).toBool();
    m_settings.restoreDialogGeometry = settings.value(QStringLiteral("Settings/restoreDialogGeometry"), m_settings.restoreDialogGeometry).toBool();

    // Document: Defaults
    m_settings.horizontalHeaderLabels = static_cast<Settings::HeaderLabel>( settings.value(QStringLiteral("Settings/horizontalHeaderLabels"), (int) m_settings.horizontalHeaderLabels).toInt() );
    m_settings.verticalHeaderLabels = static_cast<Settings::HeaderLabel>( settings.value(QStringLiteral("Settings/verticalHeaderLabels"), (int) m_settings.verticalHeaderLabels).toInt() );
    m_settings.newDocumentColumns = settings.value(QStringLiteral("Settings/newDocumentColumns"), m_settings.newDocumentColumns).toInt();
    m_settings.newDocumentRows = settings.value(QStringLiteral("Settings/newDocumentRows"), m_settings.newDocumentRows).toInt();

    // Window and dialog properties
    const QByteArray mainWindowGeometry = settings.value(QStringLiteral("MainWindow/geometry"), QByteArray()).toByteArray();
    const QByteArray mainWindowState = settings.value(QStringLiteral("MainWindow/state"), QByteArray()).toByteArray();
    aboutDialogGeometry = settings.value(QStringLiteral("AboutDialog/geometry"), QByteArray()).toByteArray();
    colophonDialogGeometry = settings.value(QStringLiteral("ColophonDialog/geometry"), QByteArray()).toByteArray();
    keyboardShortcutsDialogGeometry = settings.value(QStringLiteral("KeyboardShortcutsDialog/geometry"), QByteArray()).toByteArray();
    preferencesDialogGeometry = settings.value(QStringLiteral("PreferencesDialog/geometry"), QByteArray()).toByteArray();

    // Set window properties
    if (m_settings.restoreWindowGeometry && !mainWindowGeometry.isEmpty()) {
        restoreGeometry(mainWindowGeometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
    restoreState(mainWindowState);
}


/**
 * Saves user preferences and other application properties.
 */
void MainWindow::writeSettings()
{
    QSettings settings;

    // Application: Appearance
    settings.setValue(QStringLiteral("Settings/restoreWindowGeometry"), m_settings.restoreWindowGeometry);
    settings.setValue(QStringLiteral("Settings/restoreDialogGeometry"), m_settings.restoreDialogGeometry);

    // Document: Defaults
    settings.setValue(QStringLiteral("Settings/horizontalHeaderLabels"), (int) m_settings.horizontalHeaderLabels);
    settings.setValue(QStringLiteral("Settings/verticalHeaderLabels"), (int) m_settings.verticalHeaderLabels);
    settings.setValue(QStringLiteral("Settings/newDocumentColumns"), m_settings.newDocumentColumns);
    settings.setValue(QStringLiteral("Settings/newDocumentRows"), m_settings.newDocumentRows);

    // Window and dialog properties
    settings.setValue(QStringLiteral("MainWindow/geometry"), saveGeometry());
    settings.setValue(QStringLiteral("MainWindow/state"), saveState());
    settings.setValue(QStringLiteral("AboutDialog/geometry"), aboutDialogGeometry);
    settings.setValue(QStringLiteral("ColophonDialog/geometry"), colophonDialogGeometry);
    settings.setValue(QStringLiteral("KeyboardShortcutsDialog/geometry"), keyboardShortcutsDialogGeometry);
    settings.setValue(QStringLiteral("PreferencesDialog/geometry"), preferencesDialogGeometry);
}


/**
 * Processes the Close event.
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (true) {
        writeSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
}


/**
 * Creates a document widget.
 */
DocumentTable *MainWindow::createDocument()
{
    DocumentTable *document = new DocumentTable;
    document->setSettings(m_settings);
    documentArea->addSubWindow(document);

    return document;
}


/**
 * Displays the About dialog.
 */
void MainWindow::onActionAboutTriggered()
{
    const QByteArray geometry = m_settings.restoreDialogGeometry ? aboutDialogGeometry : QByteArray();

    AboutDialog *aboutDialog = new AboutDialog(this);
    aboutDialog->setWindowTitle(QStringLiteral("About %1").arg(QApplication::applicationName()));
    aboutDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    aboutDialog->setWindowGeometry(geometry);
    aboutDialog->exec();

    aboutDialogGeometry = aboutDialog->windowGeometry();

    aboutDialog->deleteLater();
}


/**
 * Displays the Colophon dialog.
 */
void MainWindow::onActionColophonTriggered()
{
    const QByteArray geometry = m_settings.restoreDialogGeometry ? colophonDialogGeometry : QByteArray();

    ColophonDialog *colophonDialog = new ColophonDialog(this);
    colophonDialog->setWindowTitle(QStringLiteral("Colophon"));
    colophonDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    colophonDialog->setWindowGeometry(geometry);
    colophonDialog->exec();

    colophonDialogGeometry = colophonDialog->windowGeometry();

    colophonDialog->deleteLater();
}


/**
 * Displays the Preferences dialog.
 */
void MainWindow::onActionPreferencesTriggered()
{
    const QByteArray geometry = m_settings.restoreDialogGeometry ? preferencesDialogGeometry : QByteArray();

    PreferencesDialog *preferencesDialog = new PreferencesDialog(this);
    preferencesDialog->setWindowTitle(QStringLiteral("Preferences"));
    preferencesDialog->setWindowGeometry(geometry);
    preferencesDialog->setSettings(m_settings);
    preferencesDialog->exec();

    preferencesDialogGeometry = preferencesDialog->windowGeometry();
    m_settings = preferencesDialog->settings();

    preferencesDialog->deleteLater();
}


/**
 * Fires the Close event to terminate the application.
 */
void MainWindow::onActionQuitTriggered()
{
    close();
}


/**
 * Creates a new document.
 */
void MainWindow::onActionNewTriggered()
{
    DocumentTable *document = createDocument();
    document->createDocument();
    document->show();
}


/**
 * Sets the screen-occupation state of the window.
 */
void MainWindow::onActionFullScreenTriggered()
{
    if (!isFullScreen()) {
        setWindowState(windowState() | Qt::WindowFullScreen);
    }
    else {
        setWindowState(windowState() & ~Qt::WindowFullScreen);
    }

    updateActionFullScreen();
}


/**
 * Displays the Keyboard Shortcuts dialog.
 */
void MainWindow::onActionKeyboardShortcutsTriggered()
{
    const QByteArray geometry = m_settings.restoreDialogGeometry ? keyboardShortcutsDialogGeometry : QByteArray();

    keyboardShortcutsDialog = new KeyboardShortcutsDialog(this);
    keyboardShortcutsDialog->setWindowTitle(QStringLiteral("Keyboard Shortcuts"));
    keyboardShortcutsDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    keyboardShortcutsDialog->setWindowGeometry(geometry);
    connect(keyboardShortcutsDialog, &KeyboardShortcutsDialog::finished, this, &MainWindow::onDialogKeyboardShortcutsFinished);
    keyboardShortcutsDialog->show();
}


/**
 * Keyboard Shortcuts dialog was closed.
 */
void MainWindow::onDialogKeyboardShortcutsFinished()
{
    keyboardShortcutsDialogGeometry = keyboardShortcutsDialog->windowGeometry();

    keyboardShortcutsDialog->deleteLater();
}
