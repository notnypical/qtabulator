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
    setColumnCount(m_settings.defaultCellColumns);
    setRowCount(m_settings.defaultCellRows);

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
    setColumnCount(m_settings.defaultCellColumns);
    setRowCount(m_settings.defaultCellRows);

    // Set header items
    setHorizontalHeaderItems(m_settings.defaultHeaderLabelHorizontal);
    setVerticalHeaderItems(m_settings.defaultHeaderLabelVertical);
}


/**
 * Sets the horizontal header items.
 */
void DocumentTable::setHorizontalHeaderItems(Settings::HeaderLabel type)
{
    for (int column = 0; column < columnCount(); column++) {

        int number = column;

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

        int number = row;

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(headerItemText(number, type));

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
    return QStringLiteral("%1").arg(number + 1);
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

    // Label
    QAction *actionLabelLetter = new QAction(QStringLiteral("Letter"), this);
    actionLabelLetter->setStatusTip(QStringLiteral("Change label to a capital letter"));
    actionLabelLetter->setToolTip(QStringLiteral("Change label to a capital letter"));
    connect(actionLabelLetter, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Letter); });

    QAction *actionLabelNumber = new QAction(QStringLiteral("Number"), this);
    actionLabelNumber->setStatusTip(QStringLiteral("Change label to a decimal number"));
    actionLabelNumber->setToolTip(QStringLiteral("Change label to a decimal number"));
    connect(actionLabelNumber, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Decimal); });

    QAction *actionLabelCustom = new QAction(QStringLiteral("Custom…"), this);
    actionLabelCustom->setStatusTip(QStringLiteral("Change label to a user-defined text"));
    actionLabelCustom->setToolTip(QStringLiteral("Change label to a user-defined text"));
    connect(actionLabelCustom, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Custom); });

    QAction *actionLabelLetters = new QAction(QStringLiteral("Letters"), this);
    actionLabelLetters->setStatusTip(QStringLiteral("Change all labels to capital letters"));
    actionLabelLetters->setToolTip(QStringLiteral("Change all labels to capital letters"));
    connect(actionLabelLetters, &QAction::triggered, [=]() { onActionLabelAllHorizontalTriggered(Settings::HeaderLabel::Letter); });

    QAction *actionLabelNumbers = new QAction(QStringLiteral("Numbers"), this);
    actionLabelNumbers->setStatusTip(QStringLiteral("Change all labels to decimal numbers"));
    actionLabelNumbers->setToolTip(QStringLiteral("Change all labels to decimal numbers"));
    connect(actionLabelNumbers, &QAction::triggered, [=]() { onActionLabelAllHorizontalTriggered(Settings::HeaderLabel::Decimal); });

    QAction *actionLabelCustoms = new QAction(QStringLiteral("Custom…"), this);
    actionLabelCustoms->setStatusTip(QStringLiteral("Change all labels to user-defined texts"));
    actionLabelCustoms->setToolTip(QStringLiteral("Change all labels to user-defined texts"));
    connect(actionLabelCustoms, &QAction::triggered, [=]() { onActionLabelAllHorizontalTriggered(Settings::HeaderLabel::Custom); });

    // Context menu
    QMenu *menuLabel = new QMenu(QStringLiteral("Label"), this);
    menuLabel->setIcon(QIcon::fromTheme(QStringLiteral("tag"), QIcon(QStringLiteral(":/icons/actions/16/tag.svg"))));
    menuLabel->setStatusTip(QStringLiteral("Change label"));
    menuLabel->setToolTip(QStringLiteral("Change label"));
    menuLabel->addAction(actionLabelLetter);
    menuLabel->addAction(actionLabelNumber);
    menuLabel->addAction(actionLabelCustom);
    menuLabel->addSeparator();
    menuLabel->addAction(actionLabelLetters);
    menuLabel->addAction(actionLabelNumbers);
    menuLabel->addAction(actionLabelCustoms);

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addMenu(menuLabel);
    contextMenu->exec(mapToGlobal(pos));
}


/**
 * Updates a specific horizontal header item.
 */
void DocumentTable::onActionLabelHorizontalTriggered(int column, Settings::HeaderLabel type)
{
    if (type == Settings::HeaderLabel::Custom) {

        return;
    }

    updateHorizontalHeaderItem(column, type);
}


/**
 * Updates all horizontal header items.
 */
