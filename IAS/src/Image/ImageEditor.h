#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "CommLinkMonitor.h"
#include "CropCommandReq.h"
#include <opencv2/tracking.hpp>
#include "ImageProperties.h"
#include <QObject>
#include <QVector>

struct Points {
  int cooor_x_prov = 0;
    int cooor_y_prov = 0;
};

class ImageEditor : public QObject
{
private:
    static Points points_iterator;
    static cv::Mat m_originalImage;
    static cv::Mat m_showedImage;
    static bool m_flag;
    static int m_pointerX;
    static int m_pointerY;
    static QVector <Points> m_points;
    static void onMouse(int event, int x, int y, int flags, void* userdata);
    static void scroll(int x, int y);

public:
    static QList<ROI> selectROI(QString name);
    static QList<ImageProperties> cropImage(quint16 imageId, QString name, QList<ROI> roiList, QString imagePath);
    static int cropImage(QString imgFile, ROI roi, QString cropImgFile, QString extension);
};

#endif // IMAGEEDITOR_H
