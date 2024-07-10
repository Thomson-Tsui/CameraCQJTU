#ifndef _HK_IR_HEADER_
#define _HK_IR_HEADER_

#include "hk_common.h"

#if defined(_WIN32) || defined(_WIN64)

#define HK_IR_API  bool __stdcall

#else
#define HK_IR_API bool
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//<  error or is not national grid image, return false; otherwise, return true
HK_IR_API hk_ir_is_national_grid_image(const char *sz_file_name);

HK_IR_API hk_ir_append_temperature_to_national_grid_file(HKHANDLE h, const char *sz_file_name,
                                           unsigned char *pc_label_data, unsigned int ui_label_bytes);
HK_IR_API hk_ir_append_temperature_to_national_grid_file_ex(HKHANDLE h, const char *sz_file_name,
                                           double f_longitude, double f_latitude, int i_altitude,
                                           unsigned char *pc_label_data, unsigned int ui_label_bytes);
HK_IR_API hk_ir_append_temperature_to_file(HKHANDLE h, const char *sz_file_name,
                                           unsigned char *pc_label_data, unsigned int ui_label_bytes,
                                           unsigned char *pc_sound_data, unsigned int ui_sound_bytes,
                                           unsigned char *pc_user_data, unsigned int ui_user_bytes);
HK_IR_API hk_ir_get_temperature_snap_buffer(HKHANDLE h, unsigned int ui_temperature_data_start_offset,
                                            unsigned char *pc_label_data, unsigned int ui_label_bytes,
                                            unsigned char *pc_sound_data, unsigned int ui_sound_bytes,
                                            unsigned char *pc_user_data, unsigned int ui_user_bytes,
                                            unsigned char *pc_buf, unsigned int *pui_buf_length);

HK_IR_API hk_ir_enable_super_resolution(HKHANDLE h, bool b_enable);
HK_IR_API hk_ir_start_record(HKHANDLE h, const char *sz_file_name, PHKHANDLE ph_record);
HK_IR_API hk_ir_record_one_frame(HKHANDLE h, HKHANDLE h_record, unsigned short us_mark_bytes, void *p_mark_info);
HK_IR_API hk_ir_stop_record(HKHANDLE h, PHKHANDLE ph_record, unsigned int ui_user_data_bytes, void *p_user_data);
HK_IR_API hk_ir_get_record_file_length(HKHANDLE h, HKHANDLE ph_record, unsigned short *pui_len);

HK_IR_API hk_ir_get_resolution(HKHANDLE h, unsigned short *pus_width, unsigned short *pus_height);

HK_IR_API hk_ir_get_mac_info(HKHANDLE h, char *sz_productor, char *sz_mac_type, char *sz_mac_sn, char *sz_detector_sn, char *sz_product_date_time);

HK_IR_API hk_ir_get_supported_lens_info(HKHANDLE h, P_S_LEN_INFO p_lens_info, unsigned char *pc_lens_count);
HK_IR_API hk_ir_get_cur_len_range_info(HKHANDLE h, P_S_LEN_INFO p_len_info);

HK_IR_API hk_ir_set_emiss(HKHANDLE h, float ft);
HK_IR_API hk_ir_set_dist(HKHANDLE h, float ft);
HK_IR_API hk_ir_set_env_temp(HKHANDLE h, float ft);
HK_IR_API hk_ir_set_rel_hum(HKHANDLE h, float ft);
HK_IR_API hk_ir_set_modify_temp(HKHANDLE h, float ft);
HK_IR_API hk_ir_set_temperature_unit(HKHANDLE h, TemperatureUnit unit);
HK_IR_API hk_ir_set_enviroment_reference_temperature(HKHANDLE h, float f_enviroment_reference_temperature);
HK_IR_API hk_ir_set_temperature_para(HKHANDLE h, TemperatureUnit unit, float f_emiss, float f_dist, float f_env_temp, float f_rel_hum,
                                     float f_modify_temp, float f_reference_temperature);

