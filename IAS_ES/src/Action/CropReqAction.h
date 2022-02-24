#ifndef CROPREQACTION_H
#define CROPREQACTION_H

#include "Action.h"
#include "ImageManagerIAS.h"
#include "ROI.h"
#include "ImageEditor.h"

class CropReqAction : public Action
{
private:
   ImageManagerIAS *m_imageManagerIAS;
   quint16 m_imageId;
   QList<ROI> m_roiList;
public:
    CropReqAction(ImageManagerIAS *imageManagerIAS, quint16 imageId, QList<ROI> roiList);
    void execute(void) override;
};

#endif // CROPREQACTION_H
