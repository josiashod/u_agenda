#ifndef CONTACTSDIALOG_H
#define CONTACTSDIALOG_H

#include <QDialog>
#include "./../src/lpersonne.h"


class QLineEdit;
class QListWidget;

class ContactsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactsDialog(LPersonne *contacts = nullptr, QWidget *parent = nullptr);
    ~ContactsDialog();
    void creerInterface();
    void afficherContacts();
    void onModifier(personne oldPersonne, personne newPersonne);
    void onSupprimer(std::string nomComplet);
    void onRecherche(const QString &text);
    void clear();
    void onExporter();
    void onImporter();

private:
    QLineEdit *d_recherche;
    QListWidget *d_list_contacts;
    LPersonne *d_contacts_default;
    LPersonne *d_contacts;
};

#endif // CONTACTSDIALOG_H
