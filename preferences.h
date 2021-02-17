/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of Tabulator-Qt.
 *
 * Tabulator-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tabulator-Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tabulator-Qt.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QSettings>


class Preferences
{
public:

    enum struct HeaderLabel {
        Custom = 0,
        Binary = 2,
        Octal = 8,
        Decimal = 10,
        Hexadecimal = 16,
        Letter = 26,
    };

    Preferences();

    void load(QSettings &settings);
    void save(QSettings &settings);

    void setRestoreApplicationState(bool value);
    bool restoreApplicationState(bool isDefault = false);

    void setRestoreApplicationGeometry(bool value);
    bool restoreApplicationGeometry(bool isDefault = false);

    void setRestoreDialogGeometry(bool value);
    bool restoreDialogGeometry(bool isDefault = false);

    void setMaximumRecentDocuments(int value);
    int maximumRecentDocuments(bool isDefault = false);

    void setDefaultHeaderLabelHorizontal(HeaderLabel value);
    HeaderLabel defaultHeaderLabelHorizontal(bool isDefault = false);

    void setDefaultHeaderLabelVertical(HeaderLabel value);
    HeaderLabel defaultHeaderLabelVertical(bool isDefault = false);

    void setDefaultCellCountColumn(int value);
    int defaultCellCountColumn(bool isDefault = false);

    void setDefaultCellCountRow(int value);
    int defaultCellCountRow(bool isDefault = false);

private:
    bool m_restoreApplicationState;
    bool m_restoreApplicationGeometry;
    bool m_restoreDialogGeometry;

    int m_maximumRecentDocuments;

    HeaderLabel m_defaultHeaderLabelHorizontal;
    HeaderLabel m_defaultHeaderLabelVertical;

    int m_defaultCellCountColumn;
    int m_defaultCellCountRow;
};

#endif // PREFERENCES_H
