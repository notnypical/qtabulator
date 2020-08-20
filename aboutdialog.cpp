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

#include "aboutdialog.h"

#include <QApplication>
#include <QIcon>
#include <QSettings>
#include <QScreen>
#include <QVBoxLayout>


AboutDialog::AboutDialog()
{
    setupUI();

    readSettings();
}


/**
 * Sets up the user interface.
 */
void AboutDialog::setupUI()
{
    setWindowTitle(QStringLiteral("About %1").arg(QApplication::applicationName()));
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/22/tabulator.svg")));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Button box
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AboutDialog::onButtonCloseClicked);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addStretch(1);
    layout->addWidget(buttonBox);

    setLayout(layout);
}


/**
 * Restores user preferences and other dialog properties.
 */
void AboutDialog::readSettings()
{
    QSettings settings;

    // Set dialog properties
    const QByteArray geometry = settings.value(QStringLiteral("AboutDialog/geometry"), QByteArray()).toByteArray();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}


/**
 * Saves user preferences and other dialog properties.
 */
void AboutDialog::writeSettings()
{
    QSettings settings;

    // Store dialog properties
    settings.setValue(QStringLiteral("AboutDialog/geometry"), saveGeometry());
}


/**
 * Processes the Close event.
 */
void AboutDialog::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}


/**
 * Fires the Close event to terminate the dialog.
 */
void AboutDialog::onButtonCloseClicked()
{
    close();
}
