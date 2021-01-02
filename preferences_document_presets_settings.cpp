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

#include "preferences_document_presets_settings.h"

#include <QAbstractButton>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QTabWidget>
#include <QVBoxLayout>


PreferencesDocumentPresetsSettings::PreferencesDocumentPresetsSettings(QWidget *parent) :
    QWidget(parent)
{
    // Title
    auto *title = new QLabel(tr("<strong style=\"font-size:large;\">Document Presets Settings</strong>"));

    // Header Label
    auto *rdbDefaultHeaderLabelHorizontalLetters = new QRadioButton(tr("Letters"));
    rdbDefaultHeaderLabelHorizontalLetters->setToolTip(tr("Capital letters as default horizontal header labels"));

    auto *rdbDefaultHeaderLabelHorizontalNumbers = new QRadioButton(tr("Numbers"));
    rdbDefaultHeaderLabelHorizontalNumbers->setToolTip(tr("Decimal numbers as default horizontal header labels"));

    m_grpDefaultHeaderLabelHorizontal = new QButtonGroup(this);
    m_grpDefaultHeaderLabelHorizontal->addButton(rdbDefaultHeaderLabelHorizontalLetters, (int) Settings::HeaderLabel::Letter);
    m_grpDefaultHeaderLabelHorizontal->addButton(rdbDefaultHeaderLabelHorizontalNumbers, (int) Settings::HeaderLabel::Decimal);
    connect(m_grpDefaultHeaderLabelHorizontal, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentPresetsSettings::onSettingsChanged);

    auto *defaultHeaderLabelHorizontalBox = new QHBoxLayout;
    defaultHeaderLabelHorizontalBox->addWidget(rdbDefaultHeaderLabelHorizontalLetters);
    defaultHeaderLabelHorizontalBox->addWidget(rdbDefaultHeaderLabelHorizontalNumbers);

    auto *defaultHeaderLabelLayout = new QFormLayout;
    defaultHeaderLabelLayout->addRow(tr("Labels of horizontal header"), defaultHeaderLabelHorizontalBox);

    auto *defaultHeaderLabelGroup = new QGroupBox(tr("Header Label"));
    defaultHeaderLabelGroup->setLayout(defaultHeaderLabelLayout);

    // Cell Count
    m_spbDefaultCellCountColumn = new QSpinBox(this);
    m_spbDefaultCellCountColumn->setRange(DEFAULT_CELL_COUNT_COLUMN_MINIMUM, DEFAULT_CELL_COUNT_COLUMN_MAXIMUM);
    m_spbDefaultCellCountColumn->setToolTip(tr("Default number of columns of new documents"));
    connect(m_spbDefaultCellCountColumn, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentPresetsSettings::onSettingsChanged);

    m_spbDefaultCellCountRow = new QSpinBox(this);
    m_spbDefaultCellCountRow->setRange(DEFAULT_CELL_COUNT_ROW_MINIMUM, DEFAULT_CELL_COUNT_ROW_MAXIMUM);
    m_spbDefaultCellCountRow->setToolTip(tr("Default number of rows of new documents"));
    connect(m_spbDefaultCellCountRow, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentPresetsSettings::onSettingsChanged);

    auto *defaultCellCountLayout = new QFormLayout;
    defaultCellCountLayout->addRow(tr("Number of columns"), m_spbDefaultCellCountColumn);
    defaultCellCountLayout->addRow(tr("Number of rows"), m_spbDefaultCellCountRow);

    auto *defaultCellCountGroup = new QGroupBox(tr("Cell Count"));
    defaultCellCountGroup->setLayout(defaultCellCountLayout);

    // Tab box
    auto *tabBox = new QTabWidget;
    tabBox->addTab(tabDefaultSettings(), tr("Default"));

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(title);
    m_layout->addWidget(defaultHeaderLabelGroup);
    m_layout->addWidget(defaultCellCountGroup);
    m_layout->addWidget(tabBox);
    m_layout->addStretch();
}


QString PreferencesDocumentPresetsSettings::title() const
{
    return tr("Document Presets");
}


