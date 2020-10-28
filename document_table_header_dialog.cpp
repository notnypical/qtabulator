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

#include "document_table_header_dialog.h"

#include <QDialogButtonBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>


DocumentTableHeaderDialog::DocumentTableHeaderDialog(const int number, QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Group box
    QString text = number >= 0 ? QStringLiteral("Binary Number") : QStringLiteral("Binary Numbers");
    QString toolTip = number >= 0 ? QStringLiteral("Change label to a binary number") : QStringLiteral("Change all labels to binary numbers");
    QRadioButton *rdbBinary = new QRadioButton(text);
    rdbBinary->setToolTip(toolTip);

    text = QStringLiteral("With prefix 0b");
    toolTip = number >= 0 ? QStringLiteral("Change label to a binary number with prefix 0b otherwise without prefix") : QStringLiteral("Change all labels to binary numbers with prefix 0b otherwise without prefix");
    chkBinary = new QCheckBox(text);
    chkBinary->setChecked(true);
    chkBinary->setEnabled(false);
    chkBinary->setToolTip(toolTip);
    connect(rdbBinary, &QRadioButton::toggled, this, [=](){ chkBinary->setEnabled(rdbBinary->isChecked()); });

    text = number >= 0 ? QStringLiteral("Octal Number") : QStringLiteral("Octal Numbers");
    toolTip = number >= 0 ? QStringLiteral("Change label to a octal number") : QStringLiteral("Change all labels to octal numbers");
    QRadioButton *rdbOctal = new QRadioButton(text);
    rdbOctal->setToolTip(toolTip);

    text = number >= 0 ? QStringLiteral("Decimal Number") : QStringLiteral("Decimal Numbers");
    toolTip = number >= 0 ? QStringLiteral("Change label to a decimal number") : QStringLiteral("Change all labels to decimal numbers");
    QRadioButton *rdbDecimal = new QRadioButton(text);
    rdbDecimal->setToolTip(toolTip);

    text = number >= 0 ? QStringLiteral("Hexadecimal Number") : QStringLiteral("Hexadecimal Numbers");
    toolTip = number >= 0 ? QStringLiteral("Change label to a hexadecimal number") : QStringLiteral("Change all labels to hexadecimal numbers");
    QRadioButton *rdbHexadecimal = new QRadioButton(text);
    rdbHexadecimal->setToolTip(toolTip);

    text = number >= 0 ? QStringLiteral("Capital Letter") : QStringLiteral("Capital Letters");
    toolTip = number >= 0 ? QStringLiteral("Change label to a capital letter") : QStringLiteral("Change all labels to capital letters");
    QRadioButton *rdbLetter = new QRadioButton(text);
    rdbLetter->setToolTip(toolTip);

    grpHeaderLabel = new QButtonGroup(this);
    grpHeaderLabel->addButton(rdbBinary, (int) Settings::HeaderLabel::Binary);
    grpHeaderLabel->addButton(rdbOctal, (int) Settings::HeaderLabel::Octal);
    grpHeaderLabel->addButton(rdbDecimal, (int) Settings::HeaderLabel::Decimal);
    grpHeaderLabel->addButton(rdbHexadecimal, (int) Settings::HeaderLabel::Hexadecimal);
    grpHeaderLabel->addButton(rdbLetter, (int) Settings::HeaderLabel::Letter);
    connect(grpHeaderLabel, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &DocumentTableHeaderDialog::onSettingChanged);

    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addWidget(rdbBinary, 0, 0);
    groupLayout->addWidget(chkBinary, 0, 1);
    groupLayout->addWidget(rdbOctal, 1, 0);
    groupLayout->addWidget(rdbDecimal, 2, 0);
    groupLayout->addWidget(rdbHexadecimal, 3, 0);
    groupLayout->addWidget(rdbLetter, 4, 0);
    groupLayout->setVerticalSpacing(1);

    text = number >= 0 ? QStringLiteral("Change label to a …") : QStringLiteral("Change all labels to …");
    QGroupBox *groupBox = new QGroupBox(text);
    groupBox->setLayout(groupLayout);

    // Button box
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonOk = buttonBox->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DocumentTableHeaderDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DocumentTableHeaderDialog::reject);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(groupBox);
    layout->addWidget(buttonBox);

    setLayout(layout);
}


/**
 * Enables the ok button if a setting has been changed.
 */
void DocumentTableHeaderDialog::onSettingChanged()
{
    buttonOk->setEnabled(true);
}


/**
 * Returns the type of the header label.
 */
Settings::HeaderLabel DocumentTableHeaderDialog::headerLabelType() const
{
    return static_cast<Settings::HeaderLabel>( grpHeaderLabel->checkedId() );
}


/**
 * Returns the parameter of the header label.
 */
QString DocumentTableHeaderDialog::headerLabelParameter() const
{
    Settings::HeaderLabel type = headerLabelType();

    if (type == Settings::HeaderLabel::Binary) {
        return chkBinary->isChecked() ? QStringLiteral("0b") : QString();
    }
    else {
        return QString();
    }
}
