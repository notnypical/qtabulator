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

#ifndef PREFERENCES_APPLICATION_WIDGET_H
#define PREFERENCES_APPLICATION_WIDGET_H

#include <QCheckBox>
#include <QSpinBox>
#include <QWidget>


class PreferencesApplicationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreferencesApplicationWidget(QWidget *parent = nullptr);

    QString title() const;

    bool restoreWindowGeometry() const;
    void setRestoreWindowGeometry(const bool checked);

    bool restoreDialogGeometry() const;
    void setRestoreDialogGeometry(const bool checked);

    int maximumRecentDocuments() const;
    void setMaximumRecentDocuments(const int number);

signals:
    void settingChanged();

private slots:
    void onSettingChanged();

private:
    QCheckBox *chkRestoreWindowGeometry;
    QCheckBox *chkRestoreDialogGeometry;

    QSpinBox *spbMaximumRecentDocuments;
};

#endif // PREFERENCES_APPLICATION_WIDGET_H
