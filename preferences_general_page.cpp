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

#include "preferences_general_page.h"

#include <QGroupBox>
#include <QLabel>


PreferencesGeneralPage::PreferencesGeneralPage(QWidget *parent)
    : QWidget(parent)
{
    // Title
    auto *title = new QLabel(tr("<strong style=\"font-size:large;\">General</strong>"));

    // State & Geometries
    m_chkRestoreApplicationState = new QCheckBox(tr("Save and restore the application state"));
    connect(m_chkRestoreApplicationState, &QCheckBox::stateChanged, this, &PreferencesGeneralPage::onPreferencesChanged);

    m_chkRestoreApplicationGeometry = new QCheckBox(tr("Save and restore the application geometry"));
    connect(m_chkRestoreApplicationGeometry, &QCheckBox::stateChanged, this, &PreferencesGeneralPage::onPreferencesChanged);

    m_chkRestoreDialogGeometry = new QCheckBox(tr("Save and restore dialog geometries"));
    connect(m_chkRestoreDialogGeometry, &QCheckBox::stateChanged, this, &PreferencesGeneralPage::onPreferencesChanged);

    auto *stateGeometriesLayout = new QVBoxLayout;
    stateGeometriesLayout->addWidget(m_chkRestoreApplicationState);
    stateGeometriesLayout->addWidget(m_chkRestoreApplicationGeometry);
    stateGeometriesLayout->addWidget(m_chkRestoreDialogGeometry);

    auto *stateGeometriesGroup = new QGroupBox(tr("State && Geometries"));
    stateGeometriesGroup->setLayout(stateGeometriesLayout);

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(title);
    m_layout->addWidget(stateGeometriesGroup);
    m_layout->addStretch();
}


void PreferencesGeneralPage::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


QString PreferencesGeneralPage::title() const
{
    return tr("General");
}


void PreferencesGeneralPage::onPreferencesChanged()
{
    emit preferencesChanged();
}


void PreferencesGeneralPage::setRestoreApplicationState(const bool checked)
{
    m_chkRestoreApplicationState->setChecked(checked);
}


bool PreferencesGeneralPage::restoreApplicationState() const
{
    return m_chkRestoreApplicationState->isChecked();
}


void PreferencesGeneralPage::setRestoreApplicationGeometry(const bool checked)
{
    m_chkRestoreApplicationGeometry->setChecked(checked);
}


bool PreferencesGeneralPage::restoreApplicationGeometry() const
{
    return m_chkRestoreApplicationGeometry->isChecked();
}


void PreferencesGeneralPage::setRestoreDialogGeometry(const bool checked)
{
    m_chkRestoreDialogGeometry->setChecked(checked);
}


bool PreferencesGeneralPage::restoreDialogGeometry() const
{
    return m_chkRestoreDialogGeometry->isChecked();
}
