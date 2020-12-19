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

#include "preferences_document_settings.h"

#include <QAbstractButton>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QTabWidget>
#include <QVBoxLayout>


PreferencesDocumentWidget::PreferencesDocumentWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *label = new QLabel(QStringLiteral("<strong style=\"font-size:large;\">Document</strong>"));

    // Tab box
    QTabWidget *tabBox = new QTabWidget;
    tabBox->addTab(tabDefaultSettings(), QStringLiteral("Default"));

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(tabBox);

    setLayout(layout);
}


/**
 * Creates the default settings tab page.
 */
QWidget *PreferencesDocumentWidget::tabDefaultSettings() {

    // Default: Headers
    QRadioButton *rdbDefaultHeaderLabelHorizontalLetters = new QRadioButton(QStringLiteral("Letters"));
    rdbDefaultHeaderLabelHorizontalLetters->setToolTip(QStringLiteral("Capital letters as default horizontal header labels"));

    QRadioButton *rdbDefaultHeaderLabelHorizontalNumbers = new QRadioButton(QStringLiteral("Numbers"));
    rdbDefaultHeaderLabelHorizontalNumbers->setToolTip(QStringLiteral("Decimal numbers as default horizontal header labels"));

    grpDefaultHeaderLabelHorizontal = new QButtonGroup(this);
    grpDefaultHeaderLabelHorizontal->addButton(rdbDefaultHeaderLabelHorizontalLetters, (int) Settings::HeaderLabel::Letter);
    grpDefaultHeaderLabelHorizontal->addButton(rdbDefaultHeaderLabelHorizontalNumbers, (int) Settings::HeaderLabel::Decimal);
    connect(grpDefaultHeaderLabelHorizontal, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentWidget::onSettingChanged);

    QHBoxLayout *defaultHeaderLabelHorizontalBox = new QHBoxLayout;
    defaultHeaderLabelHorizontalBox->addWidget(rdbDefaultHeaderLabelHorizontalLetters);
    defaultHeaderLabelHorizontalBox->addWidget(rdbDefaultHeaderLabelHorizontalNumbers);

    QRadioButton *rdbDefaultHeaderLabelVerticalLetters = new QRadioButton(QStringLiteral("Letters"));
    rdbDefaultHeaderLabelVerticalLetters->setToolTip(QStringLiteral("Capital letters as default vertical header labels"));

    QRadioButton *rdbDefaultHeaderLabelVerticalNumbers = new QRadioButton(QStringLiteral("Numbers"));
    rdbDefaultHeaderLabelVerticalNumbers->setToolTip(QStringLiteral("Decimal numbers as default vertical header labels"));

    grpDefaultHeaderLabelVertical = new QButtonGroup(this);
    grpDefaultHeaderLabelVertical->addButton(rdbDefaultHeaderLabelVerticalLetters, (int) Settings::HeaderLabel::Letter);
    grpDefaultHeaderLabelVertical->addButton(rdbDefaultHeaderLabelVerticalNumbers, (int) Settings::HeaderLabel::Decimal);
    connect(grpDefaultHeaderLabelVertical, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentWidget::onSettingChanged);

    QHBoxLayout *defaultHeaderLabelVerticalBox = new QHBoxLayout;
    defaultHeaderLabelVerticalBox->addWidget(rdbDefaultHeaderLabelVerticalLetters);
    defaultHeaderLabelVerticalBox->addWidget(rdbDefaultHeaderLabelVerticalNumbers);

    QFormLayout *defaultHeadersLayout = new QFormLayout;
    defaultHeadersLayout->addRow(QStringLiteral("Labels of horizontal header"), defaultHeaderLabelHorizontalBox);
    defaultHeadersLayout->addRow(QStringLiteral("Labels of vertical header"), defaultHeaderLabelVerticalBox);

    QGroupBox *defaultHeadersGroup = new QGroupBox(QStringLiteral("Headers"));
    defaultHeadersGroup->setLayout(defaultHeadersLayout);

    // Default: Cells
    spbDefaultCellColumns = new QSpinBox(this);
    spbDefaultCellColumns->setRange(1, 1000);
    spbDefaultCellColumns->setToolTip(QStringLiteral("Default number of columns of new documents"));
    connect(spbDefaultCellColumns, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentWidget::onSettingChanged);

    spbDefaultCellRows = new QSpinBox(this);
    spbDefaultCellRows->setRange(1, 1000);
    spbDefaultCellRows->setToolTip(QStringLiteral("Default number of rows of new documents"));
    connect(spbDefaultCellRows, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentWidget::onSettingChanged);

    QFormLayout *defaultCellsLayout = new QFormLayout;
    defaultCellsLayout->addRow(QStringLiteral("Number of columns"), spbDefaultCellColumns);
    defaultCellsLayout->addRow(QStringLiteral("Number of rows"), spbDefaultCellRows);

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


/**
 * Returns the default type of the horizontal header labels of documents.
 */
Settings::HeaderLabel PreferencesDocumentWidget::defaultHeaderLabelHorizontal() const
{
    return static_cast<Settings::HeaderLabel>( grpDefaultHeaderLabelHorizontal->checkedId() );
}


/**
 * Sets the default type of the horizontal header labels of documents.
 */
void PreferencesDocumentWidget::setDefaultHeaderLabelHorizontal(const Settings::HeaderLabel type)
{
    if (type != defaultHeaderLabelHorizontal()) {
        onSettingChanged();
    }

    foreach (QAbstractButton *button, grpDefaultHeaderLabelHorizontal->buttons()) {
        if (grpDefaultHeaderLabelHorizontal->id(button) == (int) type) {
            button->setChecked(true);
        }
    }
}


/**
 * Returns the default type of the vertical header labels of documents.
 */
Settings::HeaderLabel PreferencesDocumentWidget::defaultHeaderLabelVertical() const
{
    return static_cast<Settings::HeaderLabel>( grpDefaultHeaderLabelVertical->checkedId() );
}


/**
 * Sets the default type of the vertical header labels of documents.
 */
void PreferencesDocumentWidget::setDefaultHeaderLabelVertical(const Settings::HeaderLabel type)
{
    if (type != defaultHeaderLabelVertical()) {
        onSettingChanged();
    }

    foreach (QAbstractButton *button, grpDefaultHeaderLabelVertical->buttons()) {
        if (grpDefaultHeaderLabelVertical->id(button) == (int) type) {
            button->setChecked(true);
        }
    }
}


/**
 * Returns the default number of columns of new documents.
 */
int PreferencesDocumentWidget::defaultCellColumns() const
{
    return spbDefaultCellColumns->value();
}


/**
 * Sets the default number of columns of new documents.
 */
void PreferencesDocumentWidget::setDefaultCellColumns(const int number)
{
    spbDefaultCellColumns->setValue(number);
}


/**
 * Returns the default number of rows of new documents.
 */
int PreferencesDocumentWidget::defaultCellRows() const
{
    return spbDefaultCellRows->value();
}


/**
 * Sets the default number of rows of new documents.
 */
void PreferencesDocumentWidget::setDefaultCellRows(const int number)
{
    spbDefaultCellRows->setValue(number);
}
