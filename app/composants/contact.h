#ifndef CONTACT_H
#define CONTACT_H

#include <QDialog>
#include "./../src/personne.h"

class Contact : public QDialog
{
    Q_OBJECT

public:
    explicit Contact(personne* p, QWidget *parent = nullptr);

private:
    personne* d_personne;
    void creerVue();
};

#endif // CONTACT_H
