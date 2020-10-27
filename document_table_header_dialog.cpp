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
#include <QVBoxLayout>


DocumentTableHeaderDialog::DocumentTableHeaderDialog(const int number, QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Button box
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonOk = buttonBox->button(QDialogButtonBox::Ok);
    buttonOk->setEnabled(false);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DocumentTableHeaderDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DocumentTableHeaderDialog::reject);

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout;
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
