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

#include "preferences_documents_settings.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

#include "settings.h"


PreferencesDocumentsSettings::PreferencesDocumentsSettings(QWidget *parent)
    : QWidget(parent)
{
    // Title
    auto *title = new QLabel(tr("<strong style=\"font-size:large;\">Documents Settings</strong>"));

    // Documents
    m_spbMaximumRecentDocuments = new QSpinBox;
    m_spbMaximumRecentDocuments->setRange(MAXIMUM_RECENT_DOCUMENTS_MINIMUM, MAXIMUM_RECENT_DOCUMENTS_MAXIMUM);
    m_spbMaximumRecentDocuments->setToolTip(tr("Maximum number of recently opened documents"));
    connect(m_spbMaximumRecentDocuments, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentsSettings::onSettingsChanged);

    auto *documentsLayout = new QFormLayout;
    documentsLayout->addRow(tr("Number of documents"), m_spbMaximumRecentDocuments);

    auto *documentsGroup = new QGroupBox(tr("Recently Opened Documents"));
    documentsGroup->setLayout(documentsLayout);

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(title);
    m_layout->addWidget(documentsGroup);
    m_layout->addStretch();
}


QString PreferencesDocumentsSettings::title() const
{
    return tr("Documents");
}


void PreferencesDocumentsSettings::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


void PreferencesDocumentsSettings::onSettingsChanged()
{
    emit settingsChanged();
}


void PreferencesDocumentsSettings::setMaximumRecentDocuments(const int val)
{
    m_spbMaximumRecentDocuments->setValue(val);
}


int PreferencesDocumentsSettings::maximumRecentDocuments() const
{
    return m_spbMaximumRecentDocuments->value();
}
