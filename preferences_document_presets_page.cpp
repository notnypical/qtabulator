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

#include "preferences_document_presets_page.h"

#include <QAbstractButton>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>


PreferencesDocumentPresetsPage::PreferencesDocumentPresetsPage(QWidget *parent)
    : QWidget(parent)
{
    // Title
    auto *title = new QLabel(tr("<strong style=\"font-size:large;\">Document Presets</strong>"));

    // Header Labels
    auto *rdbDefaultHeaderLabelHorizontalLetters = new QRadioButton(tr("Letters"));
    rdbDefaultHeaderLabelHorizontalLetters->setToolTip(tr("Capital letters as default horizontal header labels of new documents"));

    auto *rdbDefaultHeaderLabelHorizontalNumbers = new QRadioButton(tr("Numbers"));
    rdbDefaultHeaderLabelHorizontalNumbers->setToolTip(tr("Decimal numbers as default horizontal header labels of new documents"));

    m_grpDefaultHeaderLabelHorizontal = new QButtonGroup(this);
    m_grpDefaultHeaderLabelHorizontal->addButton(rdbDefaultHeaderLabelHorizontalLetters, (int) Preferences::HeaderLabel::Letter);
    m_grpDefaultHeaderLabelHorizontal->addButton(rdbDefaultHeaderLabelHorizontalNumbers, (int) Preferences::HeaderLabel::Decimal);
    connect(m_grpDefaultHeaderLabelHorizontal, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentPresetsPage::onPreferencesChanged);

    auto *defaultHeaderLabelHorizontalBox = new QHBoxLayout;
    defaultHeaderLabelHorizontalBox->addWidget(rdbDefaultHeaderLabelHorizontalLetters);
    defaultHeaderLabelHorizontalBox->addWidget(rdbDefaultHeaderLabelHorizontalNumbers);

    auto *rdbDefaultHeaderLabelVerticalLetters = new QRadioButton(tr("Letters"));
    rdbDefaultHeaderLabelVerticalLetters->setToolTip(tr("Capital letters as default vertical header labels of new documents"));

    auto *rdbDefaultHeaderLabelVerticalNumbers = new QRadioButton(tr("Numbers"));
    rdbDefaultHeaderLabelVerticalNumbers->setToolTip(tr("Decimal numbers as default vertical header labels of new documents"));

    m_grpDefaultHeaderLabelVertical = new QButtonGroup(this);
    m_grpDefaultHeaderLabelVertical->addButton(rdbDefaultHeaderLabelVerticalLetters, (int) Preferences::HeaderLabel::Letter);
    m_grpDefaultHeaderLabelVertical->addButton(rdbDefaultHeaderLabelVerticalNumbers, (int) Preferences::HeaderLabel::Decimal);
    connect(m_grpDefaultHeaderLabelVertical, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentPresetsPage::onPreferencesChanged);

    auto *defaultHeaderLabelVerticalBox = new QHBoxLayout;
    defaultHeaderLabelVerticalBox->addWidget(rdbDefaultHeaderLabelVerticalLetters);
    defaultHeaderLabelVerticalBox->addWidget(rdbDefaultHeaderLabelVerticalNumbers);

    auto *defaultHeaderLabelLayout = new QFormLayout;
    defaultHeaderLabelLayout->addRow(tr("Labels of the horizontal header"), defaultHeaderLabelHorizontalBox);
    defaultHeaderLabelLayout->addRow(tr("Labels of the vertical header"), defaultHeaderLabelVerticalBox);

    auto *defaultHeaderLabelGroup = new QGroupBox(tr("Header Labels"));
    defaultHeaderLabelGroup->setLayout(defaultHeaderLabelLayout);

    // Cell Counts
    m_spbDefaultCellCountColumn = new QSpinBox(this);
    m_spbDefaultCellCountColumn->setRange(1, 1000);
    m_spbDefaultCellCountColumn->setToolTip(tr("Default number of columns of new documents"));
    connect(m_spbDefaultCellCountColumn, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentPresetsPage::onPreferencesChanged);

    m_spbDefaultCellCountRow = new QSpinBox(this);
    m_spbDefaultCellCountRow->setRange(1, 1000);
    m_spbDefaultCellCountRow->setToolTip(tr("Default number of rows of new documents"));
    connect(m_spbDefaultCellCountRow, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentPresetsPage::onPreferencesChanged);

    auto *defaultCellCountLayout = new QFormLayout;
    defaultCellCountLayout->addRow(tr("Number of columns"), m_spbDefaultCellCountColumn);
    defaultCellCountLayout->addRow(tr("Number of rows"), m_spbDefaultCellCountRow);

    auto *defaultCellCountGroup = new QGroupBox(tr("Cell Counts"));
    defaultCellCountGroup->setLayout(defaultCellCountLayout);

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(title);
    m_layout->addWidget(defaultHeaderLabelGroup);
    m_layout->addWidget(defaultCellCountGroup);
    m_layout->addStretch();
}


void PreferencesDocumentPresetsPage::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


QString PreferencesDocumentPresetsPage::title() const
{
    return tr("Document Presets");
}


void PreferencesDocumentPresetsPage::onPreferencesChanged()
{
    emit preferencesChanged();
}


void PreferencesDocumentPresetsPage::setDefaultHeaderLabelHorizontal(const Preferences::HeaderLabel type)
{
    if (type != defaultHeaderLabelHorizontal())
        onPreferencesChanged();

    for (auto *button : m_grpDefaultHeaderLabelHorizontal->buttons())
        if (m_grpDefaultHeaderLabelHorizontal->id(button) == (int) type)
            button->setChecked(true);
}


Preferences::HeaderLabel PreferencesDocumentPresetsPage::defaultHeaderLabelHorizontal() const
{
    return static_cast<Preferences::HeaderLabel> (m_grpDefaultHeaderLabelHorizontal->checkedId());
}


void PreferencesDocumentPresetsPage::setDefaultHeaderLabelVertical(const Preferences::HeaderLabel type)
{
    if (type != defaultHeaderLabelVertical())
        onPreferencesChanged();

    for (auto *button : m_grpDefaultHeaderLabelVertical->buttons())
        if (m_grpDefaultHeaderLabelVertical->id(button) == (int) type)
            button->setChecked(true);
}


Preferences::HeaderLabel PreferencesDocumentPresetsPage::defaultHeaderLabelVertical() const
{
    return static_cast<Preferences::HeaderLabel> (m_grpDefaultHeaderLabelVertical->checkedId());
}


void PreferencesDocumentPresetsPage::setDefaultCellCountColumn(const int val)
{
    m_spbDefaultCellCountColumn->setValue(val);
}


int PreferencesDocumentPresetsPage::defaultCellCountColumn() const
{
    return m_spbDefaultCellCountColumn->value();
}


void PreferencesDocumentPresetsPage::setDefaultCellCountRow(const int val)
{
    m_spbDefaultCellCountRow->setValue(val);
}


int PreferencesDocumentPresetsPage::defaultCellCountRow() const
{
    return m_spbDefaultCellCountRow->value();
}
