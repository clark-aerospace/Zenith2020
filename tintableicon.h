#ifndef TINTABLEICON_H
#define TINTABLEICON_H

#include <QColor>
#include <QIcon>
#include <QPixmap>
#include <QBitmap>
#include <QColor>

class TintableIcon : public QIcon
{
    QPixmap* _pixmap;

public:
    explicit TintableIcon(QString path);
    void setTintColor(QColor color);
};

#endif // TINTABLEICON_H
