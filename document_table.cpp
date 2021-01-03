/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
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
#include "document_table_header_dialog.h"

#include <QFileInfo>
#include <QHeaderView>
#include <QIcon>
#include <QMenu>


DocumentTable::DocumentTable(QWidget *parent)
    : QTableWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    m_file = "";
    isUntitled = true;

    // Creates a default document
    setColumnCount(m_settings.defaultCellCountColumn());
    setRowCount(m_settings.defaultCellCountRow());

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
 * Creates a new document.
 */
void DocumentTable::newDocument()
{
    static int sequenceNumber = 0;
    sequenceNumber++;

    m_file = QStringLiteral("Untitled");
    if (sequenceNumber > 1)
        m_file += QStringLiteral(" (%1)").arg(sequenceNumber);
    isUntitled = true;

    setColumnCount(m_settings.defaultCellCountColumn());
    setRowCount(m_settings.defaultCellCountRow());

    // Set header items
    setHorizontalHeaderItems(m_settings.defaultHeaderLabelHorizontal());
    setVerticalHeaderItems(m_settings.defaultHeaderLabelVertical());

    setWindowTitle(fileName());
}


/**
 * Loads an existing document.
 */
bool DocumentTable::loadDocument(const QString &file)
{
    m_file = file;
    isUntitled = false;

    // Set header items
    setHorizontalHeaderItems(m_settings.defaultHeaderLabelHorizontal());
    setVerticalHeaderItems(m_settings.defaultHeaderLabelVertical());

    setWindowTitle(fileName());

    return true;
}


/**
 * Returns the file.
 */
QString DocumentTable::file() const
{
    return m_file;
}


/**
 * Returns the absolute path including the file name.
 */
QString DocumentTable::filePath() const
{
    return QFileInfo(m_file).absoluteFilePath();
}


/**
 * Returns the file name.
 */
QString DocumentTable::fileName() const
{
    return QFileInfo(m_file).fileName();
}


/**
 * Sets the horizontal header items.
 */
void DocumentTable::setHorizontalHeaderItems(Settings::HeaderLabel type)
{
    QString parameter = headerItemDefaultParameter(type);

    for (int column = 0; column < columnCount(); column++) {

        int number = column;

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(headerItemText(number, type, parameter));

        setHorizontalHeaderItem(column, item);
    }
}


/**
 * Sets the vertical header items.
 */
void DocumentTable::setVerticalHeaderItems(Settings::HeaderLabel type)
{
    QString parameter = headerItemDefaultParameter(type);

    for (int row = 0; row < rowCount(); row++) {

        int number = row;

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(headerItemText(number, type, parameter));

        setVerticalHeaderItem(row, item);
    }
}


/**
 * Returns the header item text.
 */
QString DocumentTable::headerItemText(int number, Settings::HeaderLabel type, QString parameter)
{
    if (type == Settings::HeaderLabel::Custom) {
        return numberToCustom(number, parameter);
    }
    else if (type == Settings::HeaderLabel::Binary) {
        return numberToBinary(number, parameter);
    }
    else if (type == Settings::HeaderLabel::Octal) {
        return numberToOctal(number, parameter);
    }
    else if (type == Settings::HeaderLabel::Decimal) {
        return numberToDecimal(number, parameter);
    }
    else if (type == Settings::HeaderLabel::Hexadecimal) {
        return numberToHexadecimal(number, parameter);
    }
    else if (type == Settings::HeaderLabel::Letter) {
        return numberToLetter(number, parameter);
    }
    else {
        return QString();
    }
}


/**
 * Returns a default parameter that matches the type of the header label.
 */
QString DocumentTable::headerItemDefaultParameter(Settings::HeaderLabel type)
{
    if (type == Settings::HeaderLabel::Binary) {
        return QStringLiteral("0b");
    }
    else if (type == Settings::HeaderLabel::Octal) {
        return QStringLiteral("0o");
    }
    else if (type == Settings::HeaderLabel::Decimal) {
        return QStringLiteral("1");
    }
    else if (type == Settings::HeaderLabel::Hexadecimal) {
        return QStringLiteral("0x");
    }
    else if (type == Settings::HeaderLabel::Letter) {
        return QStringLiteral("upper");
    }
    else {
        return QString();
    }
}


/**
 * Returns a string equivalent of the user-defined text.
 */
QString DocumentTable::numberToCustom(int number, QString parameter)
{
    return parameter.replace(QStringLiteral("#"), QStringLiteral("%1").arg(number + 1));
}


/**
 * Returns a string equivalent of the number according to the base 2.
 */
QString DocumentTable::numberToBinary(int number, QString parameter)
{
    return QStringLiteral("%2%1").arg(numberToString(number, 2), parameter);
}


/**
 * Returns a string equivalent of the number according to the base 8.
 */
