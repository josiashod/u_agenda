#include "checkboxlist.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QEvent>
#include <QListWidget>

namespace {
    const int scSearchBarIndex = 0;
}

CheckBoxList::CheckBoxList(QWidget* parent) :
    QComboBox(parent),
    d_liste_widget(new QListWidget(this)),
    d_line_edit(new QLineEdit(this)),
    d_search_bar(new QLineEdit(this))
{
    this->clearFocus();
    QListWidgetItem* curItem = new QListWidgetItem(d_liste_widget);
    d_search_bar->setPlaceholderText("Rechercher ...");
    d_search_bar->setClearButtonEnabled(true);
    d_search_bar->clearFocus();
    d_liste_widget->addItem(curItem);
    d_liste_widget->setItemWidget(curItem, d_search_bar);

    d_line_edit->clearFocus();
    d_line_edit->setReadOnly(true);
    d_line_edit->installEventFilter(this);

    setModel(d_liste_widget->model());
    setView(d_liste_widget);
    setLineEdit(d_line_edit);

    connect(d_search_bar, &QLineEdit::textChanged, this, &CheckBoxList::onSearch);
    connect(this, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &CheckBoxList::itemClicked);
}

void CheckBoxList::hidePopup()
{
    int width = this->width();
    int height = d_liste_widget->height();
    int x = QCursor::pos().x() - mapToGlobal(geometry().topLeft()).x() + geometry().x();
    int y = QCursor::pos().y() - mapToGlobal(geometry().topLeft()).y() + geometry().y();
    if (x >= 0 && x <= width && y >= this->height() && y <= height + this->height())
    {
        // Item was clicked, do not hide popup
    }
    else
    {
        QComboBox::hidePopup();
    }
}

void CheckBoxList::stateChanged(int state)
{
    Q_UNUSED(state);
    QString selectedData("");
    int count = d_liste_widget->count();

    for (int i = 1; i < count; ++i)
    {
        QWidget *widget = d_liste_widget->itemWidget(d_liste_widget->item(i));
        QCheckBox *checkBox = static_cast<QCheckBox *>(widget);

        if (checkBox->isChecked())
        {
            selectedData.append(checkBox->text()).append("; ");
        }
    }
    if (selectedData.endsWith("; "))
    {
        selectedData.remove(selectedData.length() - 2, 2);
    }
    if (!selectedData.isEmpty())
    {
        d_line_edit->setText(selectedData);
    }
    else
    {
        d_line_edit->clear();
    }

    d_line_edit->setToolTip(selectedData);
    emit selectionChanged();
}

void CheckBoxList::addItem(const QString& text, const QVariant& userData)
{
    Q_UNUSED(userData);
    QListWidgetItem* listWidgetItem = new QListWidgetItem(d_liste_widget);
    QCheckBox* checkBox = new QCheckBox(this);
    checkBox->setText(text);
    d_liste_widget->addItem(listWidgetItem);
    d_liste_widget->setItemWidget(listWidgetItem, checkBox);
    connect(checkBox, &QCheckBox::stateChanged, this, &CheckBoxList::stateChanged);
}

QStringList CheckBoxList::currentText()
{
    QStringList emptyStringList;
    if(!d_line_edit->text().isEmpty())
    {
        emptyStringList = d_line_edit->text().split("; ");
    }
    return emptyStringList;
}

void CheckBoxList::addItems(const QStringList& texts)
{
    for(const auto& string : texts)
    {
        addItem(string);
    }
}

int CheckBoxList::count() const
{
    int count = d_liste_widget->count() - 1;// Do not count the search bar
    if(count < 0)
    {
        count = 0;
    }
    return count;
}

void CheckBoxList::onSearch(const QString& searchString)
{
    for(int i = 1; i < d_liste_widget->count(); i++)
    {
        QCheckBox* checkBox = static_cast<QCheckBox*>(d_liste_widget->itemWidget(d_liste_widget->item(i)));
        if(checkBox->text().contains(searchString, Qt::CaseInsensitive))
        {
            d_liste_widget->item(i)->setHidden(false);
        }
        else
        {
            d_liste_widget->item(i)->setHidden(true);
        }
    }
}


void CheckBoxList::itemClicked(int index)
{
    if(index != scSearchBarIndex)// 0 means the search bar
    {
        QWidget* widget = d_liste_widget->itemWidget(d_liste_widget->item(index));
        QCheckBox *checkBox = static_cast<QCheckBox *>(widget);
        checkBox->setChecked(!checkBox->isChecked());
    }
}

void CheckBoxList::setSearchBarPlaceHolderText(const QString& placeholderText)
{
    d_search_bar->setPlaceholderText(placeholderText);
}

void CheckBoxList::setPlaceHolderText(const QString& placeholderText)
{
    d_line_edit->setPlaceholderText(placeholderText);
}

void CheckBoxList::clear()
{
    d_liste_widget->clear();
    QListWidgetItem* curItem = new QListWidgetItem(d_liste_widget);
    d_search_bar = new QLineEdit(this);
    d_search_bar->setPlaceholderText("Rechercher ...");
    d_search_bar->setClearButtonEnabled(true);
    d_liste_widget->addItem(curItem);
    d_liste_widget->setItemWidget(curItem, d_search_bar);

    connect(d_search_bar, &QLineEdit::textChanged, this, &CheckBoxList::onSearch);
}

void CheckBoxList::wheelEvent(QWheelEvent* wheelEvent)
{
    // Do not handle the wheel event
    Q_UNUSED(wheelEvent);
}

bool CheckBoxList::eventFilter(QObject* object, QEvent* event)
{
    if(object == d_line_edit && event->type() == QEvent::MouseButtonRelease) {
        showPopup();
        return false;
    }
    return false;
}

void CheckBoxList::keyPressEvent(QKeyEvent* event)
{
    // Do not handle key event
    Q_UNUSED(event);
}

void CheckBoxList::setCurrentText(const QString& text)
{
    Q_UNUSED(text);
}

void CheckBoxList::setCurrentText(const QStringList& text)
{
    int count = d_liste_widget->count();

    for (int i = 1; i < count; ++i)
    {
        QWidget* widget = d_liste_widget->itemWidget(d_liste_widget->item(i));
        QCheckBox* checkBox = static_cast<QCheckBox*>(widget);
        QString checkBoxString = checkBox->text();
        if(text.contains(checkBoxString))
        {
            checkBox->setChecked(true);
        }
    }
}

void CheckBoxList::ResetSelection()
{
    int count = d_liste_widget->count();

    for (int i = 1; i < count; ++i)
    {
        QWidget *widget = d_liste_widget->itemWidget(d_liste_widget->item(i));
        QCheckBox *checkBox = static_cast<QCheckBox *>(widget);
        checkBox->setChecked(false);
    }
}
