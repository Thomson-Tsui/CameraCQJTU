#ifndef _HK_IMAGE_HEADER_
#define _HK_IMAGE_HEADER_

#include "hk_common.h"

#if defined(_WIN32) || defined(_WIN64)

#define HK_IMAGE_API  bool __stdcall
#else
#define HK_IMAGE_API bool
#endif

#ifdef __cplusplus
extern "C"
{
#endif

HK_IMAGE_API hk_image_is_valid_file(const char *sz_file_name);
HK_IMAGE_API hk_image_delete_temperature_data(const char *sz_file_name);
HK_IMAGE_API hk_image_get_user_data_ex(const char *sz_file_name, unsigned char *p_data, unsigned int *pui_data_size);

HK_IMAGE_API hk_image_init(PHKHANDLE p_h);
HK_IMAGE_API hk_image_uninit(PHKHANDLE p_h);
HK_IMAGE_API hk_image_load_from_file(HKHANDLE h, const char *sz_file_name);
HK_IMAGE_API hk_image_load_from_buffer(HKHANDLE h, unsigned char *p_data, unsigned int ui_data_len);

HK_IMAGE_API hk_image_get_storage_time(HKHANDLE h, char *sz_time);
HK_IMAGE_API hk_image_get_label_data(HKHANDLE h, unsigned char *p_data, unsigned int *pui_data_size);
HK_IMAGE_API hk_image_get_sound_data(HKHANDLE h, unsigned char *p_data, unsigned int *pui_data_size);
HK_IMAGE_API hk_image_get_user_data(HKHANDLE h, unsigned char *p_data, unsigned int *pui_data_size);

HK_IMAGE_API hk_image_apply_default_temperature_para(HKHANDLE h, bool b_apply);
HK_IMAGE_API hk_image_apply_default_imaging_para(HKHANDLE h, bool b_apply);
HK_IMAGE_API hk_image_add_default_isotherm(HKHANDLE h);
HK_IMAGE_API hk_image_add_default_anas(HKHANDLE h);
HK_IMAGE_API hk_image_remove_default_isotherm(HKHANDLE h);
HK_IMAGE_API hk_image_remove_default_anas(HKHANDLE h);

HK_IMAGE_API hk_image_get_default_anas(HKHANDLE h, char *sz_anas, unsigned int *pui_anas_bytes);
HK_IMAGE_API hk_image_get_default_zoom_factor(HKHANDLE h, ImageZoomFactor *p_image_zoom_factor);
HK_IMAGE_API hk_image_get_default_rotation_angle(HKHANDLE h, RotationAngle *p_rotation_angle);

#ifdef __cplusplus
}
#endif

#endif //< _HK_IMAGE_HEADER_
