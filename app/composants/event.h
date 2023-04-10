#ifndef EVENT_H
#define EVENT_H

#include <QDialog>
#include "./../src/lrdv.h"
#include "./../src/lpersonne.h"

class QLabel;

class Event : public QDialog
{
    Q_OBJECT

public:
    explicit Event(const rdv& r, LRdv *lrdv = nullptr, LPersonne *lpersonne = nullptr, QWidget *parent = nullptr);

signals:
    void deleted(std::string nom);
    void updated(std::string nom, const rdv& r);

private slots:
    void onSupprimer();
    void onModifier();
    void onModificationRdv(std::string nom, const rdv& r);

private:
    rdv d_rdv;
    LRdv *d_lrdv;
    LPersonne *d_lpersonne;

    QLabel* d_nom_label;
    QLabel* d_horaires_label;
    QLabel* d_description_label;
    QLabel* d_localisation_label;
    QLabel* d_participants_label;

    void creerVue();
    void afficherRdv();
};

#endif // RENDEZVOUS_H
