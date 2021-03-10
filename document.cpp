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

#include <QFileInfo>


Document::Document(QWidget *parent)
    : QWidget(parent)
{
    m_canonicalIndex = 0;

    setAttribute(Qt::WA_DeleteOnClose);


}


void Document::setPreferences(const Preferences &preferences)
{
    m_preferences = preferences;
}


QString Document::canonicalName() const
{
    return m_canonicalName;
}

void Document::setCanonicalName(const QString &canonicalName)
{
    m_canonicalName = canonicalName;
}


int Document::canonicalIndex() const
{
    return m_canonicalIndex;
}

void Document::setCanonicalIndex(int canonicalIndex)
{
    m_canonicalIndex = canonicalIndex;
}


QString Document::documentTitle() const
{
    return windowTitle();
}

void Document::setDocumentTitle()
{
    const auto fileName = !m_canonicalName.isEmpty() ? QFileInfo(m_canonicalName).fileName() : tr("Untitled");

    if (m_canonicalIndex > 1)
        setWindowTitle(tr("%1 (%2)").arg(fileName, QString::number(m_canonicalIndex)));
    else
        setWindowTitle(fileName);
}


bool Document::load(const QString &canonicalName)
{
    m_canonicalName = canonicalName;


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
