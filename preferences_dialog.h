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

#ifndef PREFERENCES_DIALOG_H
#define PREFERENCES_DIALOG_H

#include "preferences_application_widget.h"
#include "preferences_document_widget.h"
#include "settings.h"

#include <QDialog>
#include <QPushButton>


class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = nullptr);

    QByteArray windowGeometry() const;
    void setWindowGeometry(const QByteArray &geometry);

    Settings settings() const;
    void setSettings(const Settings &settings);

private slots:
    void onSettingChanged();

    void onButtonDefaultsClicked();
    void onButtonOkClicked();
    void onButtonApplyClicked();

private:
    QPushButton *buttonApply;

    Settings m_settings;
    void updateSettings(const Settings &settings);
    void saveSettings();

    PreferencesApplicationWidget *applicationSettings;
    PreferencesDocumentWidget *documentSettings;
};

#endif // PREFERENCES_DIALOG_H
