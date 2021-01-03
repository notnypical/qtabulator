/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
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

#include "main_window.h"

#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QMenuBar>
#include <QScreen>
#include <QSettings>
#include <QStandardPaths>
#include <QStatusBar>
#include <QToolBar>

#include "about_dialog.h"
#include "colophon_dialog.h"
#include "keyboard_shortcuts_dialog.h"
#include "preferences_dialog.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_documentArea(new QMdiArea)
{
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/16/tabulator.svg")));

    createActions();
    createMenus();
    createToolbars();

    readSettings();

    updateActionFullScreen();
    updateMenuOpenRecent();
    updateMenuOpenRecentItems();

    // Central widget
    m_documentArea->setViewMode(QMdiArea::TabbedView);
    m_documentArea->setTabsMovable(true);
    m_documentArea->setTabsClosable(true);
    setCentralWidget(m_documentArea);
}

MainWindow::~MainWindow()
{
}


void MainWindow::createActions()
{
    // Actions: Application
    m_actionAbout = new QAction(tr("About %1").arg(QApplication::applicationName()), this);
    m_actionAbout->setObjectName(QStringLiteral("actionAbout"));
    m_actionAbout->setIcon(QIcon(QStringLiteral(":/icons/apps/16/tabulator.svg")));
    m_actionAbout->setIconText(tr("About"));
    m_actionAbout->setToolTip(tr("Brief description of the application"));
    connect(m_actionAbout, &QAction::triggered, this, &MainWindow::onActionAboutTriggered);

    m_actionColophon = new QAction(tr("Colophon"), this);
    m_actionColophon->setObjectName(QStringLiteral("actionColophon"));
    m_actionColophon->setIconText(tr("Colophon"));
    m_actionColophon->setToolTip(tr("Lengthy description of the application"));
    connect(m_actionColophon, &QAction::triggered, this, &MainWindow::onActionColophonTriggered);

    m_actionPreferences = new QAction(tr("Preferences…"), this);
    m_actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
    m_actionPreferences->setIcon(QIcon::fromTheme(QStringLiteral("configure"), QIcon(QStringLiteral(":/icons/actions/16/configure.svg"))));
    m_actionPreferences->setIconText(tr("Preferences"));
    m_actionPreferences->setToolTip(tr("Customize the appearance and behavior of the application"));
    connect(m_actionPreferences, &QAction::triggered, this, &MainWindow::onActionPreferencesTriggered);

    m_actionQuit = new QAction(tr("Quit"), this);
    m_actionQuit->setObjectName(QStringLiteral("actionQuit"));
    m_actionQuit->setIcon(QIcon::fromTheme(QStringLiteral("application-exit"), QIcon(QStringLiteral(":/icons/actions/16/application-exit.svg"))));
    m_actionQuit->setIconText(tr("Quit"));
    m_actionQuit->setShortcut(QKeySequence::Quit);
    m_actionQuit->setToolTip(tr("Quit the application [%1]").arg(m_actionQuit->shortcut().toString(QKeySequence::NativeText)));
    m_actionQuit->setData(tr("Quit the application"));
    connect(m_actionQuit, &QAction::triggered, this, &MainWindow::close);

    // Actions: Document
    m_actionNew = new QAction(tr("New"), this);
    m_actionNew->setObjectName(QStringLiteral("actionNew"));
    m_actionNew->setIcon(QIcon::fromTheme(QStringLiteral("document-new"), QIcon(QStringLiteral(":/icons/actions/16/document-new.svg"))));
    m_actionNew->setIconText(tr("New"));
    m_actionNew->setShortcut(QKeySequence::New);
    m_actionNew->setToolTip(tr("Create new document [%1]").arg(m_actionNew->shortcut().toString(QKeySequence::NativeText)));
    m_actionNew->setData(tr("Create new document"));
    connect(m_actionNew, &QAction::triggered, this, &MainWindow::onActionNewTriggered);

    m_actionOpen = new QAction(tr("Open…"), this);
    m_actionOpen->setObjectName(QStringLiteral("actionOpen"));
    m_actionOpen->setIcon(QIcon::fromTheme(QStringLiteral("document-open"), QIcon(QStringLiteral(":/icons/actions/16/document-open.svg"))));
    m_actionOpen->setIconText(tr("Open"));
    m_actionOpen->setShortcut(QKeySequence::Open);
    m_actionOpen->setToolTip(tr("Open an existing document [%1]").arg(m_actionOpen->shortcut().toString(QKeySequence::NativeText)));
    m_actionOpen->setData(tr("Open an existing document"));
    connect(m_actionOpen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);

    m_actionOpenRecentClear = new QAction(tr("Clear List"), this);
    m_actionOpenRecentClear->setObjectName(QStringLiteral("actionOpenRecentClear"));
    m_actionOpenRecentClear->setToolTip(tr("Clear document list"));
    connect(m_actionOpenRecentClear, &QAction::triggered, this, &MainWindow::onActionOpenRecentClearTriggered);

    // Actions: View
    m_actionFullScreen = new QAction(this);
    m_actionFullScreen->setIconText(tr("Full Screen"));
    m_actionFullScreen->setCheckable(true);
    m_actionFullScreen->setShortcuts(QList<QKeySequence>() << QKeySequence(Qt::Key_F11) << QKeySequence::FullScreen);
    m_actionFullScreen->setData(tr("Display the window in full screen"));
    connect(m_actionFullScreen, &QAction::triggered, this, &MainWindow::onActionFullScreenTriggered);

    m_actionToolbarApplication = new QAction(tr("Show Application Toolbar"), this);
    m_actionToolbarApplication->setObjectName(QStringLiteral("actionToolbarApplication"));
    m_actionToolbarApplication->setCheckable(true);
    m_actionToolbarApplication->setToolTip(tr("Display the Application toolbar"));
    connect(m_actionToolbarApplication, &QAction::toggled, [=](bool checked) { m_toolbarApplication->setVisible(checked); });

    m_actionToolbarDocument = new QAction(tr("Show Document Toolbar"), this);
    m_actionToolbarDocument->setObjectName(QStringLiteral("actionToolbarDocument"));
    m_actionToolbarDocument->setCheckable(true);
    m_actionToolbarDocument->setToolTip(tr("Display the Document toolbar"));
    connect(m_actionToolbarDocument, &QAction::toggled, [=](bool checked) { m_toolbarDocument->setVisible(checked); });

    m_actionToolbarEdit = new QAction(tr("Show Edit Toolbar"), this);
    m_actionToolbarEdit->setObjectName(QStringLiteral("actionToolbarEdit"));
    m_actionToolbarEdit->setCheckable(true);
    m_actionToolbarEdit->setToolTip(tr("Display the Edit toolbar"));
    connect(m_actionToolbarEdit, &QAction::toggled, [=](bool checked) { m_toolbarEdit->setVisible(checked); });

    m_actionToolbarTools = new QAction(tr("Show Tools Toolbar"), this);
    m_actionToolbarTools->setObjectName(QStringLiteral("actionToolbarTools"));
    m_actionToolbarTools->setCheckable(true);
    m_actionToolbarTools->setToolTip(tr("Display the Tools toolbar"));
    connect(m_actionToolbarTools, &QAction::toggled, [=](bool checked) { m_toolbarTools->setVisible(checked); });

    m_actionToolbarView = new QAction(tr("Show View Toolbar"), this);
    m_actionToolbarView->setObjectName(QStringLiteral("actionToolbarView"));
    m_actionToolbarView->setCheckable(true);
    m_actionToolbarView->setToolTip(tr("Display the View toolbar"));
    connect(m_actionToolbarView, &QAction::toggled, [=](bool checked) { m_toolbarView->setVisible(checked); });

    // Actions: Help
    m_actionKeyboardShortcuts = new QAction(tr("Keyboard Shortcuts"), this);
    m_actionKeyboardShortcuts->setIcon(QIcon::fromTheme(QStringLiteral("help-keyboard-shortcuts"), QIcon(QStringLiteral(":/icons/actions/16/help-keyboard-shortcuts.svg"))));
    m_actionKeyboardShortcuts->setToolTip(tr("List of all keyboard shortcuts"));
    connect(m_actionKeyboardShortcuts, &QAction::triggered, this, &MainWindow::onActionKeyboardShortcutsTriggered);
}


