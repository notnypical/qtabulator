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
    applicationSettings = new ApplicationSettings(this);
    updateSettings(m_settings);

    QStackedWidget *stackedBox = new QStackedWidget;
    stackedBox->addWidget(applicationSettings);
    stackedBox->setCurrentIndex(0);

    QListWidget *listBox = new QListWidget;
    listBox->addItem(applicationSettings->title());
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
    applicationSettings->setRestoreWindowGeometry(settings.restoreWindowGeometry);
    applicationSettings->setRestoreDialogGeometry(settings.restoreDialogGeometry);
}


/**
 * Reads the user preferences and saves them.
 */
void PreferencesDialog::saveSettings()
{
    // Application: Appearance
    m_settings.restoreWindowGeometry = applicationSettings->restoreWindowGeometry();
    m_settings.restoreDialogGeometry = applicationSettings->restoreDialogGeometry();

    buttonApply->setEnabled(false);
}


/**
 * Enables the apply button if the settings have been changed.
 */
void PreferencesDialog::onSettingsChanged()
{
    buttonApply->setEnabled(true);
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