HK_IR_API hk_ir_get_temperature_para(HKHANDLE h, TemperatureUnit *p_unit, float *pf_emiss, float *pf_dist, float *pf_env_temp, float *pf_rel_hum,
                                     float *pf_modify_temp, float *pf_reference_temperature);

HK_IR_API hk_ir_get_temperature_from_ad(HKHANDLE h, unsigned short *pus_ad, unsigned int ui_ad_count, float *pf_temp);
HK_IR_API hk_ir_get_temperature_from_ad_ex(HKHANDLE h, unsigned short *pus_ad, unsigned int ui_ad_count, float f_emiss, float f_dist, float *pf_temp);
HK_IR_API hk_ir_get_temperature_from_position(HKHANDLE h, unsigned short us_x, unsigned short us_y, float *pf_temp);
HK_IR_API hk_ir_get_temperature_from_position_ex(HKHANDLE h, unsigned short us_x, unsigned short us_y, float f_emiss, float f_dist, float *pf_temp);
HK_IR_API hk_ir_get_all_pixel_temperature(HKHANDLE h, float *pf_temp);
HK_IR_API hk_ir_get_ad_from_temperature(HKHANDLE h, float f_temp, unsigned short *pus_ad);
HK_IR_API hk_ir_get_temperature_and_ad_from_position(HKHANDLE h, unsigned short us_x, unsigned short us_y, unsigned short *pus_ad, float *pf_temp);

//< interface about temperature, bits and anas
HK_IR_API hk_ir_get_max_temperature(HKHANDLE h, P_S_MAX_AD p_max_ad, float *pf_temp);
HK_IR_API hk_ir_get_max_temperature_ex(HKHANDLE h, unsigned short *pus_x, unsigned short *pus_y, unsigned short *pus_max_ad, float *pf_temp);
HK_IR_API hk_ir_get_min_temperature(HKHANDLE h, P_S_MIN_AD p_min_ad, float *pf_temp);
HK_IR_API hk_ir_get_min_temperature_ex(HKHANDLE h, unsigned short *pus_x, unsigned short *pus_y, unsigned short *pus_min_ad, float *pf_temp);
HK_IR_API hk_ir_get_avg_temperature(HKHANDLE h, unsigned short *pus_avg, float *pf_temp);
HK_IR_API hk_ir_get_clr_index(HKHANDLE h, unsigned char *pby_clr_index);
HK_IR_API hk_ir_get_bits_by_clr_index(HKHANDLE h, unsigned char *pby_clr_index, unsigned char *pby_bits);
HK_IR_API hk_ir_get_bits(HKHANDLE h, unsigned char *pby_bits);
HK_IR_API hk_ir_get_bits_ex(HKHANDLE h, unsigned char *pby_bits, unsigned short us_width, unsigned short us_height,
                          unsigned short us_left, unsigned short us_top, unsigned short us_right, unsigned short us_bottom);

HK_IR_API hk_ir_set_palette(HKHANDLE h, PALETTE pi);
HK_IR_API hk_ir_get_palette(HKHANDLE h, PALETTE *p_pi);
HK_IR_API hk_ir_auto_imaging(HKHANDLE h);
HK_IR_API hk_ir_set_imaging_range(HKHANDLE h, unsigned short us_low, unsigned short us_high);
HK_IR_API hk_ir_get_imaging_range(HKHANDLE h, unsigned short *pus_low, unsigned short *pus_high);
HK_IR_API hk_ir_set_low_of_imaging_range(HKHANDLE h, unsigned short us_low);
HK_IR_API hk_ir_set_high_of_imaging_range(HKHANDLE h, unsigned short us_low);
HK_IR_API hk_ir_enable_image_process(HKHANDLE h, bool b_enable);
HK_IR_API hk_ir_enable_image_stabilization(HKHANDLE h);
HK_IR_API hk_ir_disable_image_stabilization(HKHANDLE h);
HK_IR_API hk_ir_set_imaging_algorithm_mode(HKHANDLE h, ImagingAlgorithmMode imaging_algorithm_mode);
HK_IR_API hk_ir_get_imaging_algorithm_mode(HKHANDLE h, ImagingAlgorithmMode* p_imaging_algorithm_mode);

