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

#ifndef SETTINGS_H
#define SETTINGS_H


class Settings
{
public:

    enum struct HeaderLabel {
        Custom = 0,
        Binary = 2,
        Octal = 8,
        Decimal = 10,
        Hexadecimal = 16,
        Letter = 26,
    };

    Settings() {};

    // Application: Appearance
    bool restoreWindowGeometry = true;
    bool restoreDialogGeometry = true;

    // Document: Defaults
    HeaderLabel horizontalHeaderLabels = HeaderLabel::Letter;
    int horizontalHeaderDecimalStart = 1;
    HeaderLabel verticalHeaderLabels = HeaderLabel::Decimal;
    int newDocumentColumns = 25;
    int newDocumentRows = 50;
};

#endif // SETTINGS_H
