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

#include "environment_page.h"

#include <QApplication>
#include <QTextBrowser>
#include <QVBoxLayout>


EnvironmentPage::EnvironmentPage(QWidget *parent) :
    QWidget(parent)
{
    const QString qtVersion = qVersion(); // Qt version used to run Qt for C++
    const QString qtBuildVersion = QT_VERSION_STR; // Qt version used to compile Qt
    const QString osName = QSysInfo::prettyProductName();
    const QString osKernelVersion = QSysInfo::kernelVersion();
    const QString osCpuArchitecture = QSysInfo::currentCpuArchitecture();

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
        "</dl></body></html>").arg(QApplication::applicationVersion(), qtVersion, qtBuildVersion, osName, osKernelVersion, osCpuArchitecture));

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textBox);
    layout->addStretch(1);

    setLayout(layout);
}
