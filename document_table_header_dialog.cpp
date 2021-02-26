/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of qTabulator, <https://github.com/notnypical/tabulator-qt>.
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
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>


DocumentTableHeaderDialog::DocumentTableHeaderDialog(const QString type, const int index, QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Group box
    QString text = index >= 0 ? tr("Binary Number") : tr("Binary Numbers");
    QString toolTip = index >= 0 ? tr("Change label to a binary number") : tr("Change all labels to binary numbers");
    QRadioButton *rdbBinary = new QRadioButton(text);
    rdbBinary->setToolTip(toolTip);

    text = tr("With prefix 0b");
    toolTip = index >= 0 ? tr("Change label to a binary number with prefix 0b otherwise without prefix") : tr("Change all labels to binary numbers with prefix 0b otherwise without prefix");
    chkBinary = new QCheckBox(text);
    chkBinary->setChecked(true);
    chkBinary->setEnabled(false);
    chkBinary->setToolTip(toolTip);
    connect(rdbBinary, &QRadioButton::toggled, this, [=](bool checked){ chkBinary->setEnabled(checked); });

    text = index >= 0 ? tr("Octal Number") : tr("Octal Numbers");
    toolTip = index >= 0 ? tr("Change label to a octal number") : tr("Change all labels to octal numbers");
    QRadioButton *rdbOctal = new QRadioButton(text);
    rdbOctal->setToolTip(toolTip);

    text = tr("With prefix 0o");
    toolTip = index >= 0 ? tr("Change label to a octal number with prefix 0o otherwise without prefix") : tr("Change all labels to octal numbers with prefix 0o otherwise without prefix");
    chkOctal = new QCheckBox(text);
    chkOctal->setChecked(true);
    chkOctal->setEnabled(false);
    chkOctal->setToolTip(toolTip);
    connect(rdbOctal, &QRadioButton::toggled, this, [=](bool checked){ chkOctal->setEnabled(checked); });

    text = index >= 0 ? tr("Decimal Number") : tr("Decimal Numbers");
    toolTip = index >= 0 ? tr("Change label to a decimal number") : tr("Change all labels to decimal numbers");
    QRadioButton *rdbDecimal = new QRadioButton(text);
    rdbDecimal->setToolTip(toolTip);

    text = tr("Enumeration starting with 1");
    toolTip = index >= 0 ? tr("Change label to a decimal number with the enumeration starting with 1 otherwise with 0") : tr("Change all labels to decimal numbers with the enumeration starting with 1 otherwise with 0");
    chkDecimal = new QCheckBox(text);
    chkDecimal->setChecked(true);
    chkDecimal->setEnabled(false);
    chkDecimal->setToolTip(toolTip);
    connect(rdbDecimal, &QRadioButton::toggled, this, [=](bool checked){ chkDecimal->setEnabled(checked); });

    text = index >= 0 ? tr("Hexadecimal Number") : tr("Hexadecimal Numbers");
    toolTip = index >= 0 ? tr("Change label to a hexadecimal number") : tr("Change all labels to hexadecimal numbers");
    QRadioButton *rdbHexadecimal = new QRadioButton(text);
    rdbHexadecimal->setToolTip(toolTip);

    text = tr("With prefix 0x");
    toolTip = index >= 0 ? tr("Change label to a hexadecimal number with prefix 0x otherwise without prefix") : tr("Change all labels to hexadecimal numbers with prefix 0x otherwise without prefix");
    chkHexadecimal = new QCheckBox(text);
    chkHexadecimal->setChecked(true);
    chkHexadecimal->setEnabled(false);
    chkHexadecimal->setToolTip(toolTip);
    connect(rdbHexadecimal, &QRadioButton::toggled, this, [=](bool checked){ chkHexadecimal->setEnabled(checked); });

    text = index >= 0 ? tr("Capital Letter") : tr("Capital Letters");
    toolTip = index >= 0 ? tr("Change label to a capital letter") : tr("Change all labels to capital letters");
    QRadioButton *rdbLetter = new QRadioButton(text);
    rdbLetter->setToolTip(toolTip);

    text = index >= 0 ? tr("Letter as uppercase letter") : tr("Letters as uppercase letters");
    toolTip = index >= 0 ? tr("Change label to a letter as uppercase letter otherwise lowercase letter") : tr("Change all labels to letters as uppercase letters otherwise lowercase letters");
    chkLetter = new QCheckBox(text);
    chkLetter->setChecked(true);
    chkLetter->setEnabled(false);
    chkLetter->setToolTip(toolTip);
    connect(rdbLetter, &QRadioButton::toggled, this, [=](bool checked){ chkLetter->setEnabled(checked); });

    text = index >= 0 ? tr("User-defined Text") : tr("User-defined Texts");
    toolTip = index >= 0 ? tr("Change label to a user-defined text") : tr("Change all labels to user-defined texts");
    QRadioButton *rdbCustom = new QRadioButton(text);
    rdbCustom->setToolTip(toolTip);

    toolTip = index >= 0 ? tr("Change label to a user-defined text") : tr("Change all labels to user-defined texts");
    ledCustom = new QLineEdit;
    ledCustom->setEnabled(false);
    ledCustom->setToolTip(toolTip);
    connect(rdbCustom, &QRadioButton::toggled, this, [=](bool checked){ ledCustom->setEnabled(checked); });

    text = type == QStringLiteral("horizontal") ? tr("# will be replaced with column index") : tr("# will be replaced with row index");
    QLabel *lblCustom = new QLabel(text);
    lblCustom->setEnabled(false);
    connect(rdbCustom, &QRadioButton::toggled, this, [=](bool checked){ lblCustom->setEnabled(checked); });

    grpHeaderLabel = new QButtonGroup(this);
    grpHeaderLabel->addButton(rdbBinary, (int) Preferences::HeaderLabel::Binary);
    grpHeaderLabel->addButton(rdbOctal, (int) Preferences::HeaderLabel::Octal);
    grpHeaderLabel->addButton(rdbDecimal, (int) Preferences::HeaderLabel::Decimal);
    grpHeaderLabel->addButton(rdbHexadecimal, (int) Preferences::HeaderLabel::Hexadecimal);
    grpHeaderLabel->addButton(rdbLetter, (int) Preferences::HeaderLabel::Letter);
    grpHeaderLabel->addButton(rdbCustom, (int) Preferences::HeaderLabel::Custom);
    connect(grpHeaderLabel, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &DocumentTableHeaderDialog::onSettingChanged);

    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addWidget(rdbBinary, 0, 0);
    groupLayout->addWidget(chkBinary, 0, 1);
    groupLayout->addWidget(rdbOctal, 1, 0);
    groupLayout->addWidget(chkOctal, 1, 1);
    groupLayout->addWidget(rdbDecimal, 2, 0);
    groupLayout->addWidget(chkDecimal, 2, 1);
    groupLayout->addWidget(rdbHexadecimal, 3, 0);
    groupLayout->addWidget(chkHexadecimal, 3, 1);
    groupLayout->addWidget(rdbLetter, 4, 0);
    groupLayout->addWidget(chkLetter, 4, 1);
    groupLayout->addWidget(rdbCustom, 5, 0);
    groupLayout->addWidget(ledCustom, 5, 1);
    groupLayout->addWidget(lblCustom, 6, 1);
    groupLayout->setRowStretch(7, 1);

    text = index >= 0 ? tr("Change label to a …") : tr("Change all labels to …");
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
Preferences::HeaderLabel DocumentTableHeaderDialog::headerLabelType() const
{
    return static_cast<Preferences::HeaderLabel>( grpHeaderLabel->checkedId() );
}


/**
 * Returns the parameter of the header label.
 */
QString DocumentTableHeaderDialog::headerLabelParameter() const
{
    Preferences::HeaderLabel type = headerLabelType();

    if (type == Preferences::HeaderLabel::Binary) {
        return chkBinary->isChecked() ? QStringLiteral("0b") : QString();
    }
    else if (type == Preferences::HeaderLabel::Octal) {
        return chkOctal->isChecked() ? QStringLiteral("0o") : QString();
    }
    else if (type == Preferences::HeaderLabel::Decimal) {
        return chkDecimal->isChecked() ? QStringLiteral("1") : QStringLiteral("0");
    }
    else if (type == Preferences::HeaderLabel::Hexadecimal) {
        return chkHexadecimal->isChecked() ? QStringLiteral("0x") : QString();
    }
    else if (type == Preferences::HeaderLabel::Letter) {
        return chkLetter->isChecked() ? QStringLiteral("upper") : QStringLiteral("lower");
    }
    else if (type == Preferences::HeaderLabel::Custom) {
        return ledCustom->text();
    }
    else {
        return QString();
    }
}
