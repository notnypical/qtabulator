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

#include <QApplication>
#include <QMenuBar>
#include <QScreen>
#include <QSettings>
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/icons/apps/22/tabulator.svg"));

    createActions();
    createMenus();
    createStatusBar();

    readSettings();
}


MainWindow::~MainWindow()
{
}


/**
 * Creates user interface actions.
 */
void MainWindow::createActions()
{
    // Actions: Application
    const QIcon iconAbout = QIcon(":/icons/apps/16/tabulator.svg");
    actionAbout = new QAction(QString("About %1").arg(QApplication::applicationName()), this);
    actionAbout->setIcon(iconAbout);
    actionAbout->setStatusTip("Brief description of the application");
    actionAbout->setToolTip("Brief description of the application");
    connect(actionAbout, &QAction::triggered, this, &MainWindow::onActionAboutTriggered);

    actionColophon = new QAction("Colophon", this);
    actionColophon->setStatusTip("Lengthy description of the application");
    actionColophon->setToolTip("Lengthy description of the application");
    connect(actionColophon, &QAction::triggered, this, &MainWindow::onActionColophonTriggered);

    const QIcon iconPreferences = QIcon::fromTheme("configure", QIcon(":/icons/actions/16/configure.svg"));
    actionPreferences = new QAction("Preferences…", this);
    actionPreferences->setIcon(iconPreferences);
    actionPreferences->setStatusTip("Customize the appearance and behavior of the application");
    actionPreferences->setToolTip("Customize the appearance and behavior of the application");
    connect(actionPreferences, &QAction::triggered, this, &MainWindow::onActionPreferencesTriggered);

    const QIcon iconQuit = QIcon::fromTheme("application-exit", QIcon(":/icons/actions/16/application-exit.svg"));
    actionQuit = new QAction("Quit", this);
    actionQuit->setIcon(iconQuit);
    actionQuit->setShortcut(QKeySequence::Quit);
    actionQuit->setStatusTip("Quit the application");
    actionQuit->setToolTip("Quit the application");
    connect(actionQuit, &QAction::triggered, this, &MainWindow::onActionQuitTriggered);
}


/**
 * Creates groups of menu items.
 */
void MainWindow::createMenus()
{
    // Menu: Application
    QMenu *menuApplication = menuBar()->addMenu("Application");
    menuApplication->addAction(actionAbout);
    menuApplication->addAction(actionColophon);
    menuApplication->addSeparator();
    menuApplication->addAction(actionPreferences);
}


/**
 * Creates the status bar.
 */
void MainWindow::createStatusBar()
{
    statusBar()->showMessage("Ready", 3000);
}


/**
 * Restores user preferences and other application properties.
 */
void MainWindow::readSettings()
{
    QSettings settings;

    // Set window properties
    const QByteArray geometry = settings.value("MainWindow/geometry", QByteArray()).toByteArray();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
    restoreState(settings.value("MainWindow/state", QByteArray()).toByteArray());
}


/**
 * Saves user preferences and other application properties.
 */
void MainWindow::writeSettings()
{
    QSettings settings;

    // Store window properties
    settings.setValue("MainWindow/geometry", saveGeometry());
    settings.setValue("MainWindow/state", saveState());
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
}


/**
 * Displays the Colophon dialog.
 */
void MainWindow::onActionColophonTriggered()
{
}


/**
 * Displays the Preferences dialog.
 */
void MainWindow::onActionPreferencesTriggered()
{
}


/**
 * Fires the Close event to terminate the application.
 */
void MainWindow::onActionQuitTriggered()
{
}
