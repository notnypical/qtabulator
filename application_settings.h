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

#ifndef APPLICATION_SETTINGS_H
#define APPLICATION_SETTINGS_H

#include <QCheckBox>
#include <QWidget>


class ApplicationSettings : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationSettings(QWidget *parent = nullptr);

    QString title() const;

    bool restoreWindowGeometry() const;
    void setRestoreWindowGeometry(const bool checked);

    bool restoreDialogGeometry() const;
    void setRestoreDialogGeometry(const bool checked);

private:
    QCheckBox *chkRestoreWindowGeometry;
    QCheckBox *chkRestoreDialogGeometry;
};

#endif // APPLICATION_SETTINGS_H