HK_IR_API hk_ir_add_isotherm(HKHANDLE h, float f_low, float f_high, unsigned int ui_clr, bool b_transparent, PHKHANDLE ph_isotherm);
HK_IR_API hk_ir_delete_isotherm(HKHANDLE h, HKHANDLE h_isotherm);
HK_IR_API hk_ir_delete_all_isotherm(HKHANDLE h);
HK_IR_API hk_ir_update_isotherm(HKHANDLE h, HKHANDLE h_isotherm, float f_low, float f_high, unsigned int ui_clr, bool b_transparent);
HK_IR_API hk_ir_get_isotherm_count(HKHANDLE h, unsigned char *pc_count);
HK_IR_API hk_ir_get_isotherm(HKHANDLE h, unsigned char c_index, PHKHANDLE ph_isotherm,
                             float *pf_low, float *pf_high, unsigned int *pui_clr, bool *pb_transparent);

HK_IR_API hk_ir_set_zoom_factor(HKHANDLE h, ImageZoomFactor zoom_factor);
HK_IR_API hk_ir_get_zoom_factor(HKHANDLE h, ImageZoomFactor *p_zoom_factor);
HK_IR_API hk_ir_set_rotation_angle(HKHANDLE h, RotationAngle angle);
HK_IR_API hk_ir_get_rotation_angle(HKHANDLE h, RotationAngle *p_angle);

//< ana
HK_IR_API hk_ir_add_anas(HKHANDLE h, const char *sz_anas);
HK_IR_API hk_ir_update_ana_size(HKHANDLE h, const char *sz_old, const char *sz_new);
HK_IR_API hk_ir_update_ana_size_ex(HKHANDLE h, const char *sz_ana, const S_POINT *p_nodes, int i_nodes_count);
HK_IR_API hk_ir_delete_anas(HKHANDLE h, const char *sz_anas);
HK_IR_API hk_ir_delete_all_ana(HKHANDLE h);
HK_IR_API hk_ir_get_str_of_anas(HKHANDLE h, AnaType ana_type, char *sz_anas, unsigned int *pui_anas_bytes);
HK_IR_API hk_ir_get_ana_count(HKHANDLE h, AnaType ana_type, unsigned int *pui_count);

HK_IR_API hk_ir_get_hit_ana(HKHANDLE h, unsigned short us_x, unsigned short us_y, AnaType *p_ana_type, char *sz_ana, unsigned int *pui_ana_bytes);
HK_IR_API hk_ir_set_hit_range(HKHANDLE h, AnaType ana_type, unsigned char c_hit_range);

HK_IR_API hk_ir_ana_get_nodes(HKHANDLE h, const char *sz_ana, unsigned int *pui_nodes_count, S_POINT *p_nodes);
HK_IR_API hk_ir_ana_get_pixel_count(HKHANDLE h, const char *sz_ana, unsigned int *pui_count);
HK_IR_API hk_ir_ana_get_temperature(HKHANDLE h, const char *sz_ana, unsigned int *pui_count, float *pf_temp);

HK_IR_API hk_ir_get_rect_temperature(HKHANDLE h, unsigned short us_left, unsigned short us_top,
                                    unsigned short us_right, unsigned short us_bottom,
                                    P_S_MAX_AD p_max_ad, float *pf_max_temp,
                                    P_S_MIN_AD p_min_ad, float *pf_min_temp,
                                    unsigned short *pus_avg_ad, float *pf_avg_temp);
