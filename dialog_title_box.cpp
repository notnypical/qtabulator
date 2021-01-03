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

#include "dialog_title_box.h"

#include <QApplication>
#include <QLabel>
#include <QSvgWidget>
#include <QVBoxLayout>


DialogTitleBox::DialogTitleBox(QWidget *parent)
    : QWidget(parent)
{
    auto *logo = new QSvgWidget;
    logo->load(QStringLiteral(":/icons/apps/22/tabulator.svg"));

    auto *name = new QLabel(tr("<strong style=\"font-size:large;\">%1</strong> v%2").arg(QApplication::applicationName(), QApplication::applicationVersion()));
    auto *description = new QLabel(tr("An editor tool for documents with character-separated values"));

    auto *labels = new QVBoxLayout;
    labels->addWidget(name);
    labels->addWidget(description);

    // Main layout
    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(logo);
    m_layout->addLayout(labels);

    // Set logo size
    const int height = name->sizeHint().height() + labels->layout()->spacing() + description->sizeHint().height();
    logo->setFixedSize(height, height);
}


void DialogTitleBox::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}
