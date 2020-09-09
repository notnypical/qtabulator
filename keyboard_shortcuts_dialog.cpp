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

#include "keyboard_shortcuts_dialog.h"

#include <QDialogButtonBox>
#include <QScreen>
#include <QSettings>
#include <QVBoxLayout>


KeyboardShortcutsDialog::KeyboardShortcutsDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUI();
    readSettings();
}


/**
 * Sets up the user interface.
 */
void KeyboardShortcutsDialog::setupUI()
{
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &KeyboardShortcutsDialog::close);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QWidget(), 1);
    layout->addWidget(buttonBox);

    setLayout(layout);
}


/**
 * Restores user preferences and other dialog properties.
 */
void KeyboardShortcutsDialog::readSettings()
{
    QSettings settings;

    // Read user preferences
    const bool geometryDialogRestore = settings.value(QStringLiteral("Settings/geometryDialogRestore"), true).toBool();

    // Set dialog properties
    const QByteArray geometry = settings.value(QStringLiteral("KeyboardShortcutsDialog/geometry"), QByteArray()).toByteArray();
    if (geometryDialogRestore && !geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}


/**
 * Saves user preferences and other dialog properties.
 */
void KeyboardShortcutsDialog::writeSettings()
{
    QSettings settings;

    // Store dialog properties
    settings.setValue(QStringLiteral("KeyboardShortcutsDialog/geometry"), saveGeometry());
}


/**
 * Processes the Close event.
 */
void KeyboardShortcutsDialog::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}