void PreferencesDocumentPresetsSettings::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


void PreferencesDocumentPresetsSettings::onSettingsChanged()
{
    emit settingsChanged();
}


QWidget *PreferencesDocumentPresetsSettings::tabDefaultSettings() {

    // Default: Headers
    auto *rdbDefaultHeaderLabelVerticalLetters = new QRadioButton(tr("Letters"));
    rdbDefaultHeaderLabelVerticalLetters->setToolTip(tr("Capital letters as default vertical header labels"));

    auto *rdbDefaultHeaderLabelVerticalNumbers = new QRadioButton(tr("Numbers"));
    rdbDefaultHeaderLabelVerticalNumbers->setToolTip(tr("Decimal numbers as default vertical header labels"));

    m_grpDefaultHeaderLabelVertical = new QButtonGroup(this);
    m_grpDefaultHeaderLabelVertical->addButton(rdbDefaultHeaderLabelVerticalLetters, (int) Settings::HeaderLabel::Letter);
    m_grpDefaultHeaderLabelVertical->addButton(rdbDefaultHeaderLabelVerticalNumbers, (int) Settings::HeaderLabel::Decimal);
    connect(m_grpDefaultHeaderLabelVertical, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentPresetsSettings::onSettingsChanged);

    auto *defaultHeaderLabelVerticalBox = new QHBoxLayout;
    defaultHeaderLabelVerticalBox->addWidget(rdbDefaultHeaderLabelVerticalLetters);
    defaultHeaderLabelVerticalBox->addWidget(rdbDefaultHeaderLabelVerticalNumbers);

    auto *defaultHeadersLayout = new QFormLayout;
    defaultHeadersLayout->addRow(tr("Labels of vertical header"), defaultHeaderLabelVerticalBox);

    auto *defaultHeadersGroup = new QGroupBox(tr("Headers"));
    defaultHeadersGroup->setLayout(defaultHeadersLayout);

    // Layout
    auto *layout = new QVBoxLayout;
    layout->addWidget(defaultHeadersGroup);
    layout->addStretch();

    auto *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}


void PreferencesDocumentPresetsSettings::setDefaultHeaderLabelHorizontal(const Settings::HeaderLabel type)
{
    if (type != defaultHeaderLabelHorizontal())
        onSettingsChanged();

    for (auto *button : m_grpDefaultHeaderLabelHorizontal->buttons())
        if (m_grpDefaultHeaderLabelHorizontal->id(button) == (int) type)
            button->setChecked(true);
}


Settings::HeaderLabel PreferencesDocumentPresetsSettings::defaultHeaderLabelHorizontal() const
{
    return static_cast<Settings::HeaderLabel> (m_grpDefaultHeaderLabelHorizontal->checkedId());
}


void PreferencesDocumentPresetsSettings::setDefaultHeaderLabelVertical(const Settings::HeaderLabel type)
{
    if (type != defaultHeaderLabelVertical()) {
        onSettingsChanged();
    }

    for (auto *button : m_grpDefaultHeaderLabelVertical->buttons()) {
        if (m_grpDefaultHeaderLabelVertical->id(button) == (int) type) {
            button->setChecked(true);
        }
    }
}


Settings::HeaderLabel PreferencesDocumentPresetsSettings::defaultHeaderLabelVertical() const
{
    return static_cast<Settings::HeaderLabel>( m_grpDefaultHeaderLabelVertical->checkedId() );
}


void PreferencesDocumentPresetsSettings::setDefaultCellCountColumn(const int val)
{
    m_spbDefaultCellCountColumn->setValue(val);
}


int PreferencesDocumentPresetsSettings::defaultCellCountColumn() const
{
    return m_spbDefaultCellCountColumn->value();
}


void PreferencesDocumentPresetsSettings::setDefaultCellCountRow(const int val)
{
    m_spbDefaultCellCountRow->setValue(val);
}


int PreferencesDocumentPresetsSettings::defaultCellCountRow() const
{
    return m_spbDefaultCellCountRow->value();
}
