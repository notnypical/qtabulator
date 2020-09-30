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

#include <QAbstractButton>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>


PreferencesDocumentWidget::PreferencesDocumentWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *label = new QLabel(QStringLiteral("<strong style=\"font-size:large;\">Document</strong>"));

    // Header Labels
    QRadioButton *rdbHorizontalHeaderLabelsDecimals = new QRadioButton(QStringLiteral("Decimal Numbers"));
    rdbHorizontalHeaderLabelsDecimals->setToolTip(QStringLiteral("Horizontal header labels as decimal numbers"));

    QRadioButton *rdbHorizontalHeaderLabelsLetters = new QRadioButton(QStringLiteral("Letters"));
    rdbHorizontalHeaderLabelsLetters->setToolTip(QStringLiteral("Horizontal header labels as capital letters"));

    horizontalHeaderLabelsGroup = new QButtonGroup(this);
    horizontalHeaderLabelsGroup->addButton(rdbHorizontalHeaderLabelsDecimals, 10);
    horizontalHeaderLabelsGroup->addButton(rdbHorizontalHeaderLabelsLetters, 26);
    connect(horizontalHeaderLabelsGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentWidget::onSettingChanged);

    QHBoxLayout *horizontalHeaderLabelsBox = new QHBoxLayout;
    horizontalHeaderLabelsBox->addWidget(rdbHorizontalHeaderLabelsDecimals);
    horizontalHeaderLabelsBox->addWidget(rdbHorizontalHeaderLabelsLetters);

    QRadioButton *rdbHorizontalHeaderDecimalStart0 = new QRadioButton(QStringLiteral("0"));
    rdbHorizontalHeaderDecimalStart0->setToolTip(QStringLiteral("Start decimal numbers with 0"));

    QRadioButton *rdbHorizontalHeaderDecimalStart1 = new QRadioButton(QStringLiteral("1"));
    rdbHorizontalHeaderDecimalStart1->setToolTip(QStringLiteral("Start decimal numbers with 1"));

    horizontalHeaderDecimalStartGroup = new QButtonGroup(this);
    horizontalHeaderDecimalStartGroup->addButton(rdbHorizontalHeaderDecimalStart0, 0);
    horizontalHeaderDecimalStartGroup->addButton(rdbHorizontalHeaderDecimalStart1, 1);
    connect(horizontalHeaderDecimalStartGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentWidget::onSettingChanged);

    QHBoxLayout *horizontalHeaderDecimalStartBox = new QHBoxLayout;
    horizontalHeaderDecimalStartBox->addWidget(new QLabel("Start decimal numbers with:"));
    horizontalHeaderDecimalStartBox->addWidget(rdbHorizontalHeaderDecimalStart0);
    horizontalHeaderDecimalStartBox->addWidget(rdbHorizontalHeaderDecimalStart1);

    QRadioButton *rdbVerticalHeaderLabelsDecimals = new QRadioButton(QStringLiteral("Decimal Numbers"));
    rdbVerticalHeaderLabelsDecimals->setToolTip(QStringLiteral("Vertical header labels as decimal numbers"));

    QRadioButton *rdbVerticalHeaderLabelsLetters = new QRadioButton(QStringLiteral("Letters"));
    rdbVerticalHeaderLabelsLetters->setToolTip(QStringLiteral("Vertical header labels as capital letters"));

    verticalHeaderLabelsGroup = new QButtonGroup(this);
    verticalHeaderLabelsGroup->addButton(rdbVerticalHeaderLabelsDecimals, 10);
    verticalHeaderLabelsGroup->addButton(rdbVerticalHeaderLabelsLetters, 26);
    connect(verticalHeaderLabelsGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentWidget::onSettingChanged);

    QHBoxLayout *verticalHeaderLabelsBox = new QHBoxLayout;
    verticalHeaderLabelsBox->addWidget(rdbVerticalHeaderLabelsDecimals);
    verticalHeaderLabelsBox->addWidget(rdbVerticalHeaderLabelsLetters);

    QRadioButton *rdbVerticalHeaderDecimalStart0 = new QRadioButton(QStringLiteral("0"));
    rdbVerticalHeaderDecimalStart0->setToolTip(QStringLiteral("Start decimal numbers with 0"));

    QRadioButton *rdbVerticalHeaderDecimalStart1 = new QRadioButton(QStringLiteral("1"));
    rdbVerticalHeaderDecimalStart1->setToolTip(QStringLiteral("Start decimal numbers with 1"));

    verticalHeaderDecimalStartGroup = new QButtonGroup(this);
    verticalHeaderDecimalStartGroup->addButton(rdbVerticalHeaderDecimalStart0, 0);
    verticalHeaderDecimalStartGroup->addButton(rdbVerticalHeaderDecimalStart1, 1);
    connect(verticalHeaderDecimalStartGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentWidget::onSettingChanged);

    QHBoxLayout *verticalHeaderDecimalStartBox = new QHBoxLayout;
    verticalHeaderDecimalStartBox->addWidget(new QLabel("Start decimal numbers with:"));
    verticalHeaderDecimalStartBox->addWidget(rdbVerticalHeaderDecimalStart0);
    verticalHeaderDecimalStartBox->addWidget(rdbVerticalHeaderDecimalStart1);

    QFormLayout *headerLabelsLayout = new QFormLayout;
    headerLabelsLayout->addRow(QStringLiteral("Horizontal header"), horizontalHeaderLabelsBox);
    headerLabelsLayout->addRow(QString(), horizontalHeaderDecimalStartBox);
    headerLabelsLayout->addRow(QStringLiteral("Vertical header"), verticalHeaderLabelsBox);
    headerLabelsLayout->addRow(QString(), verticalHeaderDecimalStartBox);

    QGroupBox *headerLabelsGroup = new QGroupBox(QStringLiteral("Header Labels"));
    headerLabelsGroup->setLayout(headerLabelsLayout);

    // New Document
    spbNewDocumentColumns = new QSpinBox(this);
    spbNewDocumentColumns->setRange(1, 100);
    spbNewDocumentColumns->setToolTip(QStringLiteral("Number of columns of new documents"));
    connect(spbNewDocumentColumns, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentWidget::onSettingChanged);

    spbNewDocumentRows = new QSpinBox(this);
    spbNewDocumentRows->setRange(1, 100);
    spbNewDocumentRows->setToolTip(QStringLiteral("Number of rows of new documents"));
    connect(spbNewDocumentRows, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferencesDocumentWidget::onSettingChanged);

    QFormLayout *newDocumentLayout = new QFormLayout;
    newDocumentLayout->addRow(QStringLiteral("Number of columns"), spbNewDocumentColumns);
    newDocumentLayout->addRow(QStringLiteral("Number of rows"), spbNewDocumentRows);

    QGroupBox *newDocumentGroup = new QGroupBox(QStringLiteral("New Document"));
    newDocumentGroup->setLayout(newDocumentLayout);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(headerLabelsGroup);
    layout->addWidget(newDocumentGroup);
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


