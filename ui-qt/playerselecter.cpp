#include "playerselecter.h"

playerselecter::playerselecter(QDialog *parent) : QDialog(parent)
{
    this -> setWindowTitle(tr("Ready?"));

    OkButton = new QPushButton();
    OkButton -> setText(tr("ok"));

    CancelButton = new QPushButton();
    CancelButton -> setText(tr("cancel"));

    LabelBlack = new QLabel();
    LabelBlack -> setText(tr("black:"));
    LabelWhite = new QLabel();
    LabelWhite -> setText(tr("white:"));
    UpperPrompt = new QLabel();
    UpperPrompt -> setText(tr("Please choose the players.\nThe black will move chess first."));

    layout = new QGridLayout();
    layout -> addWidget(UpperPrompt, 1, 1, 1, 2);
    layout -> addWidget(LabelBlack, 2, 1);
    layout -> addWidget(LabelWhite, 2, 2);
    layout -> addWidget(OkButton, 4, 1);
    layout -> addWidget(CancelButton, 4, 2);

    for (int i = 0; i < 2; i++) {
        P[i] = new QComboBox();
        P[i] -> addItem(tr("Human"));
        P[i] -> addItem(tr("AI(level 0)"));
        P[i] -> addItem(tr("AI(level 1)"));
        P[i] -> addItem(tr("AI(level 2)"));
        layout -> addWidget(P[i], 3, i+1);
    }

    setLayout(layout);

    connect(OkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(CancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

    return;
}

void playerselecter::okButtonClicked() {
    done(P[0] -> currentIndex() * 10 + P[1] -> currentIndex());
}

void playerselecter::cancelButtonClicked() {
    done(-1);
}
