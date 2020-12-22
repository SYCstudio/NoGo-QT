#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    //initialize buttons and labels
    StartNewGameButton = new QPushButton();
    LoadExistsGameButton = new QPushButton();
    ExitButton = new QPushButton();
    LanguageButton = new QPushButton();
    LogoWidget = new QWidget();
    Chessboard = new chessboardBase(nullptr, 20, 0);

    setLabel();

    language = new QTranslator();

    //initialzize layout
    MainWindowLayout = new QGridLayout();
    LeftButtonLayout = new QVBoxLayout();

    LeftButtonLayout -> addWidget(StartNewGameButton);
    LeftButtonLayout -> addWidget(LoadExistsGameButton);
    LeftButtonLayout -> addWidget(LanguageButton);
    LeftButtonLayout -> addWidget(ExitButton);

    MainWindowLayout -> addWidget(LogoWidget, 1, 1, 1, 2);
    MainWindowLayout -> addLayout(LeftButtonLayout, 2, 1);
    MainWindowLayout -> addWidget(Chessboard, 2, 2);

    setLayout(MainWindowLayout);

    //setup connect
    connect(ExitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(StartNewGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));
    connect(Chessboard, SIGNAL(gameEnded(int)), this, SLOT(refreshBoard(int)));
    connect(LoadExistsGameButton, SIGNAL(clicked()), this, SLOT(getSaved()));
    connect(LanguageButton, SIGNAL(clicked()), this, SLOT(selectLanguage()));

    return;
}

mainWidget::~mainWidget()
{
}

void mainWidget::startNewGame()
{
    playerselecter *selecter = new playerselecter();
    int ret = selecter -> exec();
    //qDebug() << ret;
    delete selecter;
    if (ret == -1) return;
    ioInteractor * Port = new ioInteractor(ret);
    Port -> startGame();
    //qDebug() << "PORT" ;
    return;
}

void mainWidget::refreshBoard(int opt)
{
    Chessboard -> reset();
    return;
}

void mainWidget::getSaved() {
    QString filename = QFileDialog::getOpenFileName(this, tr("choose a data file"), "", tr("Data(*.dat)"));
    if (filename.isNull()) return;
    //qDebug() << filename ;

    QFile reader(filename);
    if (!reader.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warning!"), tr("Can't open this file."), QMessageBox::Ok);
        return;
    }

    QTextStream in(&reader);

    int P1, P2;
    in >> P1 >> P2;

    mainGameWindow *buf = new mainGameWindow(nullptr, 1);

    int turn;
    in >> turn;
    for (int i = 0; i < turn; i++) {
        int x, y;
        in >> x >> y;
        buf -> place(x, y);
    }

    reader.close();
    ioInteractor *Port = new ioInteractor(P1 * 10 + P2, buf);
    return;
}

void mainWidget::selectLanguage()
{
    languageselector *selector = new languageselector();
    int ret = selector -> exec();
    //qDebug() << ret;

    if (ret == -1) return;

    QString languagename;
    if (ret == 0) languagename = "ui-qt_en_GB";
    if (ret == 1) languagename = "ui-qt_zh_CN";

    language -> load(languagename);
    qApp -> installTranslator(language);

    //reset
    setLabel();

    return;
}

void mainWidget::setLabel()
{
    setWindowTitle(tr("NoGo"));
    StartNewGameButton -> setText(tr("New game"));
    LoadExistsGameButton -> setText(tr("Load"));
    LanguageButton -> setText(tr("Language"));
    ExitButton -> setText(tr("Exit"));
    return;
}