void DocumentTable::onActionLabelAllHorizontalTriggered(Settings::HeaderLabel type)
{
    if (type == Settings::HeaderLabel::Custom) {

        return;
    }

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

    QTableWidgetItem *item = horizontalHeaderItem(column);
    item->setText(headerItemText(number, type));
}


/**
 * Creates a context menu for the vertical header.
 */
void DocumentTable::contextMenuVerticalHeader(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);

    // Label
    QAction *actionLabelLetter = new QAction(QStringLiteral("Letter"), this);
    actionLabelLetter->setStatusTip(QStringLiteral("Change label to a capital letter"));
    actionLabelLetter->setToolTip(QStringLiteral("Change label to a capital letter"));
    connect(actionLabelLetter, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Letter); });

    QAction *actionLabelNumber = new QAction(QStringLiteral("Number"), this);
    actionLabelNumber->setStatusTip(QStringLiteral("Change label to a decimal number"));
    actionLabelNumber->setToolTip(QStringLiteral("Change label to a decimal number"));
    connect(actionLabelNumber, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Decimal); });

    QAction *actionLabelCustom = new QAction(QStringLiteral("Custom…"), this);
    actionLabelCustom->setStatusTip(QStringLiteral("Change label to a user-defined text"));
    actionLabelCustom->setToolTip(QStringLiteral("Change label to a user-defined text"));
    connect(actionLabelCustom, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Custom); });

    QAction *actionLabelLetters = new QAction(QStringLiteral("Letters"), this);
    actionLabelLetters->setStatusTip(QStringLiteral("Change all labels to capital letters"));
    actionLabelLetters->setToolTip(QStringLiteral("Change all labels to capital letters"));
    connect(actionLabelLetters, &QAction::triggered, [=]() { onActionLabelAllVerticalTriggered(Settings::HeaderLabel::Letter); });

    QAction *actionLabelNumbers = new QAction(QStringLiteral("Numbers"), this);
    actionLabelNumbers->setStatusTip(QStringLiteral("Change all labels to decimal numbers"));
    actionLabelNumbers->setToolTip(QStringLiteral("Change all labels to decimal numbers"));
    connect(actionLabelNumbers, &QAction::triggered, [=]() { onActionLabelAllVerticalTriggered(Settings::HeaderLabel::Decimal); });

    QAction *actionLabelCustoms = new QAction(QStringLiteral("Custom…"), this);
    actionLabelCustoms->setStatusTip(QStringLiteral("Change all labels to user-defined texts"));
    actionLabelCustoms->setToolTip(QStringLiteral("Change all labels to user-defined texts"));
    connect(actionLabelCustoms, &QAction::triggered, [=]() { onActionLabelAllVerticalTriggered(Settings::HeaderLabel::Custom); });

    // Context menu
    QMenu *menuLabel = new QMenu(QStringLiteral("Label"), this);
    menuLabel->setIcon(QIcon::fromTheme(QStringLiteral("tag"), QIcon(QStringLiteral(":/icons/actions/16/tag.svg"))));
    menuLabel->setStatusTip(QStringLiteral("Change label"));
    menuLabel->setToolTip(QStringLiteral("Change label"));
    menuLabel->addAction(actionLabelLetter);
    menuLabel->addAction(actionLabelNumber);
    menuLabel->addAction(actionLabelCustom);
    menuLabel->addSeparator();
    menuLabel->addAction(actionLabelLetters);
    menuLabel->addAction(actionLabelNumbers);
    menuLabel->addAction(actionLabelCustoms);

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addMenu(menuLabel);
    contextMenu->exec(mapToGlobal(pos));
}


/**
 * Updates a specific vertical header item.
 */
void DocumentTable::onActionLabelVerticalTriggered(int row, Settings::HeaderLabel type)
{
    if (type == Settings::HeaderLabel::Custom) {

        return;
    }

    updateVerticalHeaderItem(row, type);
}


/**
 * Updates all vertical header items.
 */
void DocumentTable::onActionLabelAllVerticalTriggered(Settings::HeaderLabel type)
{
    if (type == Settings::HeaderLabel::Custom) {

        return;
    }

    for (int row = 0; row < rowCount(); row++) {
        updateVerticalHeaderItem(row, type);
    }
}


/**
 * Updates a vertical header item.
 */
void DocumentTable::updateVerticalHeaderItem(int row, Settings::HeaderLabel type)
{
    int number = row;

    QTableWidgetItem *item = verticalHeaderItem(row);
    item->setText(headerItemText(number, type));
}
