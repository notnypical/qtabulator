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
#include "preferences_dialog.h"

#include <QApplication>
#include <QMenuBar>
#include <QScreen>
#include <QSettings>
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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

    // Read user preferences
    const bool geometryWindowRestore = settings.value(QStringLiteral("Settings/geometryWindowRestore"), true).toBool();

    // Set window properties
    const QByteArray geometry = settings.value(QStringLiteral("MainWindow/geometry"), QByteArray()).toByteArray();
    if (geometryWindowRestore && !geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
    restoreState(settings.value(QStringLiteral("MainWindow/state"), QByteArray()).toByteArray());
}


/**
 * Saves user preferences and other application properties.
 */
void MainWindow::writeSettings()
{
    QSettings settings;

    // Store window properties
    settings.setValue(QStringLiteral("MainWindow/geometry"), saveGeometry());
    settings.setValue(QStringLiteral("MainWindow/state"), saveState());
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
 * Displays the About dialog.
 */
void MainWindow::onActionAboutTriggered()
{
    AboutDialog *aboutDialog = new AboutDialog(this);
    aboutDialog->setWindowTitle(QStringLiteral("About %1").arg(QApplication::applicationName()));
    aboutDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    aboutDialog->exec();
}


/**
 * Displays the Colophon dialog.
 */
void MainWindow::onActionColophonTriggered()
{
    ColophonDialog *colophonDialog = new ColophonDialog(this);
    colophonDialog->setWindowTitle(QStringLiteral("Colophon"));
    colophonDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    colophonDialog->exec();
}


/**
 * Displays the Preferences dialog.
 */
void MainWindow::onActionPreferencesTriggered()
{
    PreferencesDialog *preferencesDialog = new PreferencesDialog(this);
    preferencesDialog->setWindowTitle(QStringLiteral("Preferences"));
    preferencesDialog->exec();
}


/**
 * Fires the Close event to terminate the application.
 */
void MainWindow::onActionQuitTriggered()
{
    close();
}
