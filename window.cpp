#include "widget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QSignalMapper>
#include <QTimer>

Window::Window()
{
    setWindowTitle(tr("2D graph"));

    Widget *drawidg = new Widget(&renderer, this);
    QPushButton *bgr1 = createButton("100sin()-30cos()");

    QPushButton *bgr2 = createButton("f(a)");




    QLabel *affineLabel = new QLabel(tr("Affine transformations:"));
    //affineLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
    QPushButton *ba0 = createButton("- Reset- ");



    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    connect(bgr1, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(bgr2, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(ba0, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    signalMapper -> setMapping (bgr1, 1) ;
    signalMapper -> setMapping (bgr2, 2) ;
    signalMapper -> setMapping (ba0, 3) ;

    connect (signalMapper, SIGNAL(mapped(int)), drawidg, SLOT(setGraphFunc(int))) ;



    QGridLayout *layout = new QGridLayout;
    layout->addWidget(drawidg, 0, 0, 5, 1);
    layout->addWidget(bgr1,0,1);
    layout->addWidget(bgr2,1,1);
    layout->addWidget(affineLabel, 2,1, Qt::AlignTop | Qt::AlignRight);
    layout->addWidget(ba0, 3,1, Qt::AlignTop | Qt::AlignRight);

    layout->setColumnStretch(0, 70);
    layout->setColumnStretch(1, 1);
    setLayout(layout);

    this->resize(900, 800);

    //QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, native, &Widget::animate);
    //timer->start(60);
}

QPushButton* Window::createButton(QString text)
{
    QPushButton* b = new QPushButton;
    b->setText(text);
    b->setMinimumSize(140,40);

    return b;
}