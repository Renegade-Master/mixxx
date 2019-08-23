#include "waveform/waveformmarklabel.h"
#include "util/math.h"

void WaveformMarkLabel::prerender(QPointF bottomLeft, QPixmap icon, QString text,
            QFont font, QColor textColor, QColor backgroundColor,
            float widgetWidth, double scaleFactor) {
    if (text.isEmpty() && icon.isNull()) {
        clear();
        return;
    }

    m_text = text;
    QFontMetrics fontMetrics(font);
    const int padding = 2;

    QRectF pixmapRect;
    pixmapRect = fontMetrics.boundingRect(text);
    if (icon.isNull()) {
        pixmapRect.setWidth(padding + pixmapRect.width() + padding);
    } else {
        pixmapRect.setWidth(padding + icon.width() + padding + pixmapRect.width() + padding);
    }
    pixmapRect.setHeight(math_max(fontMetrics.height(), icon.height()));

    // pixmapRect has a top left of (0,0) for rendering to m_pixmap.
    // m_areaRect is the same size but shifted to the coordinates of the widget.
    m_areaRect = pixmapRect;
    QPointF topLeft = QPointF(bottomLeft.x(),
            bottomLeft.y() - pixmapRect.height());
    m_areaRect.moveTo(topLeft);

    if (m_areaRect.right() > widgetWidth) {
        m_areaRect.setLeft(widgetWidth - m_areaRect.width());
    }

    m_pixmap = QPixmap(pixmapRect.width() * scaleFactor, pixmapRect.height() * scaleFactor);
    m_pixmap.setDevicePixelRatio(scaleFactor);
    m_pixmap.fill(Qt::transparent);

    QPainter painter(&m_pixmap);

    painter.setPen(backgroundColor);
    painter.setBrush(QBrush(backgroundColor));
    painter.drawRoundedRect(0, 0, pixmapRect.width(), pixmapRect.height(), 5.0, 5.0);

    if (!icon.isNull()) {
        QPointF iconTopLeft = pixmapRect.topLeft();
        iconTopLeft.setX(iconTopLeft.x() + padding);
        painter.drawPixmap(iconTopLeft, icon);
    }

    if (!text.isEmpty()) {
        // QPainter::drawText draws from the bottom left point.
        QPointF textPoint;
        textPoint.setX(icon.width() + padding);
        textPoint.setY(fontMetrics.ascent());
        painter.setFont(font);
        painter.setPen(textColor);
        painter.drawText(textPoint, text);
    }
};

void WaveformMarkLabel::draw(QPainter* pPainter) {
    pPainter->drawPixmap(m_areaRect.topLeft(), m_pixmap);
}
