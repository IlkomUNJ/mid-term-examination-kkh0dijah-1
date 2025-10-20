#include "drawingcanvas.h"
#include <QDebug>
#include <iostream>

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection() {

    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    std::cout << "image width " << image.width() << std::endl;
    std::cout << "image height " << image.height() << std::endl;


    std::vector<CustomMatrix> windows;
    windows.reserve(image.width() * image.height());
U
    int windowRadius = 3;
    int windowSize = windowRadius * 2 + 1; // Saat ini 7x7

    const int MAX_DUMP_SAMPLES = 5;
    int dumpCounter = 0;

    for (int i = windowRadius; i < image.width() - windowRadius; i++) {
        for (int j = windowRadius; j < image.height() - windowRadius; j++) {

            bool local_window[7][7] = {false};

            for (int m = -windowRadius; m <= windowRadius; m++) {
                for (int n = -windowRadius; n <= windowRadius; n++) {
                    QRgb rgbValue = image.pixel(i + m, j + n);
                    local_window[m + windowRadius][n + windowRadius] = (rgbValue != 0xffffffff);
                }
            }

            CustomMatrix mat(local_window);

            if (mat.isNonEmpty()) {
                windows.push_back(mat);

                if (dumpCounter < MAX_DUMP_SAMPLES) {
                    std::cout << "--- Pattern (" << windowSize << "x" << windowSize
                              << ") at Center (" << i << "," << j << ") ---" << std::endl;
                    mat.dump();
                    dumpCounter++;
                }
            }
        }
    }

    std::cout << "Total non-empty windows collected: " << windows.size() << std::endl;
    if (windows.size() > MAX_DUMP_SAMPLES) {
    }
    return;
}


void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4); // 4-pixel wide line
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        // Set the painter's pen to our custom pen.
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            //cout << m_points[i].x() << endl;
            painter.drawLine(m_points[i], m_points[i+1]);
        }
        isPaintLinesClicked = false;

        //return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


