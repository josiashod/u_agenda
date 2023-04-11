#ifndef CONTACT_H
#define CONTACT_H

#include <QDialog>
#include "./../src/personne.h"
#include "./../src/lrdv.h"

class Contact : public QDialog
{
    Q_OBJECT

public:
    explicit Contact(personne* p, LRdv *lrdv = nullptr, QWidget *parent = nullptr);
    ~Contact();

private slots:
    void onAfficheRdv();

private:
    personne* d_personne;
    LRdv* d_lrdv;

    void creerVue();
};

#endif // CONTACT_H
