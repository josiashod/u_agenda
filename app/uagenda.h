    #ifndef UAGENDA_H
#define UAGENDA_H

#include <QWidget>
#include <QDate>
#include "./../src/lpersonne.h"
#include "./../src/lrdv.h"

class QVBoxLayout;
class QGridLayout;
class QLabel;
class QComboBox;
class QCalendarWidget;
// class ContactDialog;

class UAgenda : public QWidget
{
    Q_OBJECT

public:
    UAgenda(QWidget *parent = nullptr);
    ~UAgenda();
    void creerInterface();
    void setPolice();
    void afficheDate();
    void afficheCalendrier();
    void rafraichirGrille();
    void loadData();
    void saveData();

public slots:
    void onReinitDate();
    void onNextMonth();
    void onPrevMonth();
    void onCalendrierChange(int year, int month);
    void onAfficheContact();
    void onRechercheRdv();
    void onAfficheRdvsJour();
    void onExportRdv();
    void onAjouter(QAction *action);
    void onAjouterContact(personne p);



private:
    QDate d_currentDate;
    QGridLayout *d_grille;
    QCalendarWidget *d_calendrierWidget;
    QLabel *d_etiquetteDate;
    LPersonne *d_contacts;
    LRdv *d_rdvs;
//    ContactDialog *contactDialog;
};
#endif // UAGENDA_H
