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

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(headerItemText(column, type));

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
    if (type == Settings::HeaderLabel::Letter) {
        return numberToHexavigesimal(number);
    }
    else {
        return QStringLiteral("%1").arg(number + 1);
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
 * Returns a string equivalent of the number according to the base 16.
 */
QString DocumentTable::numberToHexadecimal(int number)
{
    return QStringLiteral("0x%1").arg(numberToString(number, 16));
}


/**
 * Returns a string equivalent of the number according to the base 26.
 */
QString DocumentTable::numberToHexavigesimal(int number)
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

    QAction *actionLabelLetter = new QAction(QStringLiteral("Letter"), this);
    actionLabelLetter->setStatusTip(QStringLiteral("Change label to letter"));
    actionLabelLetter->setToolTip(QStringLiteral("Change label to letter"));
    connect(actionLabelLetter, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Letter); });

    QAction *actionLabelNumber = new QAction(QStringLiteral("Number"), this);
    actionLabelNumber->setStatusTip(QStringLiteral("Change label to number"));
    actionLabelNumber->setToolTip(QStringLiteral("Change label to number"));
    connect(actionLabelNumber, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), Settings::HeaderLabel::Decimal); });

    QAction *actionLabelLetters = new QAction(QStringLiteral("Letters"), this);
    actionLabelLetters->setStatusTip(QStringLiteral("Change all labels to letters"));
    actionLabelLetters->setToolTip(QStringLiteral("Change all labels to letters"));
    connect(actionLabelLetters, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(Settings::HeaderLabel::Letter); });

    QAction *actionLabelNumbers = new QAction(QStringLiteral("Numbers"), this);
    actionLabelNumbers->setStatusTip(QStringLiteral("Change all labels to numbers"));
    actionLabelNumbers->setToolTip(QStringLiteral("Change all labels to numbers"));
    connect(actionLabelNumbers, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(Settings::HeaderLabel::Decimal); });

    QMenu *menuLabel = new QMenu(QStringLiteral("Label"), this);
    menuLabel->setIcon(QIcon::fromTheme(QStringLiteral("tag"), QIcon(QStringLiteral(":/icons/actions/16/tag.svg"))));
    menuLabel->setStatusTip(QStringLiteral("Change label"));
    menuLabel->setToolTip(QStringLiteral("Change label"));
    menuLabel->addAction(actionLabelLetter);
    menuLabel->addAction(actionLabelNumber);
    menuLabel->addSeparator();
    menuLabel->addAction(actionLabelLetters);
    menuLabel->addAction(actionLabelNumbers);

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

    QAction *actionLabelLetter = new QAction(QStringLiteral("Letter"), this);
    actionLabelLetter->setStatusTip(QStringLiteral("Change label to letter"));
    actionLabelLetter->setToolTip(QStringLiteral("Change label to letter"));
    connect(actionLabelLetter, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Letter); });

    QAction *actionLabelNumber = new QAction(QStringLiteral("Number"), this);
    actionLabelNumber->setStatusTip(QStringLiteral("Change label to number"));
    actionLabelNumber->setToolTip(QStringLiteral("Change label to number"));
    connect(actionLabelNumber, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), Settings::HeaderLabel::Decimal); });

    QAction *actionLabelLetters = new QAction(QStringLiteral("Letters"), this);
    actionLabelLetters->setStatusTip(QStringLiteral("Change all labels to letters"));
    actionLabelLetters->setToolTip(QStringLiteral("Change all labels to letters"));
    connect(actionLabelLetters, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(Settings::HeaderLabel::Letter); });

    QAction *actionLabelNumbers = new QAction(QStringLiteral("Numbers"), this);
    actionLabelNumbers->setStatusTip(QStringLiteral("Change all labels to numbers"));
    actionLabelNumbers->setToolTip(QStringLiteral("Change all labels to numbers"));
    connect(actionLabelNumbers, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(Settings::HeaderLabel::Decimal); });

    QMenu *menuLabel = new QMenu(QStringLiteral("Label"), this);
    menuLabel->setIcon(QIcon::fromTheme(QStringLiteral("tag"), QIcon(QStringLiteral(":/icons/actions/16/tag.svg"))));
    menuLabel->setStatusTip(QStringLiteral("Change label"));
    menuLabel->setToolTip(QStringLiteral("Change label"));
    menuLabel->addAction(actionLabelLetter);
    menuLabel->addAction(actionLabelNumber);
    menuLabel->addSeparator();
    menuLabel->addAction(actionLabelLetters);
    menuLabel->addAction(actionLabelNumbers);

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
    QTableWidgetItem *item = horizontalHeaderItem(column);
    item->setText(headerItemText(column, type));
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
    item->setText(headerItemText(row, type));
}