void MainWindow::updateActionRecentDocuments()
{
    m_actionRecentDocuments.clear();

    QAction *actionRecentDocument;
    for (int i = 1; i <= m_settings.maximumRecentDocuments(); i++) {

        actionRecentDocument = new QAction(this);
        actionRecentDocument->setVisible(false);
        connect(actionRecentDocument, &QAction::triggered, this, [=]() { this->onActionOpenRecentDocumentTriggered(actionRecentDocument->data().toString()); });

        m_actionRecentDocuments.append(actionRecentDocument);
    }
}


void MainWindow::updateActionFullScreen()
{
    if (!isFullScreen()) {
        m_actionFullScreen->setText(tr("Full Screen Mode"));
        m_actionFullScreen->setIcon(QIcon::fromTheme(QStringLiteral("view-fullscreen"), QIcon(QStringLiteral(":/icons/actions/16/view-fullscreen.svg"))));
        m_actionFullScreen->setChecked(false);
        m_actionFullScreen->setToolTip(tr("Display the window in full screen [%1]").arg(m_actionFullScreen->shortcut().toString(QKeySequence::NativeText)));
    }
    else {
        m_actionFullScreen->setText(tr("Exit Full Screen Mode"));
        m_actionFullScreen->setIcon(QIcon::fromTheme(QStringLiteral("view-restore"), QIcon(QStringLiteral(":/icons/actions/16/view-restore.svg"))));
        m_actionFullScreen->setChecked(true);
        m_actionFullScreen->setToolTip(tr("Exit the full screen mode [%1]").arg(m_actionFullScreen->shortcut().toString(QKeySequence::NativeText)));
    }
}


