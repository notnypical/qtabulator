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

#ifndef COLOPHONDIALOG_H
#define COLOPHONDIALOG_H

#include <QCloseEvent>
#include <QDialog>
#include <QDialogButtonBox>
#include <QTextBrowser>


class ColophonDialog : public QDialog
{
public:
    ColophonDialog();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onButtonCloseClicked();

private:
    void setupUI();
    QTextBrowser *createTabAbout();
    QTextBrowser *createTabEnvironment();
    QTextBrowser *createTabLicense();
    QTextBrowser *createTabAuthors();

    void readSettings();
    void writeSettings();

    QDialogButtonBox *buttonBox;
};

#endif // COLOPHONDIALOG_H
