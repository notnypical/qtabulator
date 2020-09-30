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

#include "document_table.h"

#include <QHeaderView>
#include <QIcon>
#include <QInputDialog>
#include <QMenu>


DocumentTable::DocumentTable(QWidget *parent) :
    QTableWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    // Creates a default document
    setColumnCount(m_settings.newDocumentColumns);
    setRowCount(m_settings.newDocumentRows);

    // Enable context menus
    QHeaderView *hHeaderView = horizontalHeader();
    hHeaderView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(hHeaderView, &QTableWidget::customContextMenuRequested, this, &DocumentTable::contextMenuHorizontalHeader);

    QHeaderView *vHeaderView = verticalHeader();
    vHeaderView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(vHeaderView, &QTableWidget::customContextMenuRequested, this, &DocumentTable::contextMenuVerticalHeader);
}


/**
 * Sets the user preferences.
 */
void DocumentTable::setSettings(const Settings &settings)
{
    m_settings = settings;
}


/**
 * Creates a document.
 */
void DocumentTable::createDocument()
{
    // Creates a new document
    setColumnCount(m_settings.newDocumentColumns);
    setRowCount(m_settings.newDocumentRows);

    // Set header items
    setHorizontalHeaderItems(m_settings.horizontalHeaderLabels);
    setVerticalHeaderItems(m_settings.verticalHeaderLabels);
}


/**
 * Sets the horizontal header items.
 */
void DocumentTable::setHorizontalHeaderItems(Settings::HeaderLabel type)
{
    for (int column = 0; column < columnCount(); column++) {

        int number = column;
        if (type == Settings::HeaderLabel::Decimal) {
            number += m_settings.horizontalHeaderDecimalStart;
        }

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(headerItemText(number, type));

        setHorizontalHeaderItem(column, item);
    }
}


/**
 * Sets the vertical header items.
 */
void DocumentTable::setVerticalHeaderItems(Settings::HeaderLabel type)
{
    for (int row = 0; row < rowCount(); row++) {

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(headerItemText(row, type));

        setVerticalHeaderItem(row, item);
    }
}


/**
 * Returns the header item text.
 */
QString DocumentTable::headerItemText(int number, Settings::HeaderLabel type)
{
    if (type == Settings::HeaderLabel::Binary) {
        return numberToBinary(number);
    }
    else if (type == Settings::HeaderLabel::Octal) {
        return numberToOctal(number);
    }
    else if (type == Settings::HeaderLabel::Decimal) {
        return numberToDecimal(number);
    }
    else if (type == Settings::HeaderLabel::Hexadecimal) {
        return numberToHexadecimal(number);
    }
    else if (type == Settings::HeaderLabel::Letter) {
        return numberToLetter(number);
    }
    else {
        return QString();
    }
}


/**
 * Returns a string equivalent of the number according to the base 2.
 */
QString DocumentTable::numberToBinary(int number)
{
    return QStringLiteral("0b%1").arg(numberToString(number, 2));
}


/**
 * Returns a string equivalent of the number according to the base 8.
 */
QString DocumentTable::numberToOctal(int number)
{
    return QStringLiteral("0o%1").arg(numberToString(number, 8));
}


/**
 * Returns a string equivalent of the number according to the base 10.
 */
QString DocumentTable::numberToDecimal(int number)
{
    return QStringLiteral("%1").arg(number);
}


/**
 * Returns a string equivalent of the number according to the base 16.
 */
QString DocumentTable::numberToHexadecimal(int number)
{
    return QStringLiteral("0x%1").arg(numberToString(number, 16));
}


/**
 * Returns a string equivalent of the number according to the base 26.
 */
QString DocumentTable::numberToLetter(int number)
{
    QString chars = {};
    number++;

    while (number > 0) {
        number -= 1;
        chars.prepend(numberToString((number % 26) + 10, 36));
        number /= 26;
    };

    return chars;
}


/**
 * Returns a string equivalent of the number according to the specified base.
 */
QString DocumentTable::numberToString(int number, int base)
{
    return QString::number(number, base).toUpper();
}


/**
 * Creates a context menu for the horizonzal header.
 */
