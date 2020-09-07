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

#include "dialog_title_box.h"

#include <QApplication>
#include <QLabel>
#include <QSvgWidget>
#include <QVBoxLayout>


DialogTitleBox::DialogTitleBox(QWidget *parent) :
    QWidget(parent)
{
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

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(titleBox);
    layout->addStretch(1);

    setLayout(layout);
}
