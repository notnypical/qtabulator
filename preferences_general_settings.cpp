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

#include "preferences_general_settings.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>


PreferencesGeneralSettings::PreferencesGeneralSettings(QWidget *parent)
    : QWidget(parent)
{
    // Title
    auto *title = new QLabel(tr("<strong style=\"font-size:large;\">General Settings</strong>"));

    // State and geometries
    m_chkRestoreApplicationState = new QCheckBox(tr("Save and restore the application state"));
    connect(m_chkRestoreApplicationState, &QCheckBox::stateChanged, this, &PreferencesGeneralSettings::onSettingsChanged);

    m_chkRestoreApplicationGeometry = new QCheckBox(tr("Save and restore the application geometry"));
    connect(m_chkRestoreApplicationGeometry, &QCheckBox::stateChanged, this, &PreferencesGeneralSettings::onSettingsChanged);

    m_chkRestoreDialogGeometry = new QCheckBox(tr("Save and restore dialog geometry"));
    connect(m_chkRestoreDialogGeometry, &QCheckBox::stateChanged, this, &PreferencesGeneralSettings::onSettingsChanged);

    auto *stateGeometryLayout = new QVBoxLayout;
    stateGeometryLayout->addWidget(m_chkRestoreApplicationState);
    stateGeometryLayout->addWidget(m_chkRestoreApplicationGeometry);
    stateGeometryLayout->addWidget(m_chkRestoreDialogGeometry);

    auto *stateGeometryGroup = new QGroupBox(tr("State && Geometries"));
    stateGeometryGroup->setLayout(stateGeometryLayout);

    // Documents
    m_spbMaximumRecentDocuments = new QSpinBox(this);
    m_spbMaximumRecentDocuments->setRange(0, 25);
    m_spbMaximumRecentDocuments->setToolTip(tr("Maximum number of recently opened documents."));
    connect(m_spbMaximumRecentDocuments, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesGeneralSettings::onSettingsChanged);

    auto *documentsLayout = new QFormLayout;
    documentsLayout->addRow(tr("Number of documents"), m_spbMaximumRecentDocuments);

    auto *documentsGroup = new QGroupBox(tr("Documents"));
    documentsGroup->setLayout(documentsLayout);

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(title);
    m_layout->addWidget(stateGeometryGroup);
    m_layout->addWidget(documentsGroup);
    m_layout->addStretch();
}


QString PreferencesGeneralSettings::title() const
{
    return tr("General");
}


void PreferencesGeneralSettings::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


void PreferencesGeneralSettings::onSettingsChanged()
{
    emit settingsChanged();
}


void PreferencesGeneralSettings::setRestoreApplicationState(const bool checked)
{
    m_chkRestoreApplicationState->setChecked(checked);
}


bool PreferencesGeneralSettings::restoreApplicationState() const
{
    return m_chkRestoreApplicationState->isChecked();
}


void PreferencesGeneralSettings::setRestoreApplicationGeometry(const bool checked)
{
    m_chkRestoreApplicationGeometry->setChecked(checked);
}


bool PreferencesGeneralSettings::restoreApplicationGeometry() const
{
    return m_chkRestoreApplicationGeometry->isChecked();
}


void PreferencesGeneralSettings::setRestoreDialogGeometry(const bool checked)
{
    m_chkRestoreDialogGeometry->setChecked(checked);
}


bool PreferencesGeneralSettings::restoreDialogGeometry() const
{
    return m_chkRestoreDialogGeometry->isChecked();
}


void PreferencesGeneralSettings::setMaximumRecentDocuments(const int number)
{
    m_spbMaximumRecentDocuments->setValue(number);
}


int PreferencesGeneralSettings::maximumRecentDocuments() const
{
    return m_spbMaximumRecentDocuments->value();
}
