#ifndef CONTACTFORM_H
#define CONTACTFORM_H

#include <QDialog>

#include "./../src/personne.h"

class QLabel;
class QLineEdit;

class ContactForm : public QDialog
{
    Q_OBJECT

public:
    explicit ContactForm(personne* p = nullptr, QWidget *parent = nullptr);
    ~ContactForm();

private slots:
    void onAjouter();
    void onModifier();

signals:
    void ajoutPersonne(personne p);
    void modifiePersonne(personne oldPersonne, personne newPersonne);

private:
    personne* d_personne;
    QLineEdit* d_nom_input;
    QLineEdit* d_prenom_input;
    QLineEdit* d_numero_input;
    QLineEdit* d_email_input;

    QLabel* d_nom_erreur;
    QLabel* d_prenom_erreur;
    QLabel* d_numero_erreur;
    QLabel* d_email_erreur;

    void createForm();
    bool verifieForm();
    void afficheErreur();
};

#endif // CONTACTFORM_H
