/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of Tabulator-Qt, <https://github.com/notnypical/tabulator-qt>.
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

#include "preferences.h"


Preferences::Preferences()
{
    // General: State & Geometries
    m_restoreApplicationState = true;
    m_restoreApplicationGeometry = true;
    m_restoreDialogGeometry = true;

    // Documents: Recently Opened Documents
    m_maximumRecentDocuments = 10;

    // Document Presets: Header Labels
    m_defaultHeaderLabelHorizontal = HeaderLabel::Letter;
    m_defaultHeaderLabelVertical = HeaderLabel::Decimal;

    // Document Presets: Cell Counts
    m_defaultCellCountColumn = 25;
    m_defaultCellCountRow = 50;
}


void Preferences::load(QSettings &settings)
{
    settings.beginGroup(QStringLiteral("Preferences"));

    // General: State & Geometries
    setRestoreApplicationState(settings.value(QStringLiteral("RestoreApplicationState"), true).toBool());
    setRestoreApplicationGeometry(settings.value(QStringLiteral("RestoreApplicationGeometry"), true).toBool());
    setRestoreDialogGeometry(settings.value(QStringLiteral("RestoreDialogGeometry"), true).toBool());

    // Documents: Recently Opened Documents
    setMaximumRecentDocuments(settings.value(QStringLiteral("MaximumRecentDocuments"), 10).toInt());

    // Document Presets: Header Labels
    setDefaultHeaderLabelHorizontal(static_cast<Preferences::HeaderLabel> (settings.value(QStringLiteral("DefaultHeaderLabelHorizontal"), (int) HeaderLabel::Letter).toInt()));
    setDefaultHeaderLabelVertical(static_cast<Preferences::HeaderLabel> (settings.value(QStringLiteral("DefaultHeaderLabelVertical"), (int) HeaderLabel::Decimal).toInt()));

    // Document Presets: Cell Counts
    setDefaultCellCountColumn(settings.value(QStringLiteral("DefaultCellCountColumn"), 25).toInt());
    setDefaultCellCountRow(settings.value(QStringLiteral("DefaultCellCountRow"), 50).toInt());

    settings.endGroup();
}


void Preferences::save(QSettings &settings)
{
    settings.beginGroup(QStringLiteral("Preferences"));
    settings.remove("");

    // General: State & Geometries
    settings.setValue(QStringLiteral("RestoreApplicationState"), m_restoreApplicationState);
    settings.setValue(QStringLiteral("RestoreApplicationGeometry"), m_restoreApplicationGeometry);
    settings.setValue(QStringLiteral("RestoreDialogGeometry"), m_restoreDialogGeometry);

    // Documents: Recently Opened Documents
    settings.setValue(QStringLiteral("MaximumRecentDocuments"), m_maximumRecentDocuments);

    // Document Presets: Header Labels
    settings.setValue(QStringLiteral("DefaultHeaderLabelHorizontal"), (int) m_defaultHeaderLabelHorizontal);
    settings.setValue(QStringLiteral("DefaultHeaderLabelVertical"), (int) m_defaultHeaderLabelVertical);

    // Document Presets: Cell Counts
    settings.setValue(QStringLiteral("DefaultCellCountColumn"), m_defaultCellCountColumn);
    settings.setValue(QStringLiteral("DefaultCellCountRow"), m_defaultCellCountRow);

    settings.endGroup();
}


void Preferences::setRestoreApplicationState(bool value)
{
    m_restoreApplicationState = value;
}


bool Preferences::restoreApplicationState(bool isDefault)
{
    if (isDefault)
        return true;

    return m_restoreApplicationState;
}


void Preferences::setRestoreApplicationGeometry(bool value)
{
    m_restoreApplicationGeometry = value;
}


bool Preferences::restoreApplicationGeometry(bool isDefault)
{
    if (isDefault)
        return true;

    return m_restoreApplicationGeometry;
}


void Preferences::setRestoreDialogGeometry(bool value)
{
    m_restoreDialogGeometry = value;
}


bool Preferences::restoreDialogGeometry(bool isDefault)
{
    if (isDefault)
        return true;

    return m_restoreDialogGeometry;
}


void Preferences::setMaximumRecentDocuments(int value)
{
    if (value >= 0 && value <= 25)
        m_maximumRecentDocuments = value;
    else
        m_maximumRecentDocuments = 10;
}


int Preferences::maximumRecentDocuments(bool isDefault)
{
    if (isDefault)
        return 10;

    return m_maximumRecentDocuments;
}


void Preferences::setDefaultHeaderLabelHorizontal(Preferences::HeaderLabel value)
{
    m_defaultHeaderLabelHorizontal = value;
}


Preferences::HeaderLabel Preferences::defaultHeaderLabelHorizontal(bool isDefault)
{
    if (isDefault)
        return HeaderLabel::Letter;

    return m_defaultHeaderLabelHorizontal;
}


void Preferences::setDefaultHeaderLabelVertical(Preferences::HeaderLabel value)
{
    m_defaultHeaderLabelVertical = value;
}


Preferences::HeaderLabel Preferences::defaultHeaderLabelVertical(bool isDefault)
{
    if (isDefault)
        return HeaderLabel::Decimal;

    return m_defaultHeaderLabelVertical;
}


void Preferences::setDefaultCellCountColumn(int value)
{
    if (value >= 1 && value <= 1000)
        m_defaultCellCountColumn = value;
    else
        m_defaultCellCountColumn = 25;
}


int Preferences::defaultCellCountColumn(bool isDefault)
{
    if (isDefault)
        return 25;

    return m_defaultCellCountColumn;
}


void Preferences::setDefaultCellCountRow(int value)
{
    if (value >= 1 && value <= 1000)
        m_defaultCellCountRow = value;
    else
        m_defaultCellCountRow = 50;
}


int Preferences::defaultCellCountRow(bool isDefault)
{
    if (isDefault)
        return 50;

    return m_defaultCellCountRow;
}
