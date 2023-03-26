QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contact.cpp \
    contactform.cpp \
    contactitem.cpp \
    contactsdialog.cpp \
    main.cpp \
    rdvdialog.cpp \
    uagenda.cpp \
    ./../src/date.cpp \
    ./../src/heure.cpp \
    ./../src/personne.cpp \
    ./../src/lpersonne.cpp \
    ./../src/rdv.cpp \
    ./../src/lrdv.cpp


HEADERS += \
    contact.h \
    contactform.h \
    contactitem.h \
    contactsdialog.h \
    rdvdialog.h \
    uagenda.h \
    ./../src/date.h \
    ./../src/error.h \
    ./../src/heure.h \
    ./../src/personne.h \
    ./../src/lpersonne.h \
    ./../src/rdv.h \
    ./../src/lrdv.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    app.qrc \