void MainWindow::createMenus()
{
    // Menu: Application
    auto *menuApplication = menuBar()->addMenu(tr("Application"));
    menuApplication->setObjectName(QStringLiteral("menuApplication"));
    menuApplication->addAction(m_actionAbout);
    menuApplication->addAction(m_actionColophon);
    menuApplication->addSeparator();
    menuApplication->addAction(m_actionPreferences);
    menuApplication->addSeparator();
    menuApplication->addAction(m_actionQuit);

    // Menu: Document
    m_menuOpenRecent = new QMenu(tr("Open Recent"), this);
    m_menuOpenRecent->setIcon(QIcon::fromTheme(QStringLiteral("document-open-recent"), QIcon(QStringLiteral(":/icons/actions/16/document-open-recent.svg"))));
    m_menuOpenRecent->setToolTip(tr("Open a document which was recently opened"));

    auto *menuDocument = menuBar()->addMenu(tr("Document"));
    menuDocument->setObjectName(QStringLiteral("menuEdit"));
    menuDocument->addAction(m_actionNew);
    menuDocument->addSeparator();
    menuDocument->addAction(m_actionOpen);
    menuDocument->addMenu(m_menuOpenRecent);

    // Menu: Edit
    auto *menuEdit = menuBar()->addMenu(tr("Edit"));
    menuEdit->setObjectName(QStringLiteral("menuEdit"));

    // Menu: Tools
    auto *menuTools = menuBar()->addMenu(tr("Tools"));
    menuTools->setObjectName(QStringLiteral("menuTools"));

    // Menu: View
    auto *menuView = menuBar()->addMenu(tr("View"));
    menuView->setObjectName(QStringLiteral("menuView"));
    menuView->addAction(m_actionFullScreen);
    menuView->addSeparator();
    menuView->addAction(m_actionToolbarApplication);
    menuView->addAction(m_actionToolbarDocument);
    menuView->addAction(m_actionToolbarEdit);
    menuView->addAction(m_actionToolbarTools);
    menuView->addAction(m_actionToolbarView);

    // Menu: Help
    auto *menuHelp = menuBar()->addMenu(tr("Help"));
    menuHelp->setObjectName(QStringLiteral("menuHelp"));
    menuHelp->addAction(m_actionKeyboardShortcuts);
}


