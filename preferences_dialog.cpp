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

#include "preferences_dialog.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>


PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Preferences"));

    setDialogGeometry();

    // Settings box
    m_generalPage = new PreferencesGeneralPage(this);
    m_generalPage->setZeroMargins();
    connect(m_generalPage, &PreferencesGeneralPage::settingsChanged, this, &PreferencesDialog::onSettingsChanged);

    m_documentsPage = new PreferencesDocumentsPage(this);
    m_documentsPage->setZeroMargins();
    connect(m_documentsPage, &PreferencesDocumentsPage::settingsChanged, this, &PreferencesDialog::onSettingsChanged);

    m_documentPresetsPage = new PreferencesDocumentPresetsPage(this);
    m_documentPresetsPage->setZeroMargins();
    connect(m_documentPresetsPage, &PreferencesDocumentPresetsPage::settingsChanged, this, &PreferencesDialog::onSettingsChanged);

    auto *stackedBox = new QStackedWidget;
    stackedBox->addWidget(m_generalPage);
    stackedBox->addWidget(m_documentsPage);
    stackedBox->addWidget(m_documentPresetsPage);
    stackedBox->setCurrentIndex(0);

    auto *listBox = new QListWidget;
    listBox->addItem(m_generalPage->title());
    listBox->addItem(m_documentsPage->title());
    listBox->addItem(m_documentPresetsPage->title());
    listBox->setCurrentRow(stackedBox->currentIndex());
    connect(listBox, &QListWidget::currentRowChanged, stackedBox, &QStackedWidget::setCurrentIndex);

    auto *settingsBox = new QHBoxLayout;
    settingsBox->addWidget(listBox, 1);
    settingsBox->addWidget(stackedBox, 3);

    // Button box
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
    m_buttonApply = buttonBox->button(QDialogButtonBox::Apply);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QAbstractButton::clicked, this, &PreferencesDialog::onButtonDefaultsClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onButtonOkClicked);
    connect(m_buttonApply, &QAbstractButton::clicked, this, &PreferencesDialog::onButtonApplyClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreferencesDialog::close);

    // Main layout
    auto *layout = new QVBoxLayout(this);
    layout->addLayout(settingsBox);
    layout->addWidget(buttonBox);

    updateSettings();
    m_buttonApply->setEnabled(false);
}


void PreferencesDialog::setDialogGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty())
        restoreGeometry(geometry);
    else
        resize(800, 600);
}


QByteArray PreferencesDialog::dialogGeometry() const
{
    return saveGeometry();
}


void PreferencesDialog::setSettings(const Settings &settings)
{
    m_settings = settings;

    updateSettings();
    m_buttonApply->setEnabled(false);
}


Settings PreferencesDialog::settings() const
{
    return m_settings;
}


void PreferencesDialog::onSettingsChanged()
{
    m_buttonApply->setEnabled(true);
}


void PreferencesDialog::onButtonDefaultsClicked()
{
    updateSettings(true);
}


void PreferencesDialog::onButtonOkClicked()
{
    saveSettings();
    close();
}


void PreferencesDialog::onButtonApplyClicked()
{
    saveSettings();
    m_buttonApply->setEnabled(false);
}


void PreferencesDialog::updateSettings(bool isDefault)
{
    // General: State & Geometries
    m_generalPage->setRestoreApplicationState(m_settings.restoreApplicationState(isDefault));
    m_generalPage->setRestoreApplicationGeometry(m_settings.restoreApplicationGeometry(isDefault));
    m_generalPage->setRestoreDialogGeometry(m_settings.restoreDialogGeometry(isDefault));

    // Documents: Recently Opened Documents
    m_documentsPage->setMaximumRecentDocuments(m_settings.maximumRecentDocuments(isDefault));

    // Document Presets: Header Labels
    m_documentPresetsPage->setDefaultHeaderLabelHorizontal(m_settings.defaultHeaderLabelHorizontal(isDefault));
    m_documentPresetsPage->setDefaultHeaderLabelVertical(m_settings.defaultHeaderLabelVertical(isDefault));

    // Document Presets: Cell Counts
    m_documentPresetsPage->setDefaultCellCountColumn(m_settings.defaultCellCountColumn(isDefault));
    m_documentPresetsPage->setDefaultCellCountRow(m_settings.defaultCellCountRow(isDefault));
}


void PreferencesDialog::saveSettings()
{
    // General: State & Geometries
    m_settings.setRestoreApplicationState(m_generalPage->restoreApplicationState());
    m_settings.setRestoreApplicationGeometry(m_generalPage->restoreApplicationGeometry());
    m_settings.setRestoreDialogGeometry(m_generalPage->restoreDialogGeometry());

    // Documents: Recently Opened Documents
    m_settings.setMaximumRecentDocuments(m_documentsPage->maximumRecentDocuments());

    // Document Presets: Header Labels
    m_settings.setDefaultHeaderLabelHorizontal(m_documentPresetsPage->defaultHeaderLabelHorizontal());
    m_settings.setDefaultHeaderLabelVertical(m_documentPresetsPage->defaultHeaderLabelVertical());

    // Document Presets: Cell Counts
    m_settings.setDefaultCellCountColumn(m_documentPresetsPage->defaultCellCountColumn());
    m_settings.setDefaultCellCountRow(m_documentPresetsPage->defaultCellCountRow());
}
