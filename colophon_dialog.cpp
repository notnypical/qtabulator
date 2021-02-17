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

#include "colophon_dialog.h"

#include <QDialogButtonBox>
#include <QTabWidget>
#include <QVBoxLayout>

#include "colophon_about_page.h"
#include "colophon_authors_page.h"
#include "colophon_credits_page.h"
#include "colophon_environment_page.h"
#include "colophon_license_page.h"
#include "dialog_title_box.h"


ColophonDialog::ColophonDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Colophon"));

    // Title box
    auto *titleBox = new DialogTitleBox;

    // Content
    auto *aboutPage = new ColophonAboutPage;
    auto *environmentPage = new ColophonEnvironmentPage;
    auto *licensePage = new ColophonLicensePage;
    auto *authorsPage = new ColophonAuthorsPage;
    auto *creditsPage = new ColophonCreditsPage;

    auto *tabBox = new QTabWidget;
    tabBox->addTab(aboutPage, aboutPage->title());
    tabBox->addTab(environmentPage, environmentPage->title());
    tabBox->addTab(licensePage, licensePage->title());
    tabBox->addTab(authorsPage, authorsPage->title());
    tabBox->addTab(creditsPage, creditsPage->title());

    // Button box
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ColophonDialog::close);

    // Main layout
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(titleBox);
    layout->addWidget(tabBox);
    layout->addWidget(buttonBox);
}


void ColophonDialog::setDialogGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty())
        restoreGeometry(geometry);
    else
        resize(640, 480);
}


QByteArray ColophonDialog::dialogGeometry() const
{
    return saveGeometry();
}
