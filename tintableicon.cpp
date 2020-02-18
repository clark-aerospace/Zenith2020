#include "tintableicon.h"

TintableIcon::TintableIcon(QString path) : QIcon()
{

    this->_pixmap = new QPixmap(path, nullptr, Qt::MonoOnly);
    this->addPixmap(*_pixmap);
}

void TintableIcon::setTintColor(QColor color) {
    QBitmap mask = this->_pixmap->createMaskFromColor(QColor('black'), Qt::MaskOutColor);
    this->_pixmap->fill(color);
    this->_pixmap->setMask(mask);
    this->addPixmap(*this->_pixmap);
}
