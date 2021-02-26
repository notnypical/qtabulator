/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of Tabulator-Qt, <https://github.com/notnypical/tabulator-qt>.
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

#include "colophon_about_page.h"

#include <QApplication>
#include <QTextBrowser>


ColophonAboutPage::ColophonAboutPage(QWidget *parent)
    : QWidget(parent)
{
    auto *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(tr("<html><body>"
        "<p>%1 is an open source editor tool written in Qt for C++ and designed for easy creation and editing of documents with character-separated values.</p>"
        "<p>Copyright &copy; 2020-2021 <a href=\"%2\" title=\"Visit organization's homepage\">%3</a>.</p>"
        "<p>This application is licensed under the terms of the <a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\" title=\"Visit license's homepage\">GNU General Public License, version 3</a>.</p>"
        "</body></html>").arg(QApplication::applicationName(), QApplication::organizationDomain(), QApplication::organizationName()));

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(textBox);
}


void ColophonAboutPage::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


QString ColophonAboutPage::title() const
{
    return tr("About");
}
