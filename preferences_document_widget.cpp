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

#include "preferences_document_widget.h"

#include <QLabel>
#include <QVBoxLayout>


PreferencesDocumentWidget::PreferencesDocumentWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *label = new QLabel(QStringLiteral("<strong style=\"font-size:large;\">Document</strong>"));

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addStretch();

    setLayout(layout);
}


/**
 * Emits signal that a setting has been changed.
 */
void PreferencesDocumentWidget::onSettingChanged()
{
    emit settingChanged();
}


/**
 * Returns title of the widget.
 */
QString PreferencesDocumentWidget::title() const
{
    return QStringLiteral("Document");
}
