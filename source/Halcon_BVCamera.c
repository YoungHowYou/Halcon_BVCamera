#include "Halcon_BVCamera.h"

#pragma region BVCameraExpert

Herror CHBVCamStartGrab(Hproc_handle proc_handle)
{

	return HBVCamStartGrab(proc_handle);
}
Herror CHBVCamStopGrab(Hproc_handle proc_handle)
{

	return HBVCamStopGrab(proc_handle);
}

Herror CHBVCAM_FeatureCommand(Hproc_handle proc_handle)
{
	return HBVCAM_FeatureCommand(proc_handle);
}
Herror CHBVCAM_SetFeatureFloat(Hproc_handle proc_handle)
{
	return HBVCAM_SetFeatureFloat(proc_handle);
}

Herror CHBVCAM_SetFeatureInteger(Hproc_handle proc_handle)
{
	return HBVCAM_SetFeatureInteger(proc_handle);
}
Herror CHBVCamOpenByUID(Hproc_handle proc_handle)
{
	return HBVCamOpenByUID(proc_handle);
}

#pragma endregion
