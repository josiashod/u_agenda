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
    explicit RdvForm(QDate date,LRdv *lrdv = nullptr, LPersonne *lpersonne = nullptr, rdv* r = nullptr, QWidget *parent = nullptr);
    ~RdvForm();
    void createForm();
    bool verifieForm();
    void afficheErreur();

private slots:
//    void onAjouter();
//    void onModifier();
    void onReinitialise();

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
    QDate d_date;


    QLabel* d_nom_erreur;
    QLabel* d_description_erreur;
    QLabel* d_localisation_erreur;
    QLabel* d_date_erreur;
    QLabel* d_hd_erreur;
    QLabel* d_hf_erreur;
    QLabel* d_participants_erreur;
};

#endif // RDVFORM_H
