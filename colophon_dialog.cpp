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

#include "colophon_about_widget.h"
#include "authors_page.h"
#include "colophon_dialog.h"
#include "credits_page.h"
#include "dialog_title_box.h"
#include "environment_page.h"
#include "license_page.h"

#include <QDialogButtonBox>
#include <QScreen>
#include <QTabWidget>
#include <QVBoxLayout>


ColophonDialog::ColophonDialog(QWidget *parent) :
    QDialog(parent)
{
    // Tab box
    ColophonAboutWidget *about = new ColophonAboutWidget;

    QTabWidget *tabBox = new QTabWidget;
    tabBox->addTab(about, about->title());
    tabBox->addTab(new EnvironmentPage, QStringLiteral("Environment"));
    tabBox->addTab(new LicensePage, QStringLiteral("License"));
    tabBox->addTab(new AuthorsPage, QStringLiteral("Authors"));
    tabBox->addTab(new CreditsPage, QStringLiteral("Credits"));

    // Button box
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ColophonDialog::close);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new DialogTitleBox);
    layout->addWidget(tabBox, 1);
    layout->addWidget(buttonBox);

    setLayout(layout);
}


/**
 * Returns the geometry of the widget.
 */
QByteArray ColophonDialog::windowGeometry() const
{
    return saveGeometry();
}


/**
 * Sets the geometry of the widget.
 */
void ColophonDialog::setWindowGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}
