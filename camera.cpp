#include "camera.h"

#include <QDebug>

Camera::Camera()
{
    axis = QPointF(0, 0);
    mouseIsPressed = false;

    L= -0.0; R= -L;
    T= 0.0;  B= -T;
}

void Camera::initWH(QSize s)
{
    L= -s.width()/2; R= -L;
    T= s.height()/2; B= -T;
}

void Camera::setWH(QSize s)
{
    W = s.width();
    H = s.height();
}

QPointF Camera::getWH()
{
    return QPointF(W, H);
}

QPointF Camera::getLR()
{
    return QPointF(L, R);
}

QPointF Camera::getTB()
{
    return QPointF(T, B);
}

double Camera::getScale()
{
    return L-R > T-B ? (L-R)/W : (T-B)/H;
}

QPointF Camera::toDisplay(QPointF p)
{
    //qInfo() << t.x() << " " << t.y();
    return QPointF((p.x()-L)/(R-L)*W,
                   (T-p.y())/(T-B)*H);
}

QPointF Camera::toCamera(QPointF p)
{
    return QPointF(L+(R-L)*(p.x()+0.5)/W,
                   T-(T-B)*(p.y()+0.5)/H);
}

void Camera::recalcLRTB(QSize oldS)
{
    double w = W/(double)oldS.width();
    double h = H/(double)oldS.height();
    L *= w;
    R *= w;
    T *= h;
    B *= h;
    //qInfo() << L << " " << R;
}

void Camera::navigate(QPointF dp)
{
    //qInfo() << R-L << " " << T-B;
    double dRL = R-L, dTB = T-B;

    L -= dRL*dp.x()/W;
    R  = L + dRL;
    T += dTB*dp.y()/H;
    B  = T - dTB;

    /*
    L -= dRL*dp.x()/W;
    R -= dRL*dp.x()/W;
    T += dTB*dp.y()/H;
    B += dTB*dp.y()/H;*/
}

void Camera::scale(QPointF p, double k)
{
    QPointF dp = toCamera(p);
    L = dp.x() - (dp.x() - L)/k;
    R = dp.x() - (dp.x() - R)/k;
    T = dp.y() + (T - dp.y())/k;
    B = dp.y() + (B - dp.y())/k;
}

