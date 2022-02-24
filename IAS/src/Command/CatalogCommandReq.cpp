#include "CatalogCommandReq.h"

CatalogCommandReq::CatalogCommandReq()
{

}

CommandCode CatalogCommandReq::getCommandCode()
{
    return CommandCode::CATALOG_REQ;
}
