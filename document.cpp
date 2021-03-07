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

#include "document.h"


Document::Document(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);


}


void Document::setPreferences(const Preferences &preferences)
{
    m_preferences = preferences;
}


void Document::setCanonicalName(const QString &canonicalName)
{
    m_canonicalName = canonicalName;
}


QString Document::canonicalName() const
{
    return m_canonicalName;
}


void Document::setCanonicalIndex(int canonicalIndex)
{
    m_canonicalIndex = canonicalIndex;
}


int Document::canonicalIndex()
{
    return m_canonicalIndex;
}


bool Document::load(const QString &canonicalName)
{
    setCanonicalName(canonicalName);


    return true;
}


void Document::closeEvent(QCloseEvent *event)
{
    if (true) {
        // Document will be closed
        emit documentClosed(m_canonicalName);

        event->accept();
    } else {
        event->ignore();
    }
}