void MainWindow::updateMenuOpenRecent()
{
    // Update menu only if necessary
    if (m_settings.maximumRecentDocuments() == m_actionRecentDocuments.count())
        return;

    updateActionRecentDocuments();

    m_menuOpenRecent->clear();

    for (QAction *actionRecentDocument : m_actionRecentDocuments)
        m_menuOpenRecent->addAction(actionRecentDocument);

    m_menuOpenRecent->addSeparator();
    m_menuOpenRecent->addAction(m_actionOpenRecentClear);
}


void MainWindow::updateMenuOpenRecentItems()
{
    while (m_recentDocuments.count() > m_settings.maximumRecentDocuments())
        m_recentDocuments.removeLast();

    if (m_settings.maximumRecentDocuments() > 0) {

        if (!m_recentDocuments.isEmpty()) {

            for (int i = 0; i < m_actionRecentDocuments.count(); i++) {

                if (i < m_recentDocuments.count()) {
                    QString text = QStringLiteral("%1 [%2]").arg(QFileInfo(m_recentDocuments.at(i)).fileName(), m_recentDocuments.at(i));
                    QString data = m_recentDocuments.at(i);

                    m_actionRecentDocuments.at(i)->setText(text);
                    m_actionRecentDocuments.at(i)->setData(data);
                    m_actionRecentDocuments.at(i)->setVisible(true);
                }
                else {
                    m_actionRecentDocuments.at(i)->setVisible(false);
                }
            }

            m_menuOpenRecent->setEnabled(true);
        }
        else {
            // Document list is empty; disable the menu.
            m_menuOpenRecent->setDisabled(true);
        }

        m_menuOpenRecent->menuAction()->setVisible(true);
    }
    else {
        // No document list wanted; hide the menu.
        m_menuOpenRecent->menuAction()->setVisible(false);
    }
}


void MainWindow::createToolbars()
{
    // Toolbar: Application
    m_toolbarApplication = addToolBar(tr("Application Toolbar"));
    m_toolbarApplication->setObjectName(QStringLiteral("toolbarApplication"));
    m_toolbarApplication->addAction(m_actionAbout);
    m_toolbarApplication->addAction(m_actionPreferences);
    m_toolbarApplication->addSeparator();
    m_toolbarApplication->addAction(m_actionQuit);
    connect(m_toolbarApplication, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarApplication->setChecked(visible); });

    // Toolbar: Document
    m_toolbarDocument = addToolBar(tr("Document Toolbar"));
    m_toolbarDocument->setObjectName(QStringLiteral("toolbarDocument"));
    m_toolbarDocument->addAction(m_actionNew);
    m_toolbarDocument->addAction(m_actionOpen);
    connect(m_toolbarDocument, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarDocument->setChecked(visible); });

    // Toolbar: Edit
    m_toolbarEdit = addToolBar(tr("Edit Toolbar"));
    m_toolbarEdit->setObjectName(QStringLiteral("toolbarEdit"));
    connect(m_toolbarEdit, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarEdit->setChecked(visible); });

    // Toolbar: Tools
    m_toolbarTools = addToolBar(tr("Tools Toolbar"));
    m_toolbarTools->setObjectName(QStringLiteral("toolbarTools"));
    connect(m_toolbarTools, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarTools->setChecked(visible); });

    // Toolbar: View
    m_toolbarView = addToolBar(tr("View Toolbar"));
    m_toolbarView->setObjectName(QStringLiteral("toolbarView"));
    m_toolbarView->addAction(m_actionFullScreen);
    connect(m_toolbarView, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarView->setChecked(visible); });
}


