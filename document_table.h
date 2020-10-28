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

#ifndef DOCUMENT_TABLE_H
#define DOCUMENT_TABLE_H

#include "settings.h"

#include <QTableWidget>


class DocumentTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit DocumentTable(QWidget *parent = nullptr);

    void setSettings(const Settings &settings);

    void createDocument();

private slots:
    void contextMenuHorizontalHeader(const QPoint &pos);
    void onActionLabelHorizontalTriggered(int column, Settings::HeaderLabel type);
    void onActionLabelAllHorizontalTriggered(Settings::HeaderLabel type);

    void contextMenuVerticalHeader(const QPoint &pos);
    void onActionLabelVerticalTriggered(int row, Settings::HeaderLabel type);
    void onActionLabelAllVerticalTriggered(Settings::HeaderLabel type);

private:
    Settings m_settings;

    void setHorizontalHeaderItems(Settings::HeaderLabel type);
    void setVerticalHeaderItems(Settings::HeaderLabel type);
    static QString headerItemText(int number, Settings::HeaderLabel type, QString parameter);
    static QString headerItemDefaultParameter(Settings::HeaderLabel type);
    static QString numberToBinary(int number, QString parameter);
    static QString numberToOctal(int number, QString parameter);
    static QString numberToDecimal(int number, QString parameter);
    static QString numberToHexadecimal(int number, QString parameter);
    static QString numberToLetter(int number);
    static QString numberToString(int number, int base = 10);

    void updateHorizontalHeaderItem(int column, Settings::HeaderLabel type, QString parameter);
    void updateVerticalHeaderItem(int row, Settings::HeaderLabel type, QString parameter);
};

#endif // DOCUMENT_TABLE_H
