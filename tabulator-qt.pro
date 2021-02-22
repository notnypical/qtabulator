#
# Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
#
# This file is part of Tabulator-Qt.
#
# Tabulator-Qt is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Tabulator-Qt is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Tabulator-Qt.  If not, see <https://www.gnu.org/licenses/>.
#

QT += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about_dialog.cpp \
    colophon_about_page.cpp \
    colophon_authors_page.cpp \
    colophon_credits_page.cpp \
    colophon_dialog.cpp \
    colophon_environment_page.cpp \
    colophon_license_page.cpp \
    dialog_title_box.cpp \
    document_table.cpp \
    document_table_header_dialog.cpp \
    keyboard_shortcuts_dialog.cpp \
    keyboard_shortcuts_page.cpp \
    main.cpp \
    main_window.cpp \
    preferences.cpp \
    preferences_dialog.cpp \
    preferences_document_presets_page.cpp \
    preferences_documents_page.cpp \
    preferences_general_page.cpp

HEADERS += \
    about_dialog.h \
    colophon_about_page.h \
    colophon_authors_page.h \
    colophon_credits_page.h \
    colophon_dialog.h \
    colophon_environment_page.h \
    colophon_license_page.h \
    dialog_title_box.h \
    document_table.h \
    document_table_header_dialog.h \
    keyboard_shortcuts_dialog.h \
    keyboard_shortcuts_page.h \
    main_window.h \
    preferences.h \
    preferences_dialog.h \
    preferences_document_presets_page.h \
    preferences_documents_page.h \
    preferences_general_page.h

TRANSLATIONS += \
    translations/tabulator-qt_en.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
