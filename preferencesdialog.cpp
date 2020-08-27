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

#include "preferencesdialog.h"

#include <QAbstractButton>
#include <QApplication>
#include <QDialogButtonBox>
#include <QIcon>
#include <QLabel>
#include <QListWidget>
#include <QScreen>
#include <QSettings>
#include <QStackedWidget>
#include <QVBoxLayout>


PreferencesDialog::PreferencesDialog()
{
    saveSettings = false;

    setupUI();

    readSettings();
}


/**
 * Sets up the user interface.
 */
void PreferencesDialog::setupUI()
{
    setWindowTitle(QStringLiteral("Preferences | %1").arg(QApplication::applicationName()));
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/22/tabulator.svg")));

    // Settings box
    stackApplication = new QWidget;

    stackApplicationPage();

    QStackedWidget *stackedBox = new QStackedWidget;
    stackedBox->addWidget(stackApplication);
    stackedBox->setCurrentIndex(0);

    QListWidget *listBox = new QListWidget;
    listBox->addItem(QStringLiteral("Application"));
    listBox->setCurrentRow(stackedBox->currentIndex());
    connect(listBox, &QListWidget::currentRowChanged, stackedBox, &QStackedWidget::setCurrentIndex);

    QHBoxLayout *settingsBox = new QHBoxLayout;
    settingsBox->addWidget(listBox, 1);
    settingsBox->addWidget(stackedBox, 3);

    // Button box
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
    buttonCancel = buttonBox->button(QDialogButtonBox::Apply);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QAbstractButton::clicked, this, &PreferencesDialog::onButtonDefaultsClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onButtonOkClicked);
    connect(buttonCancel, &QAbstractButton::clicked, this, &PreferencesDialog::onButtonApplyClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreferencesDialog::onButtonCancelClicked);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(settingsBox);
    layout->addWidget(buttonBox);

    setLayout(layout);
}


/**
 * Displays the application settings page.
 */
void PreferencesDialog::stackApplicationPage()
{
    QLabel *label = new QLabel(QStringLiteral("<strong style=\"font-size:large;\">Application</strong>"));

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addStretch();

    stackApplication->setLayout(layout);
}


/**
 * Restores user preferences and other dialog properties.
 */
void PreferencesDialog::readSettings()
{
    QSettings settings;

    // Set dialog properties
    const QByteArray geometry = settings.value(QStringLiteral("PreferencesDialog/geometry"), QByteArray()).toByteArray();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    // Update UI: Button
    buttonCancel->setEnabled(false);
}


/**
 * Saves user preferences and other dialog properties.
 */
void PreferencesDialog::writeSettings()
{
    QSettings settings;

    // Store dialog properties
    settings.setValue(QStringLiteral("PreferencesDialog/geometry"), saveGeometry());

    if (saveSettings) {

        // Update UI: Button
        buttonCancel->setEnabled(false);

        saveSettings = false;
    }
}


/**
 * Processes the Close event.
 */
void PreferencesDialog::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}


/**
 * Restores default values of user preferences.
 */
void PreferencesDialog::onButtonDefaultsClicked()
{

}


/**
 * Fires the Close event to terminate the dialog with saving user preferences.
 */
void PreferencesDialog::onButtonOkClicked()
{
    saveSettings = true;
    close();
}


/**
 * Saves user preferences.
 */
void PreferencesDialog::onButtonApplyClicked()
{
    saveSettings = true;
    writeSettings();
}


/**
 * Fires the Close event to terminate the dialog without saving user preferences.
 */
void PreferencesDialog::onButtonCancelClicked()
{
    close();
}
