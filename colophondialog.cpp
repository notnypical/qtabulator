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

#include "colophondialog.h"

#include <QApplication>
#include <QIcon>
#include <QScreen>
#include <QSettings>


ColophonDialog::ColophonDialog()
{
    setWindowTitle(QStringLiteral("Colophon | %1").arg(QApplication::applicationName()));
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/22/tabulator.svg")));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    readSettings();
}


/**
 * Restores user preferences and other dialog properties.
 */
void ColophonDialog::readSettings()
{
    QSettings settings;

    // Set dialog properties
    const QByteArray geometry = settings.value(QStringLiteral("ColophonDialog/geometry"), QByteArray()).toByteArray();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}
