#include "NDIController.h"
#include <iostream>
#include <vector>
#include "NDISource.h";


NDIController::NDIController()
{
	_isAvailable = false;
	_pNDI_find = NULL;
}

NDIController::~NDIController()
{
	if(_pNDI_find != NULL)
		NDIlib_find_destroy(_pNDI_find);

	// Finished
	NDIlib_destroy();
}


bool NDIController::initNDI() 
{
	_isAvailable =  NDIlib_initialize();
	return _isAvailable;

}

bool NDIController::initFindNDI() 
{
	if (_isAvailable) {
		_pNDI_find = NDIlib_find_create_v2(nullptr);
		if (_pNDI_find)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else
	{
		return _isAvailable;
	}
}

std::vector<NDISource> NDIController::findSrcNDI()
{
	std::vector<NDISource> sources;

	if (!NDIlib_find_wait_for_sources(_pNDI_find, 5000 /* milliseconds */)) {
		std::cout << "No change to the sources found.\n";
	}
	else
	{
		bool source_list_has_changed = NDIlib_find_wait_for_sources(_pNDI_find, 5500/* 2.5 seconds */);
		uint32_t no_sources = 0;
		const NDIlib_source_t* p_sources = NDIlib_find_get_current_sources(_pNDI_find, &no_sources);

		sources = AdapterSrcNDI(p_sources, no_sources);
	}

	return sources;




}


std::vector<NDISource>  NDIController::AdapterSrcNDI(const NDIlib_source_t *p_sources, uint32_t no_sources)
{
	std::vector<NDISource> sources ;

		// Display all the sources.
		printf("Network sources (%u found).\n", no_sources);
		for (uint32_t i = 0; i < no_sources; i++)
		{
			sources.push_back(NDISource(p_sources[i].p_ndi_name, p_sources[i].p_url_address));
			printf("%u. %s\n", i + 1, p_sources[i].p_ndi_name);
		}
		return sources;


}

