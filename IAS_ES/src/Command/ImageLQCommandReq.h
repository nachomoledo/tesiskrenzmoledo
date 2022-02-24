#ifndef IMAGELQREQUESTCOMMAND_H
#define IMAGELQREQUESTCOMMAND_H

#include "Command.h"
#include <QString>

class ImageLQCommandReq : public Command
{
private:
    unsigned short m_imageId;

public:
    ImageLQCommandReq(unsigned short imageId);
    CommandCode getCommandCode(void) override;
};

#endif // IMAGELQREQUESTCOMMAND_H