void DocumentTable::contextMenuHorizontalHeader(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);

    // Specific label
    QAction *actionLabelBinary = new QAction(QStringLiteral("Binary Number"), this);
    actionLabelBinary->setStatusTip(QStringLiteral("Change label to binary number"));
    actionLabelBinary->setToolTip(QStringLiteral("Change label to binary number"));
    connect(actionLabelBinary, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Binary); });

    QAction *actionLabelOctal = new QAction(QStringLiteral("Octal Number"), this);
    actionLabelOctal->setStatusTip(QStringLiteral("Change label to octal number"));
    actionLabelOctal->setToolTip(QStringLiteral("Change label to octal number"));
    connect(actionLabelOctal, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Octal); });

    QAction *actionLabelDecimal = new QAction(QStringLiteral("Decimal Number"), this);
    actionLabelDecimal->setStatusTip(QStringLiteral("Change label to decimal number"));
    actionLabelDecimal->setToolTip(QStringLiteral("Change label to decimal number"));
    connect(actionLabelDecimal, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Decimal); });

    QAction *actionLabelHexadecimal = new QAction(QStringLiteral("Hexadecimal Number"), this);
    actionLabelHexadecimal->setStatusTip(QStringLiteral("Change label to hexadecimal number"));
    actionLabelHexadecimal->setToolTip(QStringLiteral("Change label to hexadecimal number"));
    connect(actionLabelHexadecimal, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Hexadecimal); });

    QAction *actionLabelLetter = new QAction(QStringLiteral("Letter"), this);
    actionLabelLetter->setStatusTip(QStringLiteral("Change label to letter"));
    actionLabelLetter->setToolTip(QStringLiteral("Change label to letter"));
    connect(actionLabelLetter, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Letter); });

    QAction *actionLabelCustom = new QAction(QStringLiteral("Custom…"), this);
    actionLabelCustom->setStatusTip(QStringLiteral("Customize label"));
    actionLabelCustom->setToolTip(QStringLiteral("Customize label"));
    connect(actionLabelCustom, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Custom); });

    // All labels
    QAction *actionLabelBinaries = new QAction(QStringLiteral("Binary Numbers"), this);
    actionLabelBinaries->setStatusTip(QStringLiteral("Change all labels to binary numbers"));
    actionLabelBinaries->setToolTip(QStringLiteral("Change all labels to binary numbers"));
    connect(actionLabelBinaries, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(Settings::HeaderLabel::Binary); });

    QAction *actionLabelOctals = new QAction(QStringLiteral("Octal Numbers"), this);
    actionLabelOctals->setStatusTip(QStringLiteral("Change all labels to octal numbers"));
    actionLabelOctals->setToolTip(QStringLiteral("Change all labels to octal numbers"));
    connect(actionLabelOctals, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(Settings::HeaderLabel::Octal); });

    QAction *actionLabelDecimals = new QAction(QStringLiteral("Decimal Numbers"), this);
    actionLabelDecimals->setStatusTip(QStringLiteral("Change all labels to decimal numbers"));
    actionLabelDecimals->setToolTip(QStringLiteral("Change all labels to decimal numbers"));
    connect(actionLabelDecimals, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(Settings::HeaderLabel::Decimal); });

    QAction *actionLabelHexadecimals = new QAction(QStringLiteral("Hexadecimal Numbers"), this);
    actionLabelHexadecimals->setStatusTip(QStringLiteral("Change all labels to hexadecimal numbers"));
    actionLabelHexadecimals->setToolTip(QStringLiteral("Change all labels to hexadecimal numbers"));
    connect(actionLabelHexadecimals, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(Settings::HeaderLabel::Hexadecimal); });

    QAction *actionLabelLetters = new QAction(QStringLiteral("Letters"), this);
    actionLabelLetters->setStatusTip(QStringLiteral("Change all labels to letters"));
    actionLabelLetters->setToolTip(QStringLiteral("Change all labels to letters"));
    connect(actionLabelLetters, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(Settings::HeaderLabel::Letter); });

    QMenu *menuLabel = new QMenu(QStringLiteral("Label"), this);
    menuLabel->setIcon(QIcon::fromTheme(QStringLiteral("tag"), QIcon(QStringLiteral(":/icons/actions/16/tag.svg"))));
    menuLabel->setStatusTip(QStringLiteral("Change label"));
    menuLabel->setToolTip(QStringLiteral("Change label"));
    menuLabel->addAction(actionLabelBinary);
    menuLabel->addAction(actionLabelOctal);
    menuLabel->addAction(actionLabelDecimal);
    menuLabel->addAction(actionLabelHexadecimal);
    menuLabel->addAction(actionLabelLetter);
    menuLabel->addAction(actionLabelCustom);
    menuLabel->addSeparator();
    menuLabel->addAction(actionLabelBinaries);
    menuLabel->addAction(actionLabelOctals);
    menuLabel->addAction(actionLabelDecimals);
    menuLabel->addAction(actionLabelHexadecimals);
    menuLabel->addAction(actionLabelLetters);

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addMenu(menuLabel);
    contextMenu->exec(mapToGlobal(pos));
}


