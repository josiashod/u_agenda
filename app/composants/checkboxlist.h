#ifndef CHECKBOXLIST_H
#define CHECKBOXLIST_H

#include <QComboBox>

class QListWidget;
class QLineEdit;

class CheckBoxList : public QComboBox
{
    Q_OBJECT

public:
    CheckBoxList(QWidget *parent = nullptr);
    void addItem(const QString& text, const QVariant& userData = QVariant());
    void addItems(const QStringList& texts);
    QStringList currentText();
    int count() const;
    void hidePopup() override;
    void setSearchBarPlaceHolderText(const QString& placeholderText);
    void setPlaceHolderText(const QString& placeholderText);
    void ResetSelection();

signals:
    void selectionChanged();

public slots:
    void clear();
    void setCurrentText(const QString& text);
    void setCurrentText(const QStringList& text);

protected:
    void wheelEvent(QWheelEvent* wheelEvent) override;
    bool eventFilter(QObject* object, QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    void stateChanged(int state);
    void onSearch(const QString& searchString);
    void itemClicked(int index);

    QListWidget* d_liste_widget;
    QLineEdit* d_line_edit;
    QLineEdit* d_search_bar;
};

#endif // CHECKBOXLIST_H
