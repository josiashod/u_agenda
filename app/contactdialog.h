#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>

class QLineEdit;

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
