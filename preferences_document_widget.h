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

#ifndef PREFERENCES_DOCUMENT_WIDGET_H
#define PREFERENCES_DOCUMENT_WIDGET_H

#include "settings.h"

#include <QButtonGroup>
#include <QSpinBox>
#include <QWidget>


class PreferencesDocumentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreferencesDocumentWidget(QWidget *parent = nullptr);

    QString title() const;

    Settings::HeaderLabel horizontalHeaderLabels() const;
    void setHorizontalHeaderLabels(const Settings::HeaderLabel type);

    int horizontalHeaderDecimalStart() const;
    void setHorizontalHeaderDecimalStart(const int number);

    Settings::HeaderLabel verticalHeaderLabels() const;
    void setVerticalHeaderLabels(const Settings::HeaderLabel type);

    int verticalHeaderDecimalStart() const;
    void setVerticalHeaderDecimalStart(const int number);

    int defaultCellColumns() const;
    void setDefaultCellColumns(const int number);

    int defaultCellRows() const;
    void setDefaultCellRows(const int number);

signals:
    void settingChanged();

private slots:
    void onSettingChanged();

private:
    QButtonGroup *horizontalHeaderLabelsGroup;
    QButtonGroup *horizontalHeaderDecimalStartGroup;
    QButtonGroup *verticalHeaderLabelsGroup;
    QButtonGroup *verticalHeaderDecimalStartGroup;

    QSpinBox *spbDefaultCellColumns;
    QSpinBox *spbDefaultCellRows;
};

#endif // PREFERENCES_DOCUMENT_WIDGET_H
