#include "ImageEditor.h"
#include "Defines.h"
#include <cmath>
#include <QDebug>
#include <QList>
#include <QImage>
#include <QDateTime>
#include <fstream>
#include <QFile>

//  Resolution of the monitor screen. Adjust to the convenient resolution.
#define SCREEN_RES_X 1266 //1366, default Notebook
#define SCREEN_RES_Y 711  //768, default Notebook

Points ImageEditor::points_iterator{0,0};
cv::Mat ImageEditor::m_originalImage;
cv::Mat ImageEditor::m_showedImage;
bool ImageEditor::m_flag;
int ImageEditor::m_pointerX;
int ImageEditor::m_pointerY;
QVector <Points> ImageEditor::m_points;

QList<ROI> ImageEditor::selectROI(QString name)
{
    //qDebug() << "ImageEditor::selectROI(name = " << name << ")";
    QList<ROI> roiList;
    QString commandPath = "/home/tesis/Repos/TESIS_V2/res/";
    QString command = commandPath + "select_region " + name;
    system(command.toStdString().c_str());

    QString outputFile = name.replace("jpg", "cut");
    QFile file(outputFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return roiList;
    }

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString aux(line);
        QStringList aux2 = aux.split("\n");
        QStringList aux3 = aux2.at(0).split(",");
        if (aux3.count() < 4)
        {
            return roiList;
        }

        roiList.append(ROI{static_cast<quint16>(aux3.at(0).toShort()),
                           static_cast<quint16>(aux3.at(1).toShort()),
                           static_cast<quint16>(aux3.at(2).toShort()),
                           static_cast<quint16>(aux3.at(3).toShort())});
    }

    file.remove();

    return roiList;
}

QList<ImageProperties> ImageEditor::cropImage(quint16 imageId, QString filenameQS, QList<ROI> roiList, QString imagePath)
{
    QList<ImageProperties> list;
    //qDebug() << "ImageEditor::cropImage(filenameQS = " << filenameQS << ")";
    for (int i = 0; i < roiList.size(); i++)
    {
        ROI roi = roiList.at(i);
        //qDebug() << "ImageEditor::cropImage(roiList[" << i << "] = ROI(x = " << roi.x << ", y = " << roi.y << ", w = " << roi.width << ", h = " << roi.height << "))";
    }

    QString name;
    std::string filename = filenameQS.toStdString();

    cv::Mat img = cv::imread(filename);	//	Load the original image from file

    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    if (img.empty()) {
        //qDebug() << "Could not open the image";
    }

    for (int i = 0; i < roiList.size(); i++)
    {
        ROI roi = roiList.at(i);
        //	Final name for the cut image
        name = QString("%1%2%3%4%5%6").arg(imagePath).arg("CROP").arg(i).arg("_").arg(imageId).arg(HIGH_QUALITY_EXTENSION);
        //qDebug() << "ImageEditor::cropImage name = " << name;
        x = static_cast<int>(roi.x);
        y = static_cast<int>(roi.y);
        width = static_cast<int>(roi.width);
        height = static_cast<int>(roi.height);

        try {
            //	Cut and save the crop image
            imwrite(name.toStdString(), img(cv::Rect(x, y, width, height)));
            /* sACAR SIZE DE LA IMAGEN Y TIMESTAMP */
            QImage img(name.toStdString().c_str());
            list.append(ImageProperties(imageId, QString::number(img.sizeInBytes()), QString::number(img.width()), QString::number(img.height()), QDateTime::currentMSecsSinceEpoch()));
        }
        catch (std::runtime_error& ex) {
            fprintf(stderr, "Exception saving image: %s\n", ex.what());
        }
    }

    return list;
}

int ImageEditor::cropImage(QString imgFile, ROI roi, QString cropImgFile, QString extension)
{
    //qDebug() << "ImageEditor::cropImage(imgFile = " << imgFile << ", roi = (" << roi.x << ", " << roi.y << ", " << roi.width << ", " << roi.height << "), cropImgFile = " << cropImgFile;
    int size = 0;
    QImage image(imgFile);
    if (image.isNull())
    {
        return 0;
    }
    QImage newImage = image.copy(roi.x, roi.y, roi.width, roi.height);
    if (newImage.save(cropImgFile), extension.toUpper().toStdString().c_str())
    {
        size = newImage.sizeInBytes();
    }
    return size;
}
