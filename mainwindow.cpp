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

#include "mainwindow.h"
#include "aboutdialog.h"
#include "colophondialog.h"
#include "preferencesdialog.h"

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
    const QIcon iconAbout = QIcon(QStringLiteral(":/icons/apps/16/tabulator.svg"));
    actionAbout = new QAction(QStringLiteral("About %1").arg(QApplication::applicationName()), this);
    actionAbout->setIcon(iconAbout);
    actionAbout->setStatusTip(QStringLiteral("Brief description of the application"));
    actionAbout->setToolTip(QStringLiteral("Brief description of the application"));
    connect(actionAbout, &QAction::triggered, this, &MainWindow::onActionAboutTriggered);

    actionColophon = new QAction(QStringLiteral("Colophon"), this);
    actionColophon->setStatusTip(QStringLiteral("Lengthy description of the application"));
    actionColophon->setToolTip(QStringLiteral("Lengthy description of the application"));
    connect(actionColophon, &QAction::triggered, this, &MainWindow::onActionColophonTriggered);

    const QIcon iconPreferences = QIcon::fromTheme(QStringLiteral("configure"), QIcon(QStringLiteral(":/icons/actions/16/configure.svg")));
    actionPreferences = new QAction(QStringLiteral("Preferences…"), this);
    actionPreferences->setIcon(iconPreferences);
    actionPreferences->setStatusTip(QStringLiteral("Customize the appearance and behavior of the application"));
    actionPreferences->setToolTip(QStringLiteral("Customize the appearance and behavior of the application"));
    connect(actionPreferences, &QAction::triggered, this, &MainWindow::onActionPreferencesTriggered);

    const QIcon iconQuit = QIcon::fromTheme(QStringLiteral("application-exit"), QIcon(QStringLiteral(":/icons/actions/16/application-exit.svg")));
    actionQuit = new QAction(QStringLiteral("Quit"), this);
    actionQuit->setIcon(iconQuit);
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

    // Set window properties
    const QByteArray geometry = settings.value(QStringLiteral("MainWindow/geometry"), QByteArray()).toByteArray();
    if (!geometry.isEmpty()) {
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
    AboutDialog aboutDialog;
    aboutDialog.exec();
}


/**
 * Displays the Colophon dialog.
 */
void MainWindow::onActionColophonTriggered()
{
    ColophonDialog colophonDialog;
    colophonDialog.exec();
}


/**
 * Displays the Preferences dialog.
 */
void MainWindow::onActionPreferencesTriggered()
{
    PreferencesDialog preferencesDialog;
    preferencesDialog.exec();
}


/**
 * Fires the Close event to terminate the application.
 */
void MainWindow::onActionQuitTriggered()
{
    close();
}