void MainWindow::readSettings()
{
    QSettings settings;

    m_settings.load(settings);

    // Recent documents
    int size = settings.beginReadArray(QStringLiteral("recentDocuments"));
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        m_recentDocuments.append(settings.value(QStringLiteral("document")).toString());
    }
    settings.endArray();

    // Application and dialog properties
    const auto applicationGeometry = settings.value(QStringLiteral("Application/geometry"), QByteArray()).toByteArray();
    const auto applicationState = settings.value(QStringLiteral("Application/state"), QByteArray()).toByteArray();
    m_aboutDialogGeometry = settings.value(QStringLiteral("AboutDialog/geometry"), QByteArray()).toByteArray();
    m_colophonDialogGeometry = settings.value(QStringLiteral("ColophonDialog/geometry"), QByteArray()).toByteArray();
    m_keyboardShortcutsDialogGeometry = settings.value(QStringLiteral("KeyboardShortcutsDialog/geometry"), QByteArray()).toByteArray();
    m_preferencesDialogGeometry = settings.value(QStringLiteral("PreferencesDialog/geometry"), QByteArray()).toByteArray();

    // Set application properties
    const auto geometry = m_settings.restoreApplicationGeometry() ? applicationGeometry : QByteArray();
    const auto state = m_settings.restoreApplicationState() ? applicationState : QByteArray();
    setApplicationGeometry(geometry);
    setApplicationState(state);
}


void MainWindow::writeSettings()
{
    QSettings settings;

    m_settings.save(settings);

    // Recent documents
    settings.remove(QStringLiteral("recentDocuments"));
    settings.beginWriteArray(QStringLiteral("recentDocuments"));
    for (int i = 0; i < m_recentDocuments.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue(QStringLiteral("document"), m_recentDocuments.at(i));
    }
    settings.endArray();

    // Application and dialog properties
    const auto geometry = m_settings.restoreApplicationGeometry() ? applicationGeometry() : QByteArray();
    const auto state = m_settings.restoreApplicationState() ? applicationState() : QByteArray();
    settings.setValue(QStringLiteral("Application/geometry"), geometry);
    settings.setValue(QStringLiteral("Application/state"), state);
    settings.setValue(QStringLiteral("AboutDialog/geometry"), m_aboutDialogGeometry);
    settings.setValue(QStringLiteral("ColophonDialog/geometry"), m_colophonDialogGeometry);
    settings.setValue(QStringLiteral("KeyboardShortcutsDialog/geometry"), m_keyboardShortcutsDialogGeometry);
    settings.setValue(QStringLiteral("PreferencesDialog/geometry"), m_preferencesDialogGeometry);
}


void MainWindow::setApplicationGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() * 2/3, availableGeometry.height() * 2/3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}


QByteArray MainWindow::applicationGeometry() const
{
    return saveGeometry();
}


void MainWindow::setApplicationState(const QByteArray &state)
{
    if (!state.isEmpty()) {
        restoreState(state);
    }
    else {
        m_toolbarApplication->setVisible(true);
        m_toolbarDocument->setVisible(true);
        m_toolbarEdit->setVisible(false);
        m_toolbarTools->setVisible(false);
        m_toolbarView->setVisible(true);
    }
}


QByteArray MainWindow::applicationState() const
{
    return saveState();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}


DocumentTable *MainWindow::createDocumentChild()
{
    DocumentTable *document = new DocumentTable;
    document->setSettings(m_settings);
    m_documentArea->addSubWindow(document);

    return document;
}


QMdiSubWindow *MainWindow::findDocumentChild(const QString &file) const
{
    const QList<QMdiSubWindow *> windows = m_documentArea->subWindowList();
    for (QMdiSubWindow *window : windows) {

        DocumentTable *document = qobject_cast<DocumentTable *>(window->widget());
        if (QFileInfo(document->file()).canonicalFilePath() == QFileInfo(file).canonicalFilePath())
            return window;
    }

    return nullptr;
}


DocumentTable *MainWindow::activeDocumentChild() const
{
    if (QMdiSubWindow *window = m_documentArea->activeSubWindow())
        return qobject_cast<DocumentTable *>(window->widget());

    return nullptr;
}


bool MainWindow::openDocument(const QString &fileName)
{
    const QString &file = QFileInfo(fileName).absoluteFilePath();

    // Checks whether the given document is already open.
    if (QMdiSubWindow *window = findDocumentChild(file)) {
        m_documentArea->setActiveSubWindow(window);
        updateRecentDocuments(file);
        return true;
    }

    const bool succeeded = loadDocument(file);
    if (succeeded)
        statusBar()->showMessage(QStringLiteral("Document loaded"), 3000);

    return succeeded;
}


