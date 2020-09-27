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
    for (int i = 0; i < columnCount(); i++) {

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);

        if (type == 0) {
            item->setText(numberToHexavigesimal(i));
        }
        else {
            item->setText(QStringLiteral("%1").arg(i + 1));
        }

        setHorizontalHeaderItem(i, item);
    }
}


/**
 * Sets the vertical header items.
 */
void DocumentWindow::setVerticalHeaderItems(int type)
{
    for (int i = 0; i < rowCount(); i++) {

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);

        if (type == 0) {
            item->setText(numberToHexavigesimal(i));
        }
        else {
            item->setText(QStringLiteral("%1").arg(i + 1));
        }

        setVerticalHeaderItem(i, item);
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
    QMenu *contextMenu = new QMenu(this);
    contextMenu->exec(mapToGlobal(pos));
}


/**
 * Creates a context menu for the vertical header.
 */
void DocumentWindow::contextMenuVerticalHeader(const QPoint &pos)
{
    QMenu *contextMenu = new QMenu(this);
    contextMenu->exec(mapToGlobal(pos));
}