/**
 * Creates a context menu for the vertical header.
 */
void DocumentTable::contextMenuVerticalHeader(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);

    // Specific label
    QAction *actionLabelBinary = new QAction(QStringLiteral("Binary Number"), this);
    actionLabelBinary->setStatusTip(QStringLiteral("Change label to binary number"));
    actionLabelBinary->setToolTip(QStringLiteral("Change label to binary number"));
    connect(actionLabelBinary, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Binary); });

    QAction *actionLabelOctal = new QAction(QStringLiteral("Octal Number"), this);
    actionLabelOctal->setStatusTip(QStringLiteral("Change label to octal number"));
    actionLabelOctal->setToolTip(QStringLiteral("Change label to octal number"));
    connect(actionLabelOctal, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Octal); });

    QAction *actionLabelDecimal = new QAction(QStringLiteral("Decimal Number"), this);
    actionLabelDecimal->setStatusTip(QStringLiteral("Change label to decimal number"));
    actionLabelDecimal->setToolTip(QStringLiteral("Change label to decimal number"));
    connect(actionLabelDecimal, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Decimal); });

    QAction *actionLabelHexadecimal = new QAction(QStringLiteral("Hexadecimal Number"), this);
    actionLabelHexadecimal->setStatusTip(QStringLiteral("Change label to hexadecimal number"));
    actionLabelHexadecimal->setToolTip(QStringLiteral("Change label to hexadecimal number"));
    connect(actionLabelHexadecimal, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Hexadecimal); });

    QAction *actionLabelLetter = new QAction(QStringLiteral("Letter"), this);
    actionLabelLetter->setStatusTip(QStringLiteral("Change label to letter"));
    actionLabelLetter->setToolTip(QStringLiteral("Change label to letter"));
    connect(actionLabelLetter, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Letter); });

    QAction *actionLabelCustom = new QAction(QStringLiteral("Custom…"), this);
    actionLabelCustom->setStatusTip(QStringLiteral("Customize label"));
    actionLabelCustom->setToolTip(QStringLiteral("Customize label"));
    connect(actionLabelCustom, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Custom); });

    // All labels
    QAction *actionLabelBinaries = new QAction(QStringLiteral("Binary Numbers"), this);
    actionLabelBinaries->setStatusTip(QStringLiteral("Change all labels to binary numbers"));
    actionLabelBinaries->setToolTip(QStringLiteral("Change all labels to binary numbers"));
    connect(actionLabelBinaries, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(Settings::HeaderLabel::Binary); });

    QAction *actionLabelOctals = new QAction(QStringLiteral("Octal Numbers"), this);
    actionLabelOctals->setStatusTip(QStringLiteral("Change all labels to octal numbers"));
    actionLabelOctals->setToolTip(QStringLiteral("Change all labels to octal numbers"));
    connect(actionLabelOctals, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(Settings::HeaderLabel::Octal); });

    QAction *actionLabelDecimals = new QAction(QStringLiteral("Decimal Numbers"), this);
    actionLabelDecimals->setStatusTip(QStringLiteral("Change all labels to decimal numbers"));
    actionLabelDecimals->setToolTip(QStringLiteral("Change all labels to decimal numbers"));
    connect(actionLabelDecimals, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(Settings::HeaderLabel::Decimal); });

    QAction *actionLabelHexadecimals = new QAction(QStringLiteral("Hexadecimal Numbers"), this);
    actionLabelHexadecimals->setStatusTip(QStringLiteral("Change all labels to hexadecimal numbers"));
    actionLabelHexadecimals->setToolTip(QStringLiteral("Change all labels to hexadecimal numbers"));
    connect(actionLabelHexadecimals, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(Settings::HeaderLabel::Hexadecimal); });

    QAction *actionLabelLetters = new QAction(QStringLiteral("Letters"), this);
    actionLabelLetters->setStatusTip(QStringLiteral("Change all labels to letters"));
    actionLabelLetters->setToolTip(QStringLiteral("Change all labels to letters"));
    connect(actionLabelLetters, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(Settings::HeaderLabel::Letter); });

    QMenu *menuLabel = new QMenu(QStringLiteral("Label"), this);
    menuLabel->setIcon(QIcon::fromTheme(QStringLiteral("tag"), QIcon(QStringLiteral(":/icons/actions/16/tag.svg"))));
    menuLabel->setStatusTip(QStringLiteral("Change label"));
    menuLabel->setToolTip(QStringLiteral("Change label"));
    menuLabel->addAction(actionLabelBinary);
    menuLabel->addAction(actionLabelOctal);
    menuLabel->addAction(actionLabelDecimal);
    menuLabel->addAction(actionLabelHexadecimal);
    menuLabel->addAction(actionLabelLetter);
    menuLabel->addAction(actionLabelCustom);
    menuLabel->addSeparator();
    menuLabel->addAction(actionLabelBinaries);
    menuLabel->addAction(actionLabelOctals);
    menuLabel->addAction(actionLabelDecimals);
    menuLabel->addAction(actionLabelHexadecimals);
    menuLabel->addAction(actionLabelLetters);

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addMenu(menuLabel);
    contextMenu->exec(mapToGlobal(pos));
}


