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

#include "settings.h"


Settings::Settings()
{
    // General: State & Geometries
    m_restoreApplicationState = RESTORE_APPLICATION_STATE_DEFAULT;
    m_restoreApplicationGeometry = RESTORE_APPLICATION_GEOMETRY_DEFAULT;
    m_restoreDialogGeometry = RESTORE_DIALOG_GEOMETRY_DEFAULT;

    // Documents: Recently Opened Documents
    m_maximumRecentDocuments = MAXIMUM_RECENT_DOCUMENTS_DEFAULT;

    // Document Presets: Header Labels
    m_defaultHeaderLabelHorizontal = DEFAULT_HEADER_LABEL_HORIZONTAL_DEFAULT;
    m_defaultHeaderLabelVertical = DEFAULT_HEADER_LABEL_VERTICAL_DEFAULT;

    // Document Presets: Cell Counts
    m_defaultCellCountColumn = DEFAULT_CELL_COUNT_COLUMN_DEFAULT;
    m_defaultCellCountRow = DEFAULT_CELL_COUNT_ROW_DEFAULT;
}


void Settings::load(QSettings &settings)
{
    settings.beginGroup(QStringLiteral("Settings"));

    // General: State & Geometries
    setRestoreApplicationState(settings.value(QStringLiteral("restoreApplicationState"), RESTORE_APPLICATION_STATE_DEFAULT).toBool());
    setRestoreApplicationGeometry(settings.value(QStringLiteral("restoreApplicationGeometry"), RESTORE_APPLICATION_GEOMETRY_DEFAULT).toBool());
    setRestoreDialogGeometry(settings.value(QStringLiteral("restoreDialogGeometry"), RESTORE_DIALOG_GEOMETRY_DEFAULT).toBool());

    // Documents: Recently Opened Documents
    setMaximumRecentDocuments(settings.value(QStringLiteral("maximumRecentDocuments"), MAXIMUM_RECENT_DOCUMENTS_DEFAULT).toInt());

    // Document Presets: Header Labels
    setDefaultHeaderLabelHorizontal(static_cast<Settings::HeaderLabel> (settings.value(QStringLiteral("defaultHeaderLabelHorizontal"), (int) DEFAULT_HEADER_LABEL_HORIZONTAL_DEFAULT).toInt()));
    setDefaultHeaderLabelVertical(static_cast<Settings::HeaderLabel> (settings.value(QStringLiteral("defaultHeaderLabelVertical"), (int) DEFAULT_HEADER_LABEL_VERTICAL_DEFAULT).toInt()));

    // Document Presets: Cell Counts
    setDefaultCellCountColumn(settings.value(QStringLiteral("defaultCellCountColumn"), DEFAULT_CELL_COUNT_COLUMN_DEFAULT).toInt());
    setDefaultCellCountRow(settings.value(QStringLiteral("defaultCellCountRow"), DEFAULT_CELL_COUNT_ROW_DEFAULT).toInt());

    settings.endGroup();
}


void Settings::save(QSettings &settings)
{
    settings.remove(QStringLiteral("Settings"));

    settings.beginGroup(QStringLiteral("Settings"));

    // General: State & Geometries
    settings.setValue(QStringLiteral("restoreApplicationState"), m_restoreApplicationState);
    settings.setValue(QStringLiteral("restoreApplicationGeometry"), m_restoreApplicationGeometry);
    settings.setValue(QStringLiteral("restoreDialogGeometry"), m_restoreDialogGeometry);

    // Documents: Recently Opened Documents
    settings.setValue(QStringLiteral("maximumRecentDocuments"), m_maximumRecentDocuments);

    // Document Presets: Header Labels
    settings.setValue(QStringLiteral("defaultHeaderLabelHorizontal"), (int) m_defaultHeaderLabelHorizontal);
    settings.setValue(QStringLiteral("defaultHeaderLabelVertical"), (int) m_defaultHeaderLabelVertical);

    // Document Presets: Cell Counts
    settings.setValue(QStringLiteral("defaultCellCountColumn"), m_defaultCellCountColumn);
    settings.setValue(QStringLiteral("defaultCellCountRow"), m_defaultCellCountRow);

    settings.endGroup();
}


