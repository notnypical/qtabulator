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

#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>


static const QString OrganizationName            = QStringLiteral("NotNypical");
static const QString OrganizationDomain          = QStringLiteral("https://notnypical.github.io");
static const QString ApplicationName             = QStringLiteral("qTabulator");
static const QString ApplicationBriefDescription = QStringLiteral("A CSV editor written in Qt for C++.");
static const QString ApplicationVersion          = QStringLiteral("0.1.0");


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName(OrganizationName);
    app.setOrganizationDomain(OrganizationDomain);
    app.setApplicationName(ApplicationName);
    app.setApplicationVersion(ApplicationVersion);

    QCommandLineParser parser;
    parser.setApplicationDescription(QString("%1 - %2").arg(ApplicationName, ApplicationBriefDescription));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    MainWindow window;
    window.show();

    return app.exec();
}
