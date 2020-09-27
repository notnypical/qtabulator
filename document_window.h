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

#ifndef DOCUMENT_WINDOW_H
#define DOCUMENT_WINDOW_H

#include "settings.h"

#include <QAction>
#include <QTableWidget>


class DocumentWindow : public QTableWidget
{
    Q_OBJECT

public:
    explicit DocumentWindow(QWidget *parent = nullptr);

    void setSettings(const Settings &settings);

    void createDocument();

private slots:
    void contextMenuHorizontalHeader(const QPoint &pos);
    void contextMenuVerticalHeader(const QPoint &pos);

    void onActionLabelHorizontalTriggered(int column, int type);

private:
    void createActions();
    QAction *actionLabelHorizontalLetter;

    Settings m_settings;

    void setHorizontalHeaderItems(int type);
    void setVerticalHeaderItems(int type);
    static QString headerItemText(int number, int type);
    static QString numberToBinary(int number);
    static QString numberToOctal(int number);
    static QString numberToHexadecimal(int number);
    static QString numberToHexavigesimal(int number);
    static QString numberToString(int number, int base = 10);

    void updateHorizontalHeaderItem(int column, int type);
};

#endif // DOCUMENT_WINDOW_H
