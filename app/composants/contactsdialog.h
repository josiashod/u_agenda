#ifndef CONTACTSDIALOG_H
#define CONTACTSDIALOG_H

#include <QDialog>
#include "./../src/lpersonne.h"
#include "./../src/lrdv.h"


class QLineEdit;
class QListWidget;
class QPushButton;

class ContactsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactsDialog(LPersonne *contacts = nullptr, LRdv *rdvs = nullptr, QWidget *parent = nullptr);
    ~ContactsDialog();

private:
    QLineEdit *d_recherche;
    QListWidget *d_list_contacts;
    QPushButton *d_order_btn;
    QString d_order;
    LPersonne *d_contacts_default;
    LPersonne *d_contacts;
    LRdv *d_rdvs;

    void creerInterface();
    void afficherContacts();
    void afficherOrderButton();
    void onModifier(personne oldPersonne, personne newPersonne);
    void onSupprimer(std::string nomComplet);
    void onRecherche(const QString &text);
    void clear();
    void onExporter();
    void onImporter();
    void onOrder();
};

#endif // CONTACTSDIALOG_H
