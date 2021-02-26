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

#ifndef DOCUMENT_TABLE_H
#define DOCUMENT_TABLE_H

#include "preferences.h"

#include <QTableWidget>


class DocumentTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit DocumentTable(QWidget *parent = nullptr);

    void setPreferences(const Preferences &preferences);

    void newDocument();
    bool loadDocument(const QString &file);
    QString file() const;
    QString filePath() const;
    QString fileName() const;

private slots:
    void contextMenuHorizontalHeader(const QPoint &pos);
    void onActionLabelHorizontalTriggered(int column, Preferences::HeaderLabel type);
    void onActionLabelAllHorizontalTriggered(Preferences::HeaderLabel type);

    void contextMenuVerticalHeader(const QPoint &pos);
    void onActionLabelVerticalTriggered(int row, Preferences::HeaderLabel type);
    void onActionLabelAllVerticalTriggered(Preferences::HeaderLabel type);

private:
    Preferences m_preferences;
    QString m_file;
    bool isUntitled;

    void setHorizontalHeaderItems(Preferences::HeaderLabel type);
    void setVerticalHeaderItems(Preferences::HeaderLabel type);
    static QString headerItemText(int number, Preferences::HeaderLabel type, QString parameter);
    static QString headerItemDefaultParameter(Preferences::HeaderLabel type);
    static QString numberToCustom(int number, QString parameter);
    static QString numberToBinary(int number, QString parameter);
    static QString numberToOctal(int number, QString parameter);
    static QString numberToDecimal(int number, QString parameter);
    static QString numberToHexadecimal(int number, QString parameter);
    static QString numberToLetter(int number, QString parameter);
    static QString numberToString(int number, int base = 10);

    void updateHorizontalHeaderItem(int column, Preferences::HeaderLabel type, QString parameter);
    void updateVerticalHeaderItem(int row, Preferences::HeaderLabel type, QString parameter);
};

#endif // DOCUMENT_TABLE_H
