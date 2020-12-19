/**
 * Copyright 2020 NotNypical, <https://notnypical.github.io>.
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

#include "preferences_document_settings.h"

#include <QAbstractButton>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QTabWidget>
#include <QVBoxLayout>


PreferencesDocumentSettings::PreferencesDocumentSettings(QWidget *parent) :
    QWidget(parent)
{
    // Title
    QLabel *title = new QLabel(QStringLiteral("<strong style=\"font-size:large;\">Document Settings</strong>"));

    // Tab box
    QTabWidget *tabBox = new QTabWidget;
    tabBox->addTab(tabDefaultSettings(), QStringLiteral("Default"));

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(title);
    m_layout->addWidget(tabBox);
}


QWidget *PreferencesDocumentSettings::tabDefaultSettings() {

    // Default: Headers
    QRadioButton *rdbDefaultHeaderLabelHorizontalLetters = new QRadioButton(QStringLiteral("Letters"));
    rdbDefaultHeaderLabelHorizontalLetters->setToolTip(QStringLiteral("Capital letters as default horizontal header labels"));

    QRadioButton *rdbDefaultHeaderLabelHorizontalNumbers = new QRadioButton(QStringLiteral("Numbers"));
    rdbDefaultHeaderLabelHorizontalNumbers->setToolTip(QStringLiteral("Decimal numbers as default horizontal header labels"));

    m_grpDefaultHeaderLabelHorizontal = new QButtonGroup(this);
    m_grpDefaultHeaderLabelHorizontal->addButton(rdbDefaultHeaderLabelHorizontalLetters, (int) Settings::HeaderLabel::Letter);
    m_grpDefaultHeaderLabelHorizontal->addButton(rdbDefaultHeaderLabelHorizontalNumbers, (int) Settings::HeaderLabel::Decimal);
    connect(m_grpDefaultHeaderLabelHorizontal, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentSettings::onSettingsChanged);

    QHBoxLayout *defaultHeaderLabelHorizontalBox = new QHBoxLayout;
    defaultHeaderLabelHorizontalBox->addWidget(rdbDefaultHeaderLabelHorizontalLetters);
    defaultHeaderLabelHorizontalBox->addWidget(rdbDefaultHeaderLabelHorizontalNumbers);

    QRadioButton *rdbDefaultHeaderLabelVerticalLetters = new QRadioButton(QStringLiteral("Letters"));
    rdbDefaultHeaderLabelVerticalLetters->setToolTip(QStringLiteral("Capital letters as default vertical header labels"));

    QRadioButton *rdbDefaultHeaderLabelVerticalNumbers = new QRadioButton(QStringLiteral("Numbers"));
    rdbDefaultHeaderLabelVerticalNumbers->setToolTip(QStringLiteral("Decimal numbers as default vertical header labels"));

    m_grpDefaultHeaderLabelVertical = new QButtonGroup(this);
    m_grpDefaultHeaderLabelVertical->addButton(rdbDefaultHeaderLabelVerticalLetters, (int) Settings::HeaderLabel::Letter);
    m_grpDefaultHeaderLabelVertical->addButton(rdbDefaultHeaderLabelVerticalNumbers, (int) Settings::HeaderLabel::Decimal);
    connect(m_grpDefaultHeaderLabelVertical, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentSettings::onSettingsChanged);

    QHBoxLayout *defaultHeaderLabelVerticalBox = new QHBoxLayout;
    defaultHeaderLabelVerticalBox->addWidget(rdbDefaultHeaderLabelVerticalLetters);
    defaultHeaderLabelVerticalBox->addWidget(rdbDefaultHeaderLabelVerticalNumbers);

    QFormLayout *defaultHeadersLayout = new QFormLayout;
    defaultHeadersLayout->addRow(QStringLiteral("Labels of horizontal header"), defaultHeaderLabelHorizontalBox);
    defaultHeadersLayout->addRow(QStringLiteral("Labels of vertical header"), defaultHeaderLabelVerticalBox);

    QGroupBox *defaultHeadersGroup = new QGroupBox(QStringLiteral("Headers"));
    defaultHeadersGroup->setLayout(defaultHeadersLayout);

    // Default: Cells
    m_spbDefaultCellColumns = new QSpinBox(this);
    m_spbDefaultCellColumns->setRange(1, 1000);
    m_spbDefaultCellColumns->setToolTip(QStringLiteral("Default number of columns of new documents"));
    connect(m_spbDefaultCellColumns, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentSettings::onSettingsChanged);

    m_spbDefaultCellRows = new QSpinBox(this);
    m_spbDefaultCellRows->setRange(1, 1000);
    m_spbDefaultCellRows->setToolTip(QStringLiteral("Default number of rows of new documents"));
    connect(m_spbDefaultCellRows, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentSettings::onSettingsChanged);

    QFormLayout *defaultCellsLayout = new QFormLayout;
    defaultCellsLayout->addRow(QStringLiteral("Number of columns"), m_spbDefaultCellColumns);
    defaultCellsLayout->addRow(QStringLiteral("Number of rows"), m_spbDefaultCellRows);

    QGroupBox *defaultCellsGroup = new QGroupBox(QStringLiteral("Cells"));
    defaultCellsGroup->setLayout(defaultCellsLayout);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(defaultHeadersGroup);
    layout->addWidget(defaultCellsGroup);
    layout->addStretch();

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}


QString PreferencesDocumentSettings::title() const
{
    return QStringLiteral("Document");
}


void PreferencesDocumentSettings::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


void PreferencesDocumentSettings::onSettingsChanged()
{
    emit settingsChanged();
}


void PreferencesDocumentSettings::setDefaultHeaderLabelHorizontal(const Settings::HeaderLabel type)
{
    if (type != defaultHeaderLabelHorizontal()) {
        onSettingsChanged();
    }

    foreach (QAbstractButton *button, m_grpDefaultHeaderLabelHorizontal->buttons()) {
        if (m_grpDefaultHeaderLabelHorizontal->id(button) == (int) type) {
            button->setChecked(true);
        }
    }
}


Settings::HeaderLabel PreferencesDocumentSettings::defaultHeaderLabelHorizontal() const
{
    return static_cast<Settings::HeaderLabel>( m_grpDefaultHeaderLabelHorizontal->checkedId() );
}


void PreferencesDocumentSettings::setDefaultHeaderLabelVertical(const Settings::HeaderLabel type)
{
    if (type != defaultHeaderLabelVertical()) {
        onSettingsChanged();
    }

    foreach (QAbstractButton *button, m_grpDefaultHeaderLabelVertical->buttons()) {
        if (m_grpDefaultHeaderLabelVertical->id(button) == (int) type) {
            button->setChecked(true);
        }
    }
}


Settings::HeaderLabel PreferencesDocumentSettings::defaultHeaderLabelVertical() const
{
    return static_cast<Settings::HeaderLabel>( m_grpDefaultHeaderLabelVertical->checkedId() );
}


void PreferencesDocumentSettings::setDefaultCellColumns(const int number)
{
    m_spbDefaultCellColumns->setValue(number);
}


int PreferencesDocumentSettings::defaultCellColumns() const
{
    return m_spbDefaultCellColumns->value();
}


void PreferencesDocumentSettings::setDefaultCellRows(const int number)
{
    m_spbDefaultCellRows->setValue(number);
}


int PreferencesDocumentSettings::defaultCellRows() const
{
    return m_spbDefaultCellRows->value();
}
