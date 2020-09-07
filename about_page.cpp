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

#include <QApplication>
#include <QTextBrowser>
#include <QVBoxLayout>


AboutPage::AboutPage(QWidget *parent) :
    QWidget(parent)
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

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textBox, 1);

    setLayout(layout);
}
