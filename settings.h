/**
 * Copyright 2020 NotNypical, <https://notnypical.github.io>.
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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>


const bool RESTORE_APPLICATION_STATE_DEFAULT = true;
const bool RESTORE_APPLICATION_GEOMETRY_DEFAULT = true;
const bool RESTORE_DIALOG_GEOMETRY_DEFAULT = true;

const int MAXIMUM_RECENT_DOCUMENTS_DEFAULT = 10;
const int MAXIMUM_RECENT_DOCUMENTS_MINIMUM = 0;
const int MAXIMUM_RECENT_DOCUMENTS_MAXIMUM = 25;


class Settings
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

    Settings();

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

    // Document: Defaults
    HeaderLabel defaultHeaderLabelHorizontal = HeaderLabel::Letter;
    HeaderLabel defaultHeaderLabelVertical = HeaderLabel::Decimal;
    int defaultCellColumns = 25;
    int defaultCellRows = 50;

private:
    bool m_restoreApplicationState;
    bool m_restoreApplicationGeometry;
    bool m_restoreDialogGeometry;

    int m_maximumRecentDocuments;
};

#endif // SETTINGS_H
