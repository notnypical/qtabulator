/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
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

#include "keyboard_shortcuts_page.h"

#include <QAction>
#include <QHeaderView>
#include <QTableWidget>


KeyboardShortcutsPage::KeyboardShortcutsPage(QWidget *mainWindow, QWidget *parent)
    : QWidget(parent)
{
    QStringList listHeaderLabels = { tr("Name"), tr("Shortcut"), tr("Description") };

    auto *tableBox = new QTableWidget(0, listHeaderLabels.size(), this);
    tableBox->setHorizontalHeaderLabels(listHeaderLabels);
    tableBox->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    tableBox->horizontalHeader()->setStretchLastSection(true);
    tableBox->verticalHeader()->setVisible(false);
    tableBox->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableBox->setSelectionMode(QAbstractItemView::NoSelection);
    tableBox->setFocusPolicy(Qt::NoFocus);

    QList<QAction *> listActionItems = mainWindow->findChildren<QAction *> (QString(), Qt::FindDirectChildrenOnly);
    for (auto *actionItem : listActionItems) {

        if (!actionItem->shortcut().isEmpty()) {
            int idx = tableBox->rowCount();

            tableBox->setRowCount(idx + 1);
            tableBox->setItem(idx, 0, new QTableWidgetItem(actionItem->icon(), actionItem->text()));
            tableBox->setItem(idx, 1, new QTableWidgetItem(actionItem->shortcut().toString(QKeySequence::NativeText)));
            tableBox->setItem(idx, 2, new QTableWidgetItem(actionItem->data().toString()));
        }
    }
    tableBox->resizeColumnsToContents();

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(tableBox);
}


QString KeyboardShortcutsPage::title() const
{
    return tr("Keyboard Shortcuts");
}


void KeyboardShortcutsPage::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}
