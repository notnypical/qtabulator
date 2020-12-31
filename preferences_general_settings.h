/**
 * Copyright 2020 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of Tabulator-Qt.
 *
 * Tabulator-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tabulator-Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tabulator-Qt.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PREFERENCES_GENERAL_SETTINGS_H
#define PREFERENCES_GENERAL_SETTINGS_H

#include <QCheckBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>


class PreferencesGeneralSettings : public QWidget
{
    Q_OBJECT

public:
    explicit PreferencesGeneralSettings(QWidget *parent = nullptr);

    QString title() const;

    void setZeroMargins();

    void setRestoreApplicationState(const bool checked);
    bool restoreApplicationState() const;

    void setRestoreApplicationGeometry(const bool checked);
    bool restoreApplicationGeometry() const;

    void setRestoreDialogGeometry(const bool checked);
    bool restoreDialogGeometry() const;

    void setMaximumRecentDocuments(const int number);
    int maximumRecentDocuments() const;

signals:
    void settingsChanged();

private slots:
    void onSettingsChanged();

private:
    QVBoxLayout *m_layout;

    QCheckBox *m_chkRestoreApplicationState;
    QCheckBox *m_chkRestoreApplicationGeometry;
    QCheckBox *m_chkRestoreDialogGeometry;

    QSpinBox *m_spbMaximumRecentDocuments;
};

#endif // PREFERENCES_GENERAL_SETTINGS_H
