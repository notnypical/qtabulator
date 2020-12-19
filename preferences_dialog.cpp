/**
 * Copyright 2020 NotNypical, <https://notnypical.github.io>.
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

#include "preferences_dialog.h"

#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QScreen>
#include <QStackedWidget>
#include <QVBoxLayout>


PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent)
{
    // Settings box
    m_generalSettings = new PreferencesGeneralSettings(this);
    connect(m_generalSettings, &PreferencesGeneralSettings::settingsChanged, this, &PreferencesDialog::onSettingChanged);

    documentSettings = new PreferencesDocumentWidget(this);
    connect(documentSettings, &PreferencesDocumentWidget::settingChanged, this, &PreferencesDialog::onSettingChanged);

    QStackedWidget *stackedBox = new QStackedWidget;
    stackedBox->addWidget(m_generalSettings);
    stackedBox->addWidget(documentSettings);
    stackedBox->setCurrentIndex(0);

    QListWidget *listBox = new QListWidget;
    listBox->addItem(m_generalSettings->title());
    listBox->addItem(documentSettings->title());
    listBox->setCurrentRow(stackedBox->currentIndex());
    connect(listBox, &QListWidget::currentRowChanged, stackedBox, &QStackedWidget::setCurrentIndex);

    QHBoxLayout *settingsBox = new QHBoxLayout;
    settingsBox->addWidget(listBox, 1);
    settingsBox->addWidget(stackedBox, 3);

    // Button box
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
    buttonApply = buttonBox->button(QDialogButtonBox::Apply);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QAbstractButton::clicked, this, &PreferencesDialog::onButtonDefaultsClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onButtonOkClicked);
    connect(buttonApply, &QAbstractButton::clicked, this, &PreferencesDialog::onButtonApplyClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreferencesDialog::close);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(settingsBox, 1);
    layout->addWidget(buttonBox);

    setLayout(layout);

    updateSettings(m_settings);
}


/**
 * Enables the apply button if a setting has been changed.
 */
void PreferencesDialog::onSettingChanged()
{
    buttonApply->setEnabled(true);
}


/**
 * Returns the geometry of the widget.
 */
QByteArray PreferencesDialog::windowGeometry() const
{
    return saveGeometry();
}


/**
 * Sets the geometry of the widget.
 */
void PreferencesDialog::setWindowGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}


/**
 * Returns the user preferences.
 */
Settings PreferencesDialog::settings() const
{
    return m_settings;
}


/**
 * Sets the user preferences.
 */
void PreferencesDialog::setSettings(const Settings &settings)
{
    updateSettings(settings);
    saveSettings();
}


/**
 * Updates the settings.
 */
void PreferencesDialog::updateSettings(const Settings &settings)
{
    // Application: Appearance
    m_generalSettings->setRestoreApplicationGeometry(settings.restoreWindowGeometry);
    m_generalSettings->setRestoreDialogGeometry(settings.restoreDialogGeometry);
    m_generalSettings->setMaximumRecentDocuments(settings.maximumRecentDocuments);

    // Document: Defaults
    documentSettings->setDefaultHeaderLabelHorizontal(settings.defaultHeaderLabelHorizontal);
    documentSettings->setDefaultHeaderLabelVertical(settings.defaultHeaderLabelVertical);
    documentSettings->setDefaultCellColumns(settings.defaultCellColumns);
    documentSettings->setDefaultCellRows(settings.defaultCellRows);
}


/**
 * Reads the user preferences and saves them.
 */
void PreferencesDialog::saveSettings()
{
    // Application: Appearance
    m_settings.restoreWindowGeometry = m_generalSettings->restoreApplicationGeometry();
    m_settings.restoreDialogGeometry = m_generalSettings->restoreDialogGeometry();
    m_settings.maximumRecentDocuments = m_generalSettings->maximumRecentDocuments();

    // Document: Defaults
    m_settings.defaultHeaderLabelHorizontal = documentSettings->defaultHeaderLabelHorizontal();
    m_settings.defaultHeaderLabelVertical = documentSettings->defaultHeaderLabelVertical();
    m_settings.defaultCellColumns = documentSettings->defaultCellColumns();
    m_settings.defaultCellRows = documentSettings->defaultCellRows();

    buttonApply->setEnabled(false);
}


/**
 * Restores default values of user preferences.
 */
void PreferencesDialog::onButtonDefaultsClicked()
{
    Settings settings;
    updateSettings(settings);
}


/**
 * Closes the dialog with saving user preferences.
 */
void PreferencesDialog::onButtonOkClicked()
{
    saveSettings();
    close();
}


/**
 * Saves user preferences.
 */
void PreferencesDialog::onButtonApplyClicked()
{
    saveSettings();
}
