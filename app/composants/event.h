#ifndef EVENT_H
#define EVENT_H

#include <QDialog>
#include "./../src/lrdv.h"
#include "./../src/lpersonne.h"

class Event : public QDialog
{
    Q_OBJECT

public:
    explicit Event(const rdv& r, LRdv *lrdv = nullptr, LPersonne *lpersonne = nullptr, QWidget *parent = nullptr);
    void creerVue();

signals:
    void deleted(std::string nom);

private slots:
    void onSupprimer();

private:
    rdv d_rdv;
    LRdv *d_lrdv;
    LPersonne *d_lpersonne;
};

#endif // RENDEZVOUS_H
