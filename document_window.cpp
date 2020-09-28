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

#include "document_window.h"

#include <QHeaderView>
#include <QIcon>
#include <QMenu>


DocumentWindow::DocumentWindow(QWidget *parent) :
    QTableWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    // Creates a default document
    setColumnCount(m_settings.newDocumentColumns);
    setRowCount(m_settings.newDocumentRows);

    // Enable context menus
    QHeaderView *hHeaderView = horizontalHeader();
    hHeaderView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(hHeaderView, &QTableWidget::customContextMenuRequested, this, &DocumentWindow::contextMenuHorizontalHeader);

    QHeaderView *vHeaderView = verticalHeader();
    vHeaderView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(vHeaderView, &QTableWidget::customContextMenuRequested, this, &DocumentWindow::contextMenuVerticalHeader);
}


/**
 * Sets the user preferences.
 */
void DocumentWindow::setSettings(const Settings &settings)
{
    m_settings = settings;
}


/**
 * Creates a document.
 */
void DocumentWindow::createDocument()
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
void DocumentWindow::setHorizontalHeaderItems(int type)
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
void DocumentWindow::setVerticalHeaderItems(int type)
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
QString DocumentWindow::headerItemText(int number, int type)
{
    if (type == 0) {
        return numberToHexavigesimal(number);
    }
    else {
        return QStringLiteral("%1").arg(number + 1);
    }
}


/**
 * Returns a string equivalent of the number according to the base 2.
 */
QString DocumentWindow::numberToBinary(int number)
{
    return QStringLiteral("0b%1").arg(numberToString(number, 2));
}


/**
 * Returns a string equivalent of the number according to the base 8.
 */
QString DocumentWindow::numberToOctal(int number)
{
    return QStringLiteral("0o%1").arg(numberToString(number, 8));
}


/**
 * Returns a string equivalent of the number according to the base 16.
 */
QString DocumentWindow::numberToHexadecimal(int number)
{
    return QStringLiteral("0x%1").arg(numberToString(number, 16));
}


/**
 * Returns a string equivalent of the number according to the base 26.
 */
QString DocumentWindow::numberToHexavigesimal(int number)
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
QString DocumentWindow::numberToString(int number, int base)
{
    return QString::number(number, base).toUpper();
}


/**
 * Creates a context menu for the horizonzal header.
 */
void DocumentWindow::contextMenuHorizontalHeader(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);

    QAction *actionLabelLetter = new QAction(QStringLiteral("Letter"), this);
    actionLabelLetter->setStatusTip(QStringLiteral("Change label to letter"));
    actionLabelLetter->setToolTip(QStringLiteral("Change label to letter"));
    connect(actionLabelLetter, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), 0); });

    QAction *actionLabelNumber = new QAction(QStringLiteral("Number"), this);
    actionLabelNumber->setStatusTip(QStringLiteral("Change label to number"));
    actionLabelNumber->setToolTip(QStringLiteral("Change label to number"));
    connect(actionLabelNumber, &QAction::triggered, [=]() { onActionLabelHorizontalTriggered(index.column(), 1); });

    QAction *actionLabelLetters = new QAction(QStringLiteral("Letters"), this);
    actionLabelLetters->setStatusTip(QStringLiteral("Change all labels to letters"));
    actionLabelLetters->setToolTip(QStringLiteral("Change all labels to letters"));
    connect(actionLabelLetters, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(0); });

    QAction *actionLabelNumbers = new QAction(QStringLiteral("Numbers"), this);
    actionLabelNumbers->setStatusTip(QStringLiteral("Change all labels to numbers"));
    actionLabelNumbers->setToolTip(QStringLiteral("Change all labels to numbers"));
    connect(actionLabelNumbers, &QAction::triggered, [=]() { onActionLabelHorizontalAllTriggered(1); });

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
void DocumentWindow::contextMenuVerticalHeader(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);

    QAction *actionLabelLetter = new QAction(QStringLiteral("Letter"), this);
    actionLabelLetter->setStatusTip(QStringLiteral("Change label to letter"));
    actionLabelLetter->setToolTip(QStringLiteral("Change label to letter"));
    connect(actionLabelLetter, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), 0); });

    QAction *actionLabelNumber = new QAction(QStringLiteral("Number"), this);
    actionLabelNumber->setStatusTip(QStringLiteral("Change label to number"));
    actionLabelNumber->setToolTip(QStringLiteral("Change label to number"));
    connect(actionLabelNumber, &QAction::triggered, [=]() { onActionLabelVerticalTriggered(index.row(), 1); });

    QAction *actionLabelLetters = new QAction(QStringLiteral("Letters"), this);
    actionLabelLetters->setStatusTip(QStringLiteral("Change all labels to letters"));
    actionLabelLetters->setToolTip(QStringLiteral("Change all labels to letters"));
    connect(actionLabelLetters, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(0); });

    QAction *actionLabelNumbers = new QAction(QStringLiteral("Numbers"), this);
    actionLabelNumbers->setStatusTip(QStringLiteral("Change all labels to numbers"));
    actionLabelNumbers->setToolTip(QStringLiteral("Change all labels to numbers"));
    connect(actionLabelNumbers, &QAction::triggered, [=]() { onActionLabelVerticalAllTriggered(1); });

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
void DocumentWindow::onActionLabelHorizontalTriggered(int column, int type)
{
    updateHorizontalHeaderItem(column, type);
}


/**
 * Updates all horizontal header items.
 */
void DocumentWindow::onActionLabelHorizontalAllTriggered(int type)
{
    for (int column = 0; column < columnCount(); column++) {
        updateHorizontalHeaderItem(column, type);
    }
}


/**
 * Updates a horizontal header item.
 */
void DocumentWindow::updateHorizontalHeaderItem(int column, int type)
{
    QTableWidgetItem *item = horizontalHeaderItem(column);
    item->setText(headerItemText(column, type));
}


/**
 * Updates a specific vertical header item.
 */
void DocumentWindow::onActionLabelVerticalTriggered(int row, int type)
{
    updateVerticalHeaderItem(row, type);
}


/**
 * Updates all vertical header items.
 */
void DocumentWindow::onActionLabelVerticalAllTriggered(int type)
{
    for (int row = 0; row < rowCount(); row++) {
        updateVerticalHeaderItem(row, type);
    }
}


/**
 * Updates a vertical header item.
 */
void DocumentWindow::updateVerticalHeaderItem(int row, int type)
{
    QTableWidgetItem *item = verticalHeaderItem(row);
    item->setText(headerItemText(row, type));
}
