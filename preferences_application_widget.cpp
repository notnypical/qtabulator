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

#include "preferences_application_widget.h"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>


PreferencesApplicationWidget::PreferencesApplicationWidget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label = new QLabel(QStringLiteral("<strong style=\"font-size:large;\">Application</strong>"));

    // Geometries
    chkRestoreWindowGeometry = new QCheckBox(QStringLiteral("Save and restore window geometry"));
    connect(chkRestoreWindowGeometry, &QCheckBox::stateChanged, this, &PreferencesApplicationWidget::onSettingChanged);

    chkRestoreDialogGeometry = new QCheckBox(QStringLiteral("Save and restore dialog geometry"));
    connect(chkRestoreDialogGeometry, &QCheckBox::stateChanged, this, &PreferencesApplicationWidget::onSettingChanged);

    QVBoxLayout *geometryLayout = new QVBoxLayout;
    geometryLayout->addWidget(chkRestoreWindowGeometry);
    geometryLayout->addWidget(chkRestoreDialogGeometry);

    QGroupBox *geometryGroup = new QGroupBox(QStringLiteral("Geometries"));
    geometryGroup->setLayout(geometryLayout);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(geometryGroup);
    layout->addStretch();

    setLayout(layout);
}


/**
 * Emits signal that a setting has been changed.
 */
void PreferencesApplicationWidget::onSettingChanged()
{
    emit settingChanged();
}


/**
 * Returns title of the widget.
 */
QString PreferencesApplicationWidget::title() const
{
    return QStringLiteral("Application");
}


/**
 * Returns setting whether the main window geometry should be restored.
 */
bool PreferencesApplicationWidget::restoreWindowGeometry() const
{
    return chkRestoreWindowGeometry->isChecked();
}


/**
 * Sets setting whether the main window geometry should be restored.
 */
void PreferencesApplicationWidget::setRestoreWindowGeometry(const bool checked)
{
    chkRestoreWindowGeometry->setChecked(checked);
}


/**
 * Returns setting whether the dialog geometry should be restored.
 */
bool PreferencesApplicationWidget::restoreDialogGeometry() const
{
    return chkRestoreDialogGeometry->isChecked();
}


/**
 * Sets setting whether the dialog geometry should be restored.
 */
void PreferencesApplicationWidget::setRestoreDialogGeometry(const bool checked)
{
    chkRestoreDialogGeometry->setChecked(checked);
}
