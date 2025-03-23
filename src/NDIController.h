#pragma once
#ifdef _WIN32
#ifdef _WIN64
#pragma comment(lib, "Processing.NDI.Lib.x64.lib")
#else // _WIN64
#pragma comment(lib, "Processing.NDI.Lib.x86.lib")
#endif // _WIN64
#endif // _WIN32
#include <Processing.NDI.Lib.h>

#include <vector>
#include "NDISource.h"



class NDIController
{

protected:
    bool _isAvailable;
    NDIlib_find_instance_t _pNDI_find;

public:
    NDIController();
    ~NDIController();
    bool initNDI();
    bool initFindNDI();
    std::vector<NDISource> findSrcNDI();
    std::vector<NDISource> AdapterSrcNDI(const NDIlib_source_t* p_sources, uint32_t no_sources);

};

