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

#ifndef KEYBOARD_SHORTCUTS_PAGE_H
#define KEYBOARD_SHORTCUTS_PAGE_H

#include <QVBoxLayout>
#include <QWidget>


class KeyboardShortcutsPage : public QWidget
{
    Q_OBJECT

public:
    explicit KeyboardShortcutsPage(QWidget *mainWindow, QWidget *parent = nullptr);

    QString title() const;

    void setZeroMargins();

private:
    QVBoxLayout *m_layout;
};

#endif // KEYBOARD_SHORTCUTS_PAGE_H
