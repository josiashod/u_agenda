QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    composants/checkboxlist.cpp \
    composants/contact.cpp \
    composants/contactform.cpp \
    composants/contactitem.cpp \
    composants/contactsdialog.cpp \
    composants/event.cpp \
    composants/rdvdialog.cpp \
    composants/rdvitem.cpp \
    main.cpp \
    rdvform.cpp \
    uagenda.cpp \
    ./../src/date.cpp \
    ./../src/heure.cpp \
    ./../src/personne.cpp \
    ./../src/lpersonne.cpp \
    ./../src/rdv.cpp \
    ./../src/lrdv.cpp


HEADERS += \
    composants/checkboxlist.h \
    composants/contact.h \
    composants/contactform.h \
    composants/contactitem.h \
    composants/contactsdialog.h \
    composants/event.h \
    composants/rdvdialog.h \
    composants/rdvitem.h \
    rdvform.h \
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
