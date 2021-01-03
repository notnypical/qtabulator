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

#include "main_window.h"

#include <QApplication>
#include <QCommandLineParser>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("NotNypical"));
    app.setOrganizationDomain(QStringLiteral("https://notnypical.github.io"));
    app.setApplicationName(QStringLiteral("Tabulator-Qt"));
    app.setApplicationDisplayName(QStringLiteral("Tabulator-Qt"));
    app.setApplicationVersion(QStringLiteral("0.1.0"));

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "%1 - An editor tool for documents with character-separated values").arg(app.applicationName()));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(QStringLiteral("files"), QStringLiteral("Documents to open."), QStringLiteral("[files...]"));
    parser.process(app);

    MainWindow window;
    const QStringList fileNames = parser.positionalArguments();
    for (const QString &fileName : fileNames)
        window.openDocument(fileName);
    window.show();

    return app.exec();
}
