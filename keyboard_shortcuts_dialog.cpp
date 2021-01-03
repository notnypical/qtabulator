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
#include <QVBoxLayout>

#include "keyboard_shortcuts_page.h"


KeyboardShortcutsDialog::KeyboardShortcutsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Keyboard Shortcuts"));

    setDialogGeometry();

    // Content
    auto *keyboardShortcutsPage = new KeyboardShortcutsPage(parentWidget());
    keyboardShortcutsPage->setZeroMargins();

    // Button box
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &KeyboardShortcutsDialog::close);

    // Main layout
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(keyboardShortcutsPage);
    layout->addWidget(buttonBox);
}


void KeyboardShortcutsDialog::setDialogGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty())
        restoreGeometry(geometry);
    else
        resize(640, 480);
}


QByteArray KeyboardShortcutsDialog::dialogGeometry() const
{
    return saveGeometry();
}
