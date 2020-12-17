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

#include "colophon_authors_page.h"

#include <QTextBrowser>
#include <QVBoxLayout>


ColophonAuthorsWidget::ColophonAuthorsWidget(QWidget *parent) :
    QWidget(parent)
{
    QTextBrowser *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(QStringLiteral("<html><body><dl>"
        "<dt><strong>NotNypical</strong></dt>"
            "<dd>Created and developed by <a href=\"https://notnypical.github.io\" title=\"Visit author's homepage\">NotNypical</a>.</dd>"
        "</dl></body></html>"));

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textBox, 1);

    setLayout(layout);
}


/**
 * Returns title of the widget.
 */
QString ColophonAuthorsWidget::title() const
{
    return QStringLiteral("Authors");
}
