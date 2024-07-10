#ifndef _HK_NATIONAL_GIRD_IMAGE_HEADER_
#define _HK_NATIONAL_GIRD_IMAGE_HEADER_

#include "hk_common.h"

#if defined(_WIN32) || defined(_WIN64)
#define HK_NG_IMAGE_API  bool __stdcall
#else
#define HK_NG_IMAGE_API bool
#endif

#ifdef __cplusplus
extern "C"
{
#endif

HK_NG_IMAGE_API hk_ng_image_is_valid_file(const char *sz_file_name);

HK_NG_IMAGE_API hk_ng_image_init(PHKHANDLE p_h);
HK_NG_IMAGE_API hk_ng_image_uninit(PHKHANDLE p_h);
HK_NG_IMAGE_API hk_ng_image_load_from_file(HKHANDLE h, const char *sz_file_name);
HK_NG_IMAGE_API hk_ng_image_load_from_buffer(HKHANDLE h, unsigned char *p_data, unsigned int ui_data_len);

HK_NG_IMAGE_API hk_ng_image_get_storage_time(HKHANDLE h, char *sz_time);
HK_NG_IMAGE_API hk_ng_image_get_label_data(HKHANDLE h, unsigned char *p_data, unsigned int *pui_data_size);

HK_NG_IMAGE_API hk_ng_image_get_gps_info(HKHANDLE h, double *pf_longitude, double *pf_latitude, int *pi_altitude);

#ifdef __cplusplus
}
#endif

#endif //< _HK_NATIONAL_GIRD_IMAGE_HEADER_
