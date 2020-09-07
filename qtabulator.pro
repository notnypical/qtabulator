#
# Copyright 2020 NotNypical, <https://notnypical.github.io>.
#
# This file is part of qTabulator.
#
# qTabulator is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# qTabulator is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with qTabulator.  If not, see <https://www.gnu.org/licenses/>.
#
QT       += core gui svg

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
    about_page.cpp \
    authors_page.cpp \
    colophon_dialog.cpp \
    credits_page.cpp \
    dialog_title_box.cpp \
    environment_page.cpp \
    license_page.cpp \
    main.cpp \
    main_window.cpp \
    preferences_dialog.cpp

HEADERS += \
    about_dialog.h \
    about_page.h \
    authors_page.h \
    colophon_dialog.h \
    credits_page.h \
    dialog_title_box.h \
    environment_page.h \
    license_page.h \
    main_window.h \
    preferences_dialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS +=