/**
 * Returns type of the horizontal header labels.
 */
Settings::HeaderLabel PreferencesDocumentWidget::horizontalHeaderLabels() const
{
    return static_cast<Settings::HeaderLabel>( horizontalHeaderLabelsGroup->checkedId() );
}


/**
 * Sets type of the horizontal header labels.
 */
void PreferencesDocumentWidget::setHorizontalHeaderLabels(const Settings::HeaderLabel type)
{
    if (type != horizontalHeaderLabels()) {
        onSettingChanged();
    }

    foreach (QAbstractButton *button, horizontalHeaderLabelsGroup->buttons()) {
        if (horizontalHeaderLabelsGroup->id(button) == (int) type) {
            button->setChecked(true);
        }
    }
}


int PreferencesDocumentWidget::horizontalHeaderDecimalStart() const
{
    return horizontalHeaderDecimalStartGroup->checkedId();
}


void PreferencesDocumentWidget::setHorizontalHeaderDecimalStart(const int number)
{
    if (number != horizontalHeaderDecimalStart()) {
        onSettingChanged();
    }

    foreach (QAbstractButton *button, horizontalHeaderDecimalStartGroup->buttons()) {
        if (horizontalHeaderDecimalStartGroup->id(button) == number) {
            button->setChecked(true);
        }
    }
}


/**
 * Returns type of the vertical header labels.
 */
Settings::HeaderLabel PreferencesDocumentWidget::verticalHeaderLabels() const
{
    return static_cast<Settings::HeaderLabel>( verticalHeaderLabelsGroup->checkedId() );
}


/**
 * Sets type of the vertical header labels.
 */
void PreferencesDocumentWidget::setVerticalHeaderLabels(const Settings::HeaderLabel type)
{
    if (type != verticalHeaderLabels()) {
        onSettingChanged();
    }

    foreach (QAbstractButton *button, verticalHeaderLabelsGroup->buttons()) {
        if (verticalHeaderLabelsGroup->id(button) == (int) type) {
            button->setChecked(true);
        }
    }
}


int PreferencesDocumentWidget::verticalHeaderDecimalStart() const
{
    return verticalHeaderDecimalStartGroup->checkedId();
}


void PreferencesDocumentWidget::setVerticalHeaderDecimalStart(const int number)
{
    if (number != verticalHeaderDecimalStart()) {
        onSettingChanged();
    }

    foreach (QAbstractButton *button, verticalHeaderDecimalStartGroup->buttons()) {
        if (verticalHeaderDecimalStartGroup->id(button) == number) {
            button->setChecked(true);
        }
    }
}


/**
 * Returns number of columns of new document.
 */
int PreferencesDocumentWidget::newDocumentColumns() const
{
    return spbNewDocumentColumns->value();
}


/**
 * Sets number of columns of new document.
 */
void PreferencesDocumentWidget::setNewDocumentColumns(const int number)
{
    spbNewDocumentColumns->setValue(number);
}


/**
 * Returns number of rows of new document.
 */
int PreferencesDocumentWidget::newDocumentRows() const
{
    return spbNewDocumentRows->value();
}


/**
 * Sets number of rows of new document.
 */
void PreferencesDocumentWidget::setNewDocumentRows(const int number)
{
    spbNewDocumentRows->setValue(number);
}
