#ifndef RDVFORM_H
#define RDVFORM_H

#include <QDialog>
#include <QDate>

#include "./../src/lrdv.h"
#include "./../src/lpersonne.h"
#include "composants/checkboxlist.h"

class QLabel;
class QLineEdit;
class QTextEdit;
class QDateTimeEdit;

class RdvForm: public QDialog
{
    Q_OBJECT

public:
    explicit RdvForm(QDate date, LRdv *lrdv = nullptr, LPersonne *lpersonne = nullptr, rdv* r = nullptr, QWidget *parent = nullptr);
    ~RdvForm();

private slots:
    void onDateChange(QDate d);
    void onHDChange(QTime time);
    void onHFChange(QTime time);
    void onAjouter();
    void onModifier();
//    void onReinitialise();

signals:
    void ajoutRdv(const rdv& r);
    void modifieRdv(std::string nom, const rdv& r);

private:
    rdv* d_rdv;
    LRdv *d_lrdv;
    LPersonne *d_lpersonne;
    QLineEdit* d_nom_input;
    QTextEdit* d_description_input;
    QLineEdit* d_localisation_input;
    QDateTimeEdit* d_date_input;
    QDateTimeEdit* d_hd_input;
    QDateTimeEdit* d_hf_input;
    CheckBoxList* d_participants_input;

    QLabel* d_nom_erreur;
    QLabel* d_description_erreur;
    QLabel* d_localisation_erreur;
    QLabel* d_participants_erreur;


    void createForm();
    bool verifieForm();
    void remplirFormulaire();
    void chargementCheckBoxList();
    void afficheDate(QDate d);
    void afficheHD(QTime time);
    void afficheHF(QTime time);
    void afficheErreur();
    bool overlapRDV();
};

#endif // RDVFORM_H
