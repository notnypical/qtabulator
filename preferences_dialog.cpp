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

#include "preferences_dialog.h"

#include <QDialogButtonBox>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>


PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Preferences"));

    // Preferences box
    m_generalPage = new PreferencesGeneralPage(this);
    m_generalPage->setZeroMargins();
    connect(m_generalPage, &PreferencesGeneralPage::preferencesChanged, this, &PreferencesDialog::onPreferencesChanged);

    m_documentsPage = new PreferencesDocumentsPage(this);
    m_documentsPage->setZeroMargins();
    connect(m_documentsPage, &PreferencesDocumentsPage::preferencesChanged, this, &PreferencesDialog::onPreferencesChanged);

    m_documentPresetsPage = new PreferencesDocumentPresetsPage(this);
    m_documentPresetsPage->setZeroMargins();
    connect(m_documentPresetsPage, &PreferencesDocumentPresetsPage::preferencesChanged, this, &PreferencesDialog::onPreferencesChanged);

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

    auto *preferencesBox = new QHBoxLayout;
    preferencesBox->addWidget(listBox, 1);
    preferencesBox->addWidget(stackedBox, 3);

    // Button box
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
    m_buttonApply = buttonBox->button(QDialogButtonBox::Apply);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QAbstractButton::clicked, this, &PreferencesDialog::onButtonDefaultsClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onButtonOkClicked);
    connect(m_buttonApply, &QAbstractButton::clicked, this, &PreferencesDialog::onButtonApplyClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreferencesDialog::close);

    // Main layout
    auto *layout = new QVBoxLayout(this);
    layout->addLayout(preferencesBox);
    layout->addWidget(buttonBox);

    updatePreferences();
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


void PreferencesDialog::setPreferences(const Preferences &preferences)
{
    m_preferences = preferences;

    updatePreferences();
    m_buttonApply->setEnabled(false);
}


Preferences PreferencesDialog::preferences() const
{
    return m_preferences;
}


void PreferencesDialog::onPreferencesChanged()
{
    m_buttonApply->setEnabled(true);
}


void PreferencesDialog::onButtonDefaultsClicked()
{
    updatePreferences(true);
}


void PreferencesDialog::onButtonOkClicked()
{
    savePreferences();
    close();
}


void PreferencesDialog::onButtonApplyClicked()
{
    savePreferences();
    m_buttonApply->setEnabled(false);
}


void PreferencesDialog::updatePreferences(bool isDefault)
{
    // General: State & Geometries
    m_generalPage->setRestoreApplicationState(m_preferences.restoreApplicationState(isDefault));
    m_generalPage->setRestoreApplicationGeometry(m_preferences.restoreApplicationGeometry(isDefault));
    m_generalPage->setRestoreDialogGeometry(m_preferences.restoreDialogGeometry(isDefault));

    // Documents: Recently Opened Documents
    m_documentsPage->setMaximumRecentDocuments(m_preferences.maximumRecentDocuments(isDefault));

    // Document Presets: Header Labels
    m_documentPresetsPage->setDefaultHeaderLabelHorizontal(m_preferences.defaultHeaderLabelHorizontal(isDefault));
    m_documentPresetsPage->setDefaultHeaderLabelVertical(m_preferences.defaultHeaderLabelVertical(isDefault));

    // Document Presets: Cell Counts
    m_documentPresetsPage->setDefaultCellCountColumn(m_preferences.defaultCellCountColumn(isDefault));
    m_documentPresetsPage->setDefaultCellCountRow(m_preferences.defaultCellCountRow(isDefault));
}


void PreferencesDialog::savePreferences()
{
    // General: State & Geometries
    m_preferences.setRestoreApplicationState(m_generalPage->restoreApplicationState());
    m_preferences.setRestoreApplicationGeometry(m_generalPage->restoreApplicationGeometry());
    m_preferences.setRestoreDialogGeometry(m_generalPage->restoreDialogGeometry());

    // Documents: Recently Opened Documents
    m_preferences.setMaximumRecentDocuments(m_documentsPage->maximumRecentDocuments());

    // Document Presets: Header Labels
    m_preferences.setDefaultHeaderLabelHorizontal(m_documentPresetsPage->defaultHeaderLabelHorizontal());
    m_preferences.setDefaultHeaderLabelVertical(m_documentPresetsPage->defaultHeaderLabelVertical());

    // Document Presets: Cell Counts
    m_preferences.setDefaultCellCountColumn(m_documentPresetsPage->defaultCellCountColumn());
    m_preferences.setDefaultCellCountRow(m_documentPresetsPage->defaultCellCountRow());
}
