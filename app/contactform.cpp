#include "contactform.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRegularExpressionValidator>

ContactForm::ContactForm(personne* p, QWidget *parent) :
    QDialog(parent),
    d_personne{p}
{
    createForm();
}

ContactForm::~ContactForm()
{
}

void ContactForm::createForm()
{
    if (!d_personne)
        setWindowTitle("Ajouter un contact");
    else
        setWindowTitle("Modifier "+ QString::fromStdString(d_personne->nomComplet()));
    setMinimumSize(450, 382);

    auto main{new QVBoxLayout(this)};

    d_nom_input = new QLineEdit();
    d_prenom_input = new QLineEdit();
    d_numero_input = new QLineEdit();
    d_email_input = new QLineEdit();

    d_nom_erreur = new QLabel{""};
    d_nom_erreur->setStyleSheet("QLabel{ color: #e11d48 }");

    d_prenom_erreur = new QLabel{""};
    d_prenom_erreur->setStyleSheet("QLabel{ color: #e11d48 }");

    d_numero_erreur = new QLabel{""};
    d_numero_erreur->setStyleSheet("QLabel{ color: #e11d48 }");

    d_email_erreur = new QLabel{""};
    d_email_erreur->setStyleSheet("QLabel{ color: #e11d48 }");

    QRegularExpression nomRegx("[A-Z]+");
    QRegularExpression prenomRegx("[A-Z].[a-z]+");
    QRegularExpression numRegx("(0|\\+33|0033)[1-9][0-9]{8}");
    QRegularExpression emailRegx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b", QRegularExpression::CaseInsensitiveOption);

    d_nom_input->setPlaceholderText("DOE");
    d_nom_input->setValidator(new QRegularExpressionValidator(nomRegx));

    d_prenom_input->setPlaceholderText("John");
    d_prenom_input->setValidator(new QRegularExpressionValidator(prenomRegx));

    d_numero_input->setPlaceholderText("+33 99 99 99 99");
    d_numero_input->setValidator(new QRegularExpressionValidator(numRegx));
    d_email_input->setPlaceholderText("john.d@example.com");
    d_email_input->setValidator(new QRegularExpressionValidator(emailRegx));

    if(d_personne)
    {
        d_nom_input->setText(QString::fromStdString(d_personne->nom()));
        d_prenom_input->setText(QString::fromStdString(d_personne->prenom()));
        d_numero_input->setText(QString::fromStdString(d_personne->numero()));
        d_email_input->setText(QString::fromStdString(d_personne->email()));
    }

    main->addWidget(new QLabel{tr("Nom")});
    main->addWidget(d_nom_input);
    main->addWidget(d_nom_erreur);
    main->addSpacing(5);

    main->addWidget(new QLabel{tr("Prenom")});
    main->addWidget(d_prenom_input);
    main->addWidget(d_prenom_erreur);
    main->addSpacing(5);

    main->addWidget(new QLabel{tr("Numero")});
    main->addWidget(d_numero_input);
    main->addWidget(d_numero_erreur);
    main->addSpacing(5);

    main->addWidget(new QLabel{tr("Email")});
    main->addWidget(d_email_input);
    main->addWidget(d_email_erreur);
    main->addSpacing(10);

    auto btn{new QPushButton{}};

    if(!d_personne)
    {
        btn->setText("Ajouter");
        btn->setStyleSheet("QPushButton{background-color: #0D9488}");
        connect(btn, &QPushButton::clicked, this, &ContactForm::onAjouter);
    }
    else
    {
        btn->setText("Enregistrer");
        btn->setStyleSheet("QPushButton{background-color: #fb923c}");
        connect(btn, &QPushButton::clicked, this, &ContactForm::onModifier);
    }

    main->addStretch(1);
    main->addWidget(btn, 0, Qt::AlignBottom);
}

bool ContactForm::verifieForm()
{
    return (d_nom_input->text().length() >= 3 &&
        d_prenom_input->text().length() >= 3 &&
        d_numero_input->hasAcceptableInput() &&
        d_email_input->hasAcceptableInput());
}

void ContactForm::afficheErreur()
{
    if(!d_nom_input->text().length())
        d_nom_erreur->setText("Veuillez entrer un nom");
    else if(d_nom_input->text().length() < 2)
        d_nom_erreur->setText("Le nom doit comporter au moins 3 caractères");
    else
        d_nom_erreur->setText("");

    if(!d_prenom_input->text().length())
        d_prenom_erreur->setText("Veuillez entrer un prénom");
    else if(d_prenom_input->text().length() < 2)
        d_prenom_erreur->setText("Le prenom doit comporter au moins 3 caractères");
    else
        d_prenom_erreur->setText("");

    if(!d_email_input->text().length())
        d_email_erreur->setText("Veuillez entrer un email");
    else if(!d_email_input->hasAcceptableInput())
        d_email_erreur->setText("L'email n'est pas valide");
    else
        d_email_erreur->setText("");

    if(!d_numero_input->text().length())
        d_numero_erreur->setText("Veuillez entrer un numéro de télephone");
    else if(!d_numero_input->hasAcceptableInput())
        d_numero_erreur->setText("Le numéro de téléphone n'est pas valide");
    else
        d_numero_erreur->setText("");
}

void ContactForm::onAjouter()
{
    afficheErreur();

    if(verifieForm())
    {
        std::string nom = d_nom_input->text().toStdString();
        std::string prenom = d_prenom_input->text().toStdString();
        std::string email = d_email_input->text().toStdString();
        std::string numero = d_numero_input->text().toStdString();

        personne p{nom, prenom, numero, email};
        hide();
        emit addPersonne(p);
    }
//    else
//    {
//        QMessageBox{QMessageBox::Critical, tr("Erreur dans le formulaire"), tr("Les informations entrées ne sont pas correctes")}.exec();
//    }
}

void ContactForm::onModifier()
{
    afficheErreur();

    if(verifieForm())
    {
        std::string nom = d_nom_input->text().toStdString();
        std::string prenom = d_prenom_input->text().toStdString();
        std::string email = d_email_input->text().toStdString();
        std::string numero = d_numero_input->text().toStdString();

        personne p{nom, prenom, numero, email};
        hide();
        emit updatePersonne(*d_personne, p);
    }
//    else
//    {
//        QMessageBox{QMessageBox::Critical, tr("Erreur dans le formulaire"), tr("Les informations entrées ne sont pas correctes")}.exec();
//    }
}
