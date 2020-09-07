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

#include "about_page.h"
#include "colophon_dialog.h"
#include "dialog_title_box.h"
#include "environment_page.h"
#include "license_page.h"

#include <QApplication>
#include <QDialogButtonBox>
#include <QIcon>
#include <QLabel>
#include <QScreen>
#include <QSettings>
#include <QSvgWidget>
#include <QTabWidget>
#include <QVBoxLayout>


ColophonDialog::ColophonDialog()
{
    setupUI();

    readSettings();
}


/**
 * Sets up the user interface.
 */
void ColophonDialog::setupUI()
{
    setWindowTitle(QStringLiteral("Colophon | %1").arg(QApplication::applicationName()));
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/22/tabulator.svg")));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Tab box
    QTabWidget *tabBox = new QTabWidget;
    tabBox->addTab(new AboutPage, QStringLiteral("About"));
    tabBox->addTab(new EnvironmentPage, QStringLiteral("Environment"));
    tabBox->addTab(new LicensePage, QStringLiteral("License"));
    tabBox->addTab(createTabAuthors(), QStringLiteral("Authors"));
    tabBox->addTab(createTabCredits(), QStringLiteral("Credits"));

    // Button box
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ColophonDialog::onButtonCloseClicked);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new DialogTitleBox);
    layout->addWidget(tabBox, 1);
    layout->addWidget(buttonBox);

    setLayout(layout);
}


/**
 * Creates the Authors tab.
 */
QTextBrowser *ColophonDialog::createTabAuthors()
{
    QTextBrowser *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(QStringLiteral("<html><body><dl>"
        "<dt><strong>NotNypical</strong></dt>"
            "<dd>Created and developed by <a href=\"https://notnypical.github.io\" title=\"Visit author's homepage\">NotNypical</a>.</dd>"
        "</dl></body></html>"));

    return textBox;
}


/**
 * Creates the Credits tab.
 */
QTextBrowser *ColophonDialog::createTabCredits()
{
    QTextBrowser *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(QStringLiteral("<html><body><dl>"
        "<dt><strong>BreezeIcons project</strong></dt>"
            "<dd>Application logo and icons made by <a href=\"https://api.kde.org/frameworks/breeze-icons/html/\" title=\"Visit project's homepage\">BreezeIcons project</a> "
                "from <a href=\"https://kde.org\" title=\"Visit organization's homepage\">KDE</a> "
                "are licensed under <a href=\"https://www.gnu.org/licenses/lgpl-3.0.en.html\" title=\"GNU Lesser General Public License Version 3\">LGPLv3</a>.</dd>"
        "</dl></body></html>"));

    return textBox;
}


/**
 * Restores user preferences and other dialog properties.
 */
void ColophonDialog::readSettings()
{
    QSettings settings;

    // Read user preferences
    const bool geometryDialogRestore = settings.value(QStringLiteral("Settings/geometryDialogRestore"), true).toBool();

    // Set dialog properties
    const QByteArray geometry = settings.value(QStringLiteral("ColophonDialog/geometry"), QByteArray()).toByteArray();
    if (geometryDialogRestore && !geometry.isEmpty()) {
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
void ColophonDialog::writeSettings()
{
    QSettings settings;

    // Store dialog properties
    settings.setValue(QStringLiteral("ColophonDialog/geometry"), saveGeometry());
}


/**
 * Processes the Close event.
 */
void ColophonDialog::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}


/**
 * Fires the Close event to terminate the dialog.
 */
void ColophonDialog::onButtonCloseClicked()
{
    close();
}
