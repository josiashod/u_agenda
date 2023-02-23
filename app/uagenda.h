#ifndef UAGENDA_H
#define UAGENDA_H

#include <QWidget>
#include <QDate>

class QVBoxLayout;
class QGridLayout;
class QLabel;
class QComboBox;
class QCalendarWidget;
class ContactDialog;

class UAgenda : public QWidget
{
    Q_OBJECT

public:
    UAgenda(QWidget *parent = nullptr);
    ~UAgenda();
    void creerInterface();
    void afficheDate();
    void afficheCalendrier();
    void rafraichirGrille();

public slots:
    void onReinitDate();
    void onNextMonth();
    void onPrevMonth();
    void onCalendrierChange(int year, int month);
    void onAfficheContact();


private:
    QDate d_currentDate;
    QGridLayout *d_grille;
    QCalendarWidget *d_calendrierWidget;
    QLabel *d_etiquetteDate;
    ContactDialog *contactDialog;
};
#endif // UAGENDA_H
