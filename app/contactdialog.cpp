#include "contactdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>

ContactDialog::ContactDialog(QWidget *parent) :
    QDialog(parent)
{
    creerInterface();
}

ContactDialog::~ContactDialog()
{
}

void ContactDialog::creerInterface()
{
    setWindowTitle("Mes contacts");
    setMinimumSize(450, 652);

    auto main{new QVBoxLayout(this)};
    auto titre{new QLabel(tr("Liste des contacts"))};

    titre->setStyleSheet("QLabel { font-weight: bold; }");
    main->addWidget(titre, 0, Qt::AlignTop);

    d_recherche = new QLineEdit();
    d_recherche->setPlaceholderText("Rechercher un contact");
    main->addWidget(d_recherche, 0, Qt::AlignTop);

    auto liste{new QListWidget()};

    for(int i = 0; i < 50; i++)
    {
        auto item {new QListWidgetItem{"Contact N°" + QString::number(i)}};
        item->setSizeHint(QSize(0, 55));
        liste->addItem(item);
    }

    main->addWidget(liste, 55);
    main->setSpacing(10);
    main->insertStretch(-1, 1);
}