QString DocumentTable::numberToOctal(int number, QString parameter)
{
    return QStringLiteral("%2%1").arg(numberToString(number, 8), parameter);
}


/**
 * Returns a string equivalent of the number according to the base 10.
 */
QString DocumentTable::numberToDecimal(int number, QString parameter)
{
    return QStringLiteral("%1").arg(number + parameter.toInt());
}


/**
 * Returns a string equivalent of the number according to the base 16.
 */
QString DocumentTable::numberToHexadecimal(int number, QString parameter)
{
    return QStringLiteral("%2%1").arg(numberToString(number, 16), parameter);
}


/**
 * Returns a string equivalent of the number according to the base 26.
 */
QString DocumentTable::numberToLetter(int number, QString parameter)
{
    QString chars = {};
    number++;

    while (number > 0) {
        number -= 1;
        chars.prepend(numberToString((number % 26) + 10, 36));
        number /= 26;
    };

    return parameter == QStringLiteral("upper") ? chars.toUpper() : chars.toLower();
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
    QString parameter = headerItemDefaultParameter(type);

    if (type == Settings::HeaderLabel::Custom) {

        DocumentTableHeaderDialog *documentTableHeaderDialog = new DocumentTableHeaderDialog(QStringLiteral("horizontal"), column, this);
        documentTableHeaderDialog->setWindowTitle(QStringLiteral("Horizontal Header Item"));

        if (documentTableHeaderDialog->exec() == QDialog::Accepted) {
            type = documentTableHeaderDialog->headerLabelType();
            parameter = documentTableHeaderDialog->headerLabelParameter();
        }
        else {
            return;
        }
    }

    updateHorizontalHeaderItem(column, type, parameter);
}


/**
 * Updates all horizontal header items.
 */
void DocumentTable::onActionLabelAllHorizontalTriggered(Settings::HeaderLabel type)
{
    QString parameter = headerItemDefaultParameter(type);

    if (type == Settings::HeaderLabel::Custom) {

        DocumentTableHeaderDialog *documentTableHeaderDialog = new DocumentTableHeaderDialog(QStringLiteral("horizontal"), -1, this);
        documentTableHeaderDialog->setWindowTitle(QStringLiteral("Horizontal Header Items"));

        if (documentTableHeaderDialog->exec() == QDialog::Accepted) {
            type = documentTableHeaderDialog->headerLabelType();
            parameter = documentTableHeaderDialog->headerLabelParameter();
        }
        else {
            return;
        }
    }

    for (int column = 0; column < columnCount(); column++) {
        updateHorizontalHeaderItem(column, type, parameter);
    }
}


/**
 * Updates a horizontal header item.
 */
void DocumentTable::updateHorizontalHeaderItem(int column, Settings::HeaderLabel type, QString parameter)
{
    int number = column;

    QTableWidgetItem *item = horizontalHeaderItem(column);
    item->setText(headerItemText(number, type, parameter));
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
    QString parameter = headerItemDefaultParameter(type);

    if (type == Settings::HeaderLabel::Custom) {

        DocumentTableHeaderDialog *documentTableHeaderDialog = new DocumentTableHeaderDialog(QStringLiteral("vertical"), row, this);
        documentTableHeaderDialog->setWindowTitle(QStringLiteral("Vertical Header Item"));

        if (documentTableHeaderDialog->exec() == QDialog::Accepted) {
            type = documentTableHeaderDialog->headerLabelType();
            parameter = documentTableHeaderDialog->headerLabelParameter();
        }
        else {
            return;
        }
    }

    updateVerticalHeaderItem(row, type, parameter);
}


/**
 * Updates all vertical header items.
 */
void DocumentTable::onActionLabelAllVerticalTriggered(Settings::HeaderLabel type)
{
    QString parameter = headerItemDefaultParameter(type);

    if (type == Settings::HeaderLabel::Custom) {

        DocumentTableHeaderDialog *documentTableHeaderDialog = new DocumentTableHeaderDialog(QStringLiteral("vertical"), -1, this);
        documentTableHeaderDialog->setWindowTitle(QStringLiteral("Vertical Header Items"));

        if (documentTableHeaderDialog->exec() == QDialog::Accepted) {
            type = documentTableHeaderDialog->headerLabelType();
            parameter = documentTableHeaderDialog->headerLabelParameter();
        }
        else {
            return;
        }
    }

    for (int row = 0; row < rowCount(); row++) {
        updateVerticalHeaderItem(row, type, parameter);
    }
}


/**
 * Updates a vertical header item.
 */
void DocumentTable::updateVerticalHeaderItem(int row, Settings::HeaderLabel type, QString parameter)
{
    int number = row;

    QTableWidgetItem *item = verticalHeaderItem(row);
    item->setText(headerItemText(number, type, parameter));
}
