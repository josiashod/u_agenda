#ifndef CONTACTSDIALOG_H
#define CONTACTSDIALOG_H

#include <QDialog>
#include "./../src/lpersonne.h"


class QLineEdit;
class QListWidget;
class QPushButton;

class ContactsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactsDialog(LPersonne *contacts = nullptr, QWidget *parent = nullptr);
    ~ContactsDialog();
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

private:
    QLineEdit *d_recherche;
    QListWidget *d_list_contacts;
    QPushButton *d_order_btn;
    QString d_order;
    LPersonne *d_contacts_default;
    LPersonne *d_contacts;
};

#endif // CONTACTSDIALOG_H
