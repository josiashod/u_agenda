#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>

class QLineEdit;

class Contact: public QWidget
{
    Q_OBJECT

public:
    explicit Contact(QWidget *parent = nullptr, QString nomComplet = "", QString numero = "");
    ~Contact();
    void creerInterface();

private:
    QString d_nomComplet;
    QString d_numero;
};

class ContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactDialog(QWidget *parent = nullptr);
    ~ContactDialog();
    void creerInterface();

private:
    QLineEdit *d_recherche;
};

#endif // CONTACTDIALOG_H
