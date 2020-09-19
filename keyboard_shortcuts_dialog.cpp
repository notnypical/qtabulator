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
#include "keyboard_shortcuts_widget.h"

#include <QDialogButtonBox>
#include <QScreen>
#include <QVBoxLayout>


KeyboardShortcutsDialog::KeyboardShortcutsDialog(QWidget *parent) :
    QDialog(parent)
{
    // Button box
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &KeyboardShortcutsDialog::close);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new KeyboardShortcutsWidget(parentWidget()), 1);
    layout->addWidget(buttonBox);

    setLayout(layout);
}


/**
 * Returns the geometry of the widget.
 */
QByteArray KeyboardShortcutsDialog::windowGeometry() const
{
    return saveGeometry();
}


/**
 * Sets the geometry of the widget.
 */
void KeyboardShortcutsDialog::setWindowGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}