HK_IR_API hk_ir_get_rect_temperature_ex(HKHANDLE h, unsigned short us_left, unsigned short us_top,
                                    unsigned short us_right, unsigned short us_bottom,
                                    unsigned short *pus_max_x, unsigned short *pus_max_y,
                                    unsigned short *pus_max_ad, float *pf_max_temp,
                                    unsigned short *pus_min_x, unsigned short *pus_min_y,
                                    unsigned short *pus_min_ad, float *pf_min_temp,
                                    unsigned short *pus_avg_ad, float *pf_avg_temp);
HK_IR_API hk_ir_get_line_temperature(HKHANDLE h, unsigned short us_start_x, unsigned short us_start_y,
                                     unsigned short us_end_x, unsigned short us_end_y,
                                    P_S_MAX_AD p_max_ad, float *pf_max_temp,
                                    P_S_MIN_AD p_min_ad, float *pf_min_temp,
                                    unsigned short *pus_avg_ad, float *pf_avg_temp);
HK_IR_API hk_ir_get_line_temperature_ex(HKHANDLE h, unsigned short us_start_x, unsigned short us_start_y,
                                        unsigned short us_end_x, unsigned short us_end_y,
                                        unsigned short *pus_max_x, unsigned short *pus_max_y,
                                        unsigned short *pus_max_ad, float *pf_max_temp,
                                        unsigned short *pus_min_x, unsigned short *pus_min_y,
                                        unsigned short *pus_min_ad, float *pf_min_temp,
                                        unsigned short *pus_avg_ad, float *pf_avg_temp);
HK_IR_API hk_ir_ana_get_max_temperature(HKHANDLE h, const char *sz_ana, P_S_MAX_AD p_max_ad, float *pf_temp);
HK_IR_API hk_ir_ana_get_max_temperature_ex(HKHANDLE h, const char *sz_ana, unsigned short *pus_x, unsigned short *pus_y,
                                           unsigned short *pus_max_ad, float *pf_temp);
HK_IR_API hk_ir_ana_get_min_temperature(HKHANDLE h, const char *sz_ana, P_S_MIN_AD p_min_ad, float *pf_temp);
HK_IR_API hk_ir_ana_get_min_temperature_ex(HKHANDLE h, const char *sz_ana, unsigned short *pus_x, unsigned short *pus_y,
                                           unsigned short *pus_min_ad, float *pf_temp);
HK_IR_API hk_ir_ana_get_avg_temperature(HKHANDLE h, const char *sz_ana, unsigned short *pus_avg, float *pf_temp);

HK_IR_API hk_ir_ana_show_max_point(HKHANDLE h, const char *sz_ana, bool b_show);
HK_IR_API hk_ir_ana_show_min_point(HKHANDLE h, const char *sz_ana, bool b_show);
HK_IR_API hk_ir_ana_is_show_max_point(HKHANDLE h, const char *sz_ana, bool *pb_show);
HK_IR_API hk_ir_ana_is_show_min_point(HKHANDLE h, const char *sz_ana, bool *pb_show);
HK_IR_API hk_ir_ana_set_show_text_type(HKHANDLE h, const char *sz_ana, ShowTextType type);
HK_IR_API hk_ir_ana_get_show_text_type(HKHANDLE h, const char *sz_ana, ShowTextType *p_type);
HK_IR_API hk_ir_ana_set_text_location(HKHANDLE h, const char *sz_ana, AnaTextLocation location);
HK_IR_API hk_ir_ana_get_text_location(HKHANDLE h, const char *sz_ana, AnaTextLocation *p_location);

HK_IR_API hk_ir_ana_show_alias(HKHANDLE h, const char *sz_ana, bool b_show);
HK_IR_API hk_ir_ana_is_show_alias(HKHANDLE h, const char *sz_ana, bool *pb_show);
HK_IR_API hk_ir_ana_set_alias(HKHANDLE h, const char *sz_ana, const char *sz_alias);
HK_IR_API hk_ir_ana_get_alias(HKHANDLE h, const char *sz_ana, char *sz_alias, unsigned int *pui_alias_bytes);

