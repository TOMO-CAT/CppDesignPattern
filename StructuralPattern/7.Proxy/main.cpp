#include "Client.h"
#include "Service.h"
#include "Proxy.h"

int main() {
    ThirdPartyTVClass* aTVService = new ThirdPartyTVClass();
    CachedTVClass* aTVProxy = new CachedTVClass(aTVService);
    TVManager* manager = new TVManager(aTVProxy);

    manager->renderVideoPage(1);
    manager->renderListPanel();

    delete aTVService;
    delete aTVProxy;
    delete manager;
}