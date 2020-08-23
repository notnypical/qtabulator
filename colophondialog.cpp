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

    // Title box
    QLabel *name = new QLabel(QStringLiteral("<strong style=\"font-size:large;\">%1</strong> v%2").arg(QApplication::applicationName(), QApplication::applicationVersion()));
    QLabel *description = new QLabel(QStringLiteral("A CSV editor written in Qt for C++."));

    QWidget *widgetTmp = new QWidget;
    QVBoxLayout *vboxlayoutTmp = new QVBoxLayout(widgetTmp);
    const int vboxlayoutHeight = name->sizeHint().height() + vboxlayoutTmp->layout()->spacing() + description->sizeHint().height();

    QSvgWidget *logo = new QSvgWidget;
    logo->load(QStringLiteral(":/icons/apps/22/tabulator.svg"));
    logo->setFixedSize(vboxlayoutHeight, vboxlayoutHeight);

    QVBoxLayout *labels = new QVBoxLayout;
    labels->addWidget(name);
    labels->addWidget(description);

    QHBoxLayout *titleBox = new QHBoxLayout;
    titleBox->addWidget(logo);
    titleBox->addLayout(labels);

    // Tab box
    QTabWidget *tabBox = new QTabWidget;
    tabBox->addTab(createTabAbout(), QStringLiteral("About"));
    tabBox->addTab(createTabEnvironment(), QStringLiteral("Environment"));
    tabBox->addTab(createTabLicense(), QStringLiteral("License"));
    tabBox->addTab(createTabAuthors(), QStringLiteral("Authors"));

    // Button box
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ColophonDialog::onButtonCloseClicked);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(titleBox);
    layout->addWidget(tabBox);
    layout->addWidget(buttonBox);

    setLayout(layout);
}


/**
 * Creates the About tab.
 */
QTextBrowser *ColophonDialog::createTabAbout()
{
    QTextBrowser *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(QStringLiteral("<html><body>"
        "<p>%1 is an open source tool written in Qt for C++ and intended for easy creation and editing of documents with character-separated values.</p>"
        "<p>Copyright &copy; 2020 <a href=\"%2\">%3</a>.</p>"
        "<p>This application is licensed under the terms of the <a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\">GNU General Public License, version 3</a>.</p>"
        "</body></html>").arg(QApplication::applicationName(), QApplication::organizationDomain(), QApplication::organizationName()));

    return textBox;
}


/**
 * Creates the Environment tab.
 */
QTextBrowser *ColophonDialog::createTabEnvironment()
{
    QTextBrowser *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(QStringLiteral("<html><body><dl>"
        "<dt><strong>Application version</strong></dt>"
            "<dd>%1</dd>"
        "<dt><strong>Qt for C++ version</strong></dt>"
            "<dd>Qt %2 (Built against %3)</dd>"
        "<dt><strong>Operation System</strong></dt>"
            "<dd>%4 (Kernel %5 on %6)</dd>"
        "</dl></body></html>").arg(QApplication::applicationVersion(), qVersion(), QT_VERSION_STR, QSysInfo::prettyProductName(), QSysInfo::kernelVersion(), QSysInfo::currentCpuArchitecture()));

    return textBox;
}


/**
 * Creates the License tab.
 */
QTextBrowser *ColophonDialog::createTabLicense()
{
    QTextBrowser *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(QStringLiteral("<html><body>"
        "<p>%1 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p>"
        "<p>%1 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.</p>"
        "<p>You should have received a copy of the GNU General Public License along with %1. If not, see <a href=\"https://www.gnu.org/licenses/\">https://www.gnu.org/licenses/</a>.</p>"
        "</body></html>").arg(QApplication::applicationName()));

    return textBox;
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
