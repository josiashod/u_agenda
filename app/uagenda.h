#ifndef UAGENDA_H
#define UAGENDA_H

#include <QWidget>
#include <QDate>
#include "./../src/lpersonne.h"
#include "./../src/lrdv.h"

class QLineEdit;
class QVBoxLayout;
class QGridLayout;
class QLabel;
class QComboBox;
class QCalendarWidget;
class QPushButton;

class UAgenda : public QWidget
{
    Q_OBJECT

public:
    UAgenda(QWidget *parent = nullptr);
    ~UAgenda();

private slots:
    void onReinitDate();
    void onNextMonth();
    void onPrevMonth();
    void onDateChange(QDate d);
    void onCalendrierChange(int year, int month);
    void onAfficheContact();
    void onSearchBar(const QString &text);
    void onRechercheRdv();
    void onAfficheRdvsJour();
    void onExportRdv();
    void onAjouter(QAction *action);
    void onAjouterContact(personne p);
    void onAfficheRdv();
    void onSupprimerRdv(std::string nom);
    void onAjoutRdv();


private:
    QDate d_currentDate;
    QVBoxLayout *d_calendrier;
    QGridLayout *d_grille;
    QVBoxLayout *d_layouts_grille[37];
    QCalendarWidget *d_calendrierWidget;
    QLabel *d_etiquetteDate;
    LPersonne *d_contacts;
    LRdv *d_rdvs;
    QLineEdit *d_search_in;
    QPushButton *d_search_btn;

    void creerInterface();
    void setPolice();
    void afficheDate();
    void creerGrille();
    void afficheCalendrier();
    void rafraichirGrille();
    void loadData();
    void saveData();
//    ContactDialog *contactDialog;
};
#endif // UAGENDA_H
