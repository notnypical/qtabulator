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

#include "colophon_credits_widget.h"

#include <QTextBrowser>
#include <QVBoxLayout>


ColophonCreditsWidget::ColophonCreditsWidget(QWidget *parent) :
    QWidget(parent)
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

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textBox, 1);

    setLayout(layout);
}


/**
 * Returns title of the widget.
 */
QString ColophonCreditsWidget::title() const
{
    return QStringLiteral("Credits");
}
