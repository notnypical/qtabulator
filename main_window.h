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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "settings.h"

#include <QAction>
#include <QCloseEvent>
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onActionAboutTriggered();
    void onActionColophonTriggered();
    void onActionPreferencesTriggered();
    void onActionQuitTriggered();

    void onActionFullScreenTriggered();

    void onActionKeyboardShortcutsTriggered();

private:
    void setupUI();
    void createActions();
    void updateActionFullScreen();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    Settings m_settings;
    void readSettings();
    void writeSettings();

    QAction *actionAbout;
    QAction *actionColophon;
    QAction *actionPreferences;
    QAction *actionQuit;

    QAction *actionFullScreen;

    QAction *actionKeyboardShortcuts;
};

#endif // MAIN_WINDOW_H