void Settings::setRestoreApplicationState(bool value)
{
    m_restoreApplicationState = value;
}


bool Settings::restoreApplicationState(bool isDefault)
{
    if (isDefault)
        return RESTORE_APPLICATION_STATE_DEFAULT;

    return m_restoreApplicationState;
}


void Settings::setRestoreApplicationGeometry(bool value)
{
    m_restoreApplicationGeometry = value;
}


bool Settings::restoreApplicationGeometry(bool isDefault)
{
    if (isDefault)
        return RESTORE_APPLICATION_GEOMETRY_DEFAULT;

    return m_restoreApplicationGeometry;
}


void Settings::setRestoreDialogGeometry(bool value)
{
    m_restoreDialogGeometry = value;
}


bool Settings::restoreDialogGeometry(bool isDefault)
{
    if (isDefault)
        return RESTORE_DIALOG_GEOMETRY_DEFAULT;

    return m_restoreDialogGeometry;
}


void Settings::setMaximumRecentDocuments(int value)
{
    if (value >= MAXIMUM_RECENT_DOCUMENTS_MINIMUM && value <= MAXIMUM_RECENT_DOCUMENTS_MAXIMUM)
        m_maximumRecentDocuments = value;
    else
        m_maximumRecentDocuments = MAXIMUM_RECENT_DOCUMENTS_DEFAULT;
}


int Settings::maximumRecentDocuments(bool isDefault)
{
    if (isDefault)
        return MAXIMUM_RECENT_DOCUMENTS_DEFAULT;

    return m_maximumRecentDocuments;
}


void Settings::setDefaultHeaderLabelHorizontal(Settings::HeaderLabel value)
{
    m_defaultHeaderLabelHorizontal = value;
}


Settings::HeaderLabel Settings::defaultHeaderLabelHorizontal(bool isDefault)
{
    if (isDefault)
        return DEFAULT_HEADER_LABEL_HORIZONTAL_DEFAULT;

    return m_defaultHeaderLabelHorizontal;
}


void Settings::setDefaultHeaderLabelVertical(Settings::HeaderLabel value)
{
    m_defaultHeaderLabelVertical = value;
}


Settings::HeaderLabel Settings::defaultHeaderLabelVertical(bool isDefault)
{
    if (isDefault)
        return DEFAULT_HEADER_LABEL_VERTICAL_DEFAULT;

    return m_defaultHeaderLabelVertical;
}


void Settings::setDefaultCellCountColumn(int value)
{
    if (value >= DEFAULT_CELL_COUNT_COLUMN_MINIMUM && value <= DEFAULT_CELL_COUNT_COLUMN_MAXIMUM)
        m_defaultCellCountColumn = value;
    else
        m_defaultCellCountColumn = DEFAULT_CELL_COUNT_COLUMN_DEFAULT;
}


int Settings::defaultCellCountColumn(bool isDefault)
{
    if (isDefault)
        return DEFAULT_CELL_COUNT_COLUMN_DEFAULT;

    return m_defaultCellCountColumn;
}


void Settings::setDefaultCellCountRow(int value)
{
    if (value >= DEFAULT_CELL_COUNT_ROW_MINIMUM && value <= DEFAULT_CELL_COUNT_ROW_MAXIMUM)
        m_defaultCellCountRow = value;
    else
        m_defaultCellCountRow = DEFAULT_CELL_COUNT_ROW_DEFAULT;
}


int Settings::defaultCellCountRow(bool isDefault)
{
    if (isDefault)
        return DEFAULT_CELL_COUNT_ROW_DEFAULT;

    return m_defaultCellCountRow;
}
