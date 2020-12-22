#ifndef LANGUAGESELECTOR_H
#define LANGUAGESELECTOR_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>

class languageselector : public QDialog
{
    Q_OBJECT
public:
    languageselector(QDialog * parent = nullptr);
private:
    QPushButton *OkButton, *CancelButton;
    QGridLayout *layout;
    QLabel *Prompt;
    QComboBox *LanguageBox;
private slots:
    void okButtonClicked();
    void cancelButtonClicked();
};

#endif // LANGUAGESELECTOR_H
