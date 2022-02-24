#ifndef IMAGEHQREQUESTCOMMAND_H
#define IMAGEHQREQUESTCOMMAND_H

#include "Command.h"
#include <QString>

class ImageHQCommandReq : public Command
{
private:
    unsigned short m_imageId;

public:
    ImageHQCommandReq(unsigned short imageId);
    CommandCode getCommandCode(void) override;
};

#endif // IMAGEHQREQUESTCOMMAND_H