HK_IR_API hk_ir_ana_set_visible(HKHANDLE h, const char *sz_ana, bool b_visible);
HK_IR_API hk_ir_ana_is_visible(HKHANDLE h, const char *sz_ana, bool *pb_visible);
HK_IR_API hk_ir_ana_set_can_move(HKHANDLE h, const char *sz_ana, bool b_move);
HK_IR_API hk_ir_ana_is_can_move(HKHANDLE h, const char *sz_ana, bool *pb_move);

HK_IR_API hk_ir_ana_show_des(HKHANDLE h, const char *sz_ana, bool b_show);
HK_IR_API hk_ir_ana_is_show_des(HKHANDLE h, const char *sz_ana, bool *pb_show);
HK_IR_API hk_ir_ana_set_des(HKHANDLE h, const char *sz_ana, const char *sz_des);
HK_IR_API hk_ir_ana_get_des(HKHANDLE h, const char *sz_ana, char *sz_des, unsigned int *pui_des_bytes);

HK_IR_API hk_ir_ana_set_line_color(HKHANDLE h, const char *sz_ana, unsigned int ui_color);
HK_IR_API hk_ir_ana_get_line_color(HKHANDLE h, const char *sz_ana, unsigned int *pui_color);

HK_IR_API hk_ir_ana_set_self_para(HKHANDLE h, const char *sz_ana, bool b_self_para, float f_emiss, float f_dist);
HK_IR_API hk_ir_ana_get_self_para(HKHANDLE h, const char *sz_ana, bool *pb_self_para, float *pf_emiss, float *pf_dist);

HK_IR_API hk_ir_ana_show_cursor(HKHANDLE h, const char *sz_ana, bool b_show);
HK_IR_API hk_ir_ana_show_temp_of_cursor(HKHANDLE h, const char *sz_ana, bool b_show);
HK_IR_API hk_ir_ana_set_scale_of_cursor(HKHANDLE h, const char *sz_ana, float f_scale);
HK_IR_API hk_ir_get_cursor_info(HKHANDLE h, const char *sz_ana, bool *p_show_cursor, bool *p_show_temp_of_cursor,
                                 float *pf_scale, unsigned short *pus_x, unsigned short *pus_y, float *pf_temp);

HK_IR_API hk_ir_ana_apply_self_palette(HKHANDLE h, const char *sz_ana, bool b_apply);
HK_IR_API hk_ir_ana_is_use_self_palette(HKHANDLE h, const char *sz_ana, bool *pb_apply);
HK_IR_API hk_ir_ana_set_palette(HKHANDLE h, const char *sz_ana, PALETTE pi);
HK_IR_API hk_ir_ana_auto_imaging(HKHANDLE h, const char *sz_ana);
HK_IR_API hk_ir_ana_set_imaging_range(HKHANDLE h, const char *sz_ana, unsigned short us_low, unsigned short us_high);
HK_IR_API hk_ir_ana_set_low_of_imaging_range(HKHANDLE h, const char *sz_ana, unsigned short us_low);
HK_IR_API hk_ir_ana_set_high_of_imaging_range(HKHANDLE h, const char *sz_ana, unsigned short us_high);
HK_IR_API hk_ir_ana_get_palette(HKHANDLE h, const char *sz_ana, PALETTE *p_palette);
HK_IR_API hk_ir_ana_get_imaging_range(HKHANDLE h, const char *sz_ana, unsigned short *pus_low, unsigned short *pus_high);

HK_IR_API hk_ir_repair_pt(HKHANDLE h, unsigned short us_x, unsigned short us_y, unsigned short us_ad);
HK_IR_API hk_ir_reapply(HKHANDLE h);

HK_IR_API hk_ir_compare_count_of_temperature(HKHANDLE h, unsigned short us_left, unsigned short us_top,
                                          unsigned short us_right, unsigned short us_bottom,
                                          RelationType rel_type, float f_threshode_temp,
                                          unsigned int ui_pixel_count, bool *pb_result);

#ifdef __cplusplus
}
#endif

#endif //< _HK_IR_HEADER_