bool MainWindow::loadDocument(const QString &file)
{
    DocumentTable *document = createDocumentChild();

    const bool succeeded = document->loadDocument(file);
    if (succeeded) {
        document->show();
        updateRecentDocuments(file);
    }
    else {
        document->close();
    }

    return succeeded;
}


void MainWindow::updateRecentDocuments(const QString &file)
{
    m_recentDocuments.removeOne(file);
    m_recentDocuments.prepend(file);

    updateMenuOpenRecentItems();
}


void MainWindow::onActionAboutTriggered()
{
    const auto geometry = m_settings.restoreDialogGeometry() ? m_aboutDialogGeometry : QByteArray();

    AboutDialog dialog(this);
    dialog.setDialogGeometry(geometry);
    dialog.exec();

    m_aboutDialogGeometry = m_settings.restoreDialogGeometry() ? dialog.dialogGeometry() : QByteArray();
}


void MainWindow::onActionColophonTriggered()
{
    const auto geometry = m_settings.restoreDialogGeometry() ? m_colophonDialogGeometry : QByteArray();

    ColophonDialog dialog(this);
    dialog.setDialogGeometry(geometry);
    dialog.exec();

    m_colophonDialogGeometry = m_settings.restoreDialogGeometry() ? dialog.dialogGeometry() : QByteArray();
}


void MainWindow::onActionPreferencesTriggered()
{
    const auto geometry = m_settings.restoreDialogGeometry() ? m_preferencesDialogGeometry : QByteArray();

    PreferencesDialog dialog(this);
    dialog.setDialogGeometry(geometry);
    dialog.setSettings(m_settings);
    dialog.exec();

    m_settings = dialog.settings();
    m_preferencesDialogGeometry = m_settings.restoreDialogGeometry() ? dialog.dialogGeometry() : QByteArray();

    updateMenuOpenRecent();
    updateMenuOpenRecentItems();
}


void MainWindow::onActionNewTriggered()
{
    DocumentTable *document = createDocumentChild();
    document->newDocument();
    document->show();
}


void MainWindow::onActionOpenTriggered()
{
    const QStringList fileNames = QFileDialog::getOpenFileNames(this, QStringLiteral("Open Document"),
                                      QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                                      QStringLiteral("CSV Files (*.csv);;All Files (*.*)"));

    for (const QString &fileName : fileNames)
        openDocument(fileName);
}


void MainWindow::onActionOpenRecentDocumentTriggered(const QString file)
{
    openDocument(file);
}


void MainWindow::onActionOpenRecentClearTriggered()
{
    m_recentDocuments.clear();

    updateMenuOpenRecentItems();
}


void MainWindow::onActionFullScreenTriggered()
{
    if (!isFullScreen())
        setWindowState(windowState() | Qt::WindowFullScreen);
    else
        setWindowState(windowState() & ~Qt::WindowFullScreen);

    updateActionFullScreen();
}


void MainWindow::onActionKeyboardShortcutsTriggered()
{
    if (!m_keyboardShortcutsDialog) {
        const auto geometry = m_settings.restoreDialogGeometry() ? m_keyboardShortcutsDialogGeometry : QByteArray();

        m_keyboardShortcutsDialog = new KeyboardShortcutsDialog(this);
        m_keyboardShortcutsDialog->setDialogGeometry(geometry);
        connect(m_keyboardShortcutsDialog, &KeyboardShortcutsDialog::finished, this, &MainWindow::onDialogKeyboardShortcutsFinished);
    }
    m_keyboardShortcutsDialog->show();
    m_keyboardShortcutsDialog->raise();
    m_keyboardShortcutsDialog->activateWindow();
}


void MainWindow::onDialogKeyboardShortcutsFinished()
{
    m_keyboardShortcutsDialogGeometry = m_settings.restoreDialogGeometry() ? m_keyboardShortcutsDialog->dialogGeometry() : QByteArray();
}
