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
    QRadioButton *rdbHorizontalHeaderLabelsLetters = new QRadioButton(QStringLiteral("Letters"));
    rdbHorizontalHeaderLabelsLetters->setToolTip(QStringLiteral("Horizontal header labels as capital letters"));

    QRadioButton *rdbHorizontalHeaderLabelsNumbers = new QRadioButton(QStringLiteral("Numbers"));
    rdbHorizontalHeaderLabelsNumbers->setToolTip(QStringLiteral("Horizontal header labels as numbers"));

    horizontalHeaderLabelsGroup = new QButtonGroup(this);
    horizontalHeaderLabelsGroup->addButton(rdbHorizontalHeaderLabelsLetters, 0);
    horizontalHeaderLabelsGroup->addButton(rdbHorizontalHeaderLabelsNumbers, 1);
    connect(horizontalHeaderLabelsGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentWidget::onSettingChanged);

    QHBoxLayout *horizontalHeaderLabelsBox = new QHBoxLayout;
    horizontalHeaderLabelsBox->addWidget(rdbHorizontalHeaderLabelsLetters);
    horizontalHeaderLabelsBox->addWidget(rdbHorizontalHeaderLabelsNumbers);

    QRadioButton *rdbVerticalHeaderLabelsLetters = new QRadioButton(QStringLiteral("Letters"));
    rdbVerticalHeaderLabelsLetters->setToolTip(QStringLiteral("Vertical header labels as capital letters"));

    QRadioButton *rdbVerticalHeaderLabelsNumbers = new QRadioButton(QStringLiteral("Numbers"));
    rdbVerticalHeaderLabelsNumbers->setToolTip(QStringLiteral("Vertical header labels as numbers"));

    verticalHeaderLabelsGroup = new QButtonGroup(this);
    verticalHeaderLabelsGroup->addButton(rdbVerticalHeaderLabelsLetters, 0);
    verticalHeaderLabelsGroup->addButton(rdbVerticalHeaderLabelsNumbers, 1);
    connect(verticalHeaderLabelsGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &PreferencesDocumentWidget::onSettingChanged);

    QHBoxLayout *verticalHeaderLabelsBox = new QHBoxLayout;
    verticalHeaderLabelsBox->addWidget(rdbVerticalHeaderLabelsLetters);
    verticalHeaderLabelsBox->addWidget(rdbVerticalHeaderLabelsNumbers);

    QFormLayout *headerLabelsLayout = new QFormLayout;
    headerLabelsLayout->addRow(QStringLiteral("Horizontal header"), horizontalHeaderLabelsBox);
    headerLabelsLayout->addRow(QStringLiteral("Vertical header"), verticalHeaderLabelsBox);

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
int PreferencesDocumentWidget::horizontalHeaderLabels() const
{
    return horizontalHeaderLabelsGroup->checkedId();
}


/**
 * Sets type of the horizontal header labels.
 */
void PreferencesDocumentWidget::setHorizontalHeaderLabels(const int id)
{
    if (id != horizontalHeaderLabels()) {
        onSettingChanged();
    }

    foreach (QAbstractButton *button, horizontalHeaderLabelsGroup->buttons()) {
        if (horizontalHeaderLabelsGroup->id(button) == id) {
            button->setChecked(true);
        }
    }
}


/**
 * Returns type of the vertical header labels.
 */
int PreferencesDocumentWidget::verticalHeaderLabels() const
{
    return verticalHeaderLabelsGroup->checkedId();
}


/**
 * Sets type of the vertical header labels.
 */
void PreferencesDocumentWidget::setVerticalHeaderLabels(const int id)
{
    if (id != verticalHeaderLabels()) {
        onSettingChanged();
    }

    foreach (QAbstractButton *button, verticalHeaderLabelsGroup->buttons()) {
        if (verticalHeaderLabelsGroup->id(button) == id) {
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
