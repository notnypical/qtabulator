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

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QCloseEvent>
#include <QWidget>

#include "preferences.h"


class Document : public QWidget
{
    Q_OBJECT

public:
    explicit Document(QWidget *parent = nullptr);

    void setPreferences(const Preferences &preferences);

    bool load(const QString &canonicalName);

    QString canonicalName() const;

signals:
    void documentClosed(QString);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Preferences m_preferences;

    QString m_canonicalName;
};

#endif // DOCUMENT_H
