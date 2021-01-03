/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
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

#ifndef COLOPHON_CREDITS_PAGE_H
#define COLOPHON_CREDITS_PAGE_H

#include <QVBoxLayout>
#include <QWidget>


class ColophonCreditsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ColophonCreditsPage(QWidget *parent = nullptr);

    QString title() const;

    void setZeroMargins();

private:
    QVBoxLayout *m_layout;
};

#endif // COLOPHON_CREDITS_PAGE_H
