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

#include "keyboard_shortcuts_widget.h"

#include <QAction>
#include <QHeaderView>
#include <QTableWidget>
#include <QVBoxLayout>


KeyboardShortcutsWidget::KeyboardShortcutsWidget(QWidget *mainWindow, QWidget *parent) :
    QWidget(parent)
{
    QStringList listHHeaderLabels = { QStringLiteral("Name"), QStringLiteral("Shortcut"), QStringLiteral("Description") };

    QList<QAction *> listShortcutActionItems;
    QList<QAction *> listActionItems = mainWindow->findChildren<QAction *>(QString(), Qt::FindDirectChildrenOnly);
    foreach (QAction *actionItem, listActionItems) {
        if (!actionItem->shortcut().isEmpty()) {
            listShortcutActionItems << actionItem;
        }
    }

    QTableWidget *tableBox = new QTableWidget(listShortcutActionItems.size(), listHHeaderLabels.size(), this);
    tableBox->setHorizontalHeaderLabels(listHHeaderLabels);
    tableBox->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    tableBox->horizontalHeader()->setStretchLastSection(true);
    tableBox->verticalHeader()->setVisible(false);
    tableBox->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableBox->setSelectionMode(QAbstractItemView::NoSelection);
    tableBox->setFocusPolicy(Qt::NoFocus);

    for (int index = 0; index < listShortcutActionItems.size(); index++) {
        tableBox->setItem(index, 0, new QTableWidgetItem(listShortcutActionItems[index]->icon(), listShortcutActionItems[index]->text()));
        tableBox->setItem(index, 1, new QTableWidgetItem(listShortcutActionItems[index]->shortcut().toString(QKeySequence::NativeText)));
        tableBox->setItem(index, 2, new QTableWidgetItem(listShortcutActionItems[index]->data().toString()));
    }

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tableBox, 1);

    setLayout(layout);
}
