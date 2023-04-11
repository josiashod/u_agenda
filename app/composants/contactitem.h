#ifndef CONTACTITEM_H
#define CONTACTITEM_H

#include <QWidget>
#include "./../src/lpersonne.h"
#include "./../src/lrdv.h"

class ContactItem: public QWidget
{
    Q_OBJECT

public:
    explicit ContactItem(personne *p, LRdv *lrdv = nullptr, QWidget *parent = nullptr);
    ~ContactItem();
    void creerItem();


private slots:
    void onAfficherFormModification();
    void onAfficher();
    void onModifier(personne oldPersonne, personne newPersonne);
    void onSupprimer();

signals:
    void updated(personne oldPersonne, personne newPersonne);
    void deleted(std::string nomComplet);

private:
    personne* d_personne;
    LRdv* d_lrdv;
};

#endif // CONTACTITEM_H
