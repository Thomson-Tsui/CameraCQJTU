#ifndef _HK_TEMPERATURE_STREAM_HEADER_
#define _HK_TEMPERATURE_STREAM_HEADER_

#include "hk_common_def.h"


#if defined(_WIN32) || defined(_WIN64)
#define HK_TS_API  bool __stdcall
#else
#define HK_TS_API bool
#endif

#ifdef __cplusplus
extern "C"
{
#endif

HK_TS_API hk_ts_is_valid_file(const char *sz_file_name);
//< default resolution of thumbnail is [image_width / 4, image_height / 4]
HK_TS_API hk_ts_get_thumbnail_bits(const char *sz_file_name, unsigned short *pus_thumbnail_width, unsigned short *pus_thumbnail_height,
                                         unsigned char *puc_bits);

HK_TS_API hk_ts_init(PHKHANDLE p_h);
HK_TS_API hk_ts_uninit(PHKHANDLE p_h);
HK_TS_API hk_ts_load_from_file(HKHANDLE h, const char *sz_file_name);
HK_TS_API hk_ts_seek_frame(HKHANDLE h, unsigned int ui_frame_no);
HK_TS_API hk_ts_seek_frame_ex(HKHANDLE h, const P_S_TimeVal p_time);

HK_TS_API hk_ts_get_version(HKHANDLE h, unsigned short *pus_version);
HK_TS_API hk_ts_get_start_time(HKHANDLE h, P_S_TimeVal p_time);
HK_TS_API hk_ts_get_end_time(HKHANDLE h, P_S_TimeVal p_time);
HK_TS_API hk_ts_get_time_of_frame(HKHANDLE h, unsigned int ui_frame_no, P_S_TimeVal p_time);
HK_TS_API hk_ts_get_total_frames(HKHANDLE h, unsigned int *pui_total_frames);

HK_TS_API hk_ts_get_marks_count(HKHANDLE h, unsigned int *pui_count);
HK_TS_API hk_ts_get_mark_info_with_index(HKHANDLE h, unsigned int ui_index, unsigned int *pui_frame_no,
    unsigned short *pus_mark_bytes, unsigned char *puc_mark_info);
HK_TS_API hk_ts_get_mark_info(HKHANDLE h, unsigned int ui_frame_no, unsigned short *pus_mark_bytes, unsigned char *puc_mark_info);
HK_TS_API hk_ts_add_mark_info(HKHANDLE h, unsigned int ui_frame_no, unsigned short us_mark_bytes, unsigned char *puc_mark_info);
HK_TS_API hk_ts_update_mark_info(HKHANDLE h, unsigned int ui_frame_no, unsigned short us_mark_bytes, unsigned char *puc_mark_info);
HK_TS_API hk_ts_delete_mark_info(HKHANDLE h, unsigned int ui_frame_no);
HK_TS_API hk_ts_delete_all_mark_info(HKHANDLE h);

HK_TS_API hk_ts_get_user_data(HKHANDLE h, unsigned int *pui_data_size, unsigned char *puc_data);
HK_TS_API hk_ts_update_user_data(HKHANDLE h, unsigned int ui_data_size, unsigned char *puc_data);
HK_TS_API hk_ts_delete_user_data(HKHANDLE h);

HK_TS_API hk_ts_apply_default_temperature_para(HKHANDLE h, bool b_apply);
HK_TS_API hk_ts_apply_default_imaging_para(HKHANDLE h, bool b_apply);

#ifdef __cplusplus
}
#endif

#endif //< _hk_ts_HEADER_
