#ifndef RDVITEM_H
#define RDVITEM_H


#include <QWidget>
#include "./../src/lrdv.h"
#include "./../src/lpersonne.h"

class QLineEdit;

class RdvItem: public QWidget
{
    Q_OBJECT

public:
    explicit RdvItem(const rdv& r, LRdv *rdvs = nullptr, LPersonne *lpersonne = nullptr, QWidget *parent = nullptr);
    ~RdvItem();

private slots:
    void onAfficher();
    void onAfficherFormModif();
    void onModifier(std::string nom, const rdv& r);
    void onSupprimer();

signals:
    void updated(std::string nom, const rdv& r);
    void deleted(std::string nom);

private:
    rdv d_rdv;
    LRdv *d_rdvs;
    LPersonne *d_lpersonne;
    void creerInterface();
};

#endif // RDVITEM_H
