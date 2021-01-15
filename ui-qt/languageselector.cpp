#include "languageselector.h"

languageselector::languageselector(QDialog *parent) : QDialog(parent)
{
    this -> setWindowTitle(tr("Choose a language"));
    OkButton = new QPushButton();
    OkButton -> setText(tr("ok"));

    CancelButton = new QPushButton();
    CancelButton -> setText(tr("cancel"));

    LanguageBox = new QComboBox();

    LanguageBox -> addItem(tr("English"));
    LanguageBox -> addItem(tr("简体中文"));

    layout = new QGridLayout();
    layout -> addWidget(LanguageBox, 1, 1, 1, 2);
    layout -> addWidget(OkButton, 2, 1);
    layout -> addWidget(CancelButton, 2, 2);

    setLayout(layout);

    connect(OkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(CancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

    return;
}

void languageselector::okButtonClicked() {
    done(LanguageBox -> currentIndex());
    return;
}

void languageselector::cancelButtonClicked() {
    done(-1);
    return;
}
