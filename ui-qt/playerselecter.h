#ifndef PLAYERSELECTER_H
#define PLAYERSELECTER_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class playerselecter : public QDialog
{
    Q_OBJECT
public:
    explicit playerselecter(QDialog *parent = nullptr);
    QComboBox *P[2];
    QPushButton *OkButton, *CancelButton;
    QGridLayout *layout;
    QLabel *LabelBlack, *LabelWhite, *UpperPrompt;

public slots:
    void okButtonClicked();
    void cancelButtonClicked();
};

#endif // PLAYERSELECTER_H
