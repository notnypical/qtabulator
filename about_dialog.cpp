/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
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

#include "about_dialog.h"

#include <QApplication>
#include <QDialogButtonBox>
#include <QVBoxLayout>

#include "colophon_about_page.h"
#include "dialog_title_box.h"


AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("About %1").arg(QApplication::applicationName()));

    setDialogGeometry();

    // Title box
    auto *titleBox = new DialogTitleBox;

    // Content
    auto *aboutPage = new ColophonAboutPage;
    aboutPage->setZeroMargins();

    // Button box
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AboutDialog::close);

    // Main layout
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(titleBox);
    layout->addWidget(aboutPage);
    layout->addWidget(buttonBox);
}


void AboutDialog::setDialogGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty())
        restoreGeometry(geometry);
    else
        resize(480, 320);
}


QByteArray AboutDialog::dialogGeometry() const
{
    return saveGeometry();
}
