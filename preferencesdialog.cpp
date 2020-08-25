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
#include <QIcon>
#include <QPushButton>
#include <QScreen>
#include <QSettings>
#include <QVBoxLayout>


PreferencesDialog::PreferencesDialog()
{
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

    // Button box
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onButtonOkClicked);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QAbstractButton::clicked, this, &PreferencesDialog::onButtonApplyClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreferencesDialog::onButtonCancelClicked);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addStretch(1);
    layout->addWidget(buttonBox);

    setLayout(layout);
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
    QPushButton *buttonCancel = buttonBox->button(QDialogButtonBox::Apply);
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

    // Update UI: Button
    QPushButton *buttonCancel = buttonBox->button(QDialogButtonBox::Apply);
    buttonCancel->setEnabled(false);
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
 * Fires the Close event to terminate the dialog with saving user preferences.
 */
void PreferencesDialog::onButtonOkClicked()
{
    close();
}


/**
 * Saves user preferences.
 */
void PreferencesDialog::onButtonApplyClicked()
{
    writeSettings();
}


/**
 * Fires the Close event to terminate the dialog without saving user preferences.
 */
void PreferencesDialog::onButtonCancelClicked()
{
    close();
}