/**
 * Updates a specific horizontal header item.
 */
void DocumentTable::onActionLabelHorizontalTriggered(int column, Settings::HeaderLabel type)
{
    updateHorizontalHeaderItem(column, type);
}


/**
 * Updates all horizontal header items.
 */
void DocumentTable::onActionLabelHorizontalAllTriggered(Settings::HeaderLabel type)
{
    for (int column = 0; column < columnCount(); column++) {
        updateHorizontalHeaderItem(column, type);
    }
}


/**
 * Updates a horizontal header item.
 */
void DocumentTable::updateHorizontalHeaderItem(int column, Settings::HeaderLabel type)
{
    int number = column;
    if (type == Settings::HeaderLabel::Decimal) {
        number += m_settings.horizontalHeaderDecimalStart;
    }

    QTableWidgetItem *item = horizontalHeaderItem(column);
    if (type == Settings::HeaderLabel::Custom) {

        bool ok;
        QString text = QInputDialog::getText(this, QStringLiteral("Horizontal Header Item"),
                                             QStringLiteral("Label:"), QLineEdit::Normal, item->text(),
                                             &ok, windowFlags() & ~Qt::WindowContextHelpButtonHint);

        if (ok && !text.isEmpty()) {
            item->setText(text);
        }
    }
    else {
        item->setText(headerItemText(number, type));
    }
}


/**
 * Updates a specific vertical header item.
 */
void DocumentTable::onActionLabelVerticalTriggered(int row, Settings::HeaderLabel type)
{
    updateVerticalHeaderItem(row, type);
}


/**
 * Updates all vertical header items.
 */
void DocumentTable::onActionLabelVerticalAllTriggered(Settings::HeaderLabel type)
{
    for (int row = 0; row < rowCount(); row++) {
        updateVerticalHeaderItem(row, type);
    }
}


/**
 * Updates a vertical header item.
 */
void DocumentTable::updateVerticalHeaderItem(int row, Settings::HeaderLabel type)
{
    QTableWidgetItem *item = verticalHeaderItem(row);

    if (type == Settings::HeaderLabel::Custom) {

        bool ok;
        QString text = QInputDialog::getText(this, QStringLiteral("Vertical Header Item"),
                                             QStringLiteral("Label:"), QLineEdit::Normal, item->text(),
                                             &ok, windowFlags() & ~Qt::WindowContextHelpButtonHint);

        if (ok && !text.isEmpty()) {
            item->setText(text);
        }
    }
    else {
        item->setText(headerItemText(row, type));
    }
}
