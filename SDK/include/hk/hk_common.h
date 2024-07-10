#ifndef HK_COMMON_HEADER_
#define HK_COMMON_HEADER_

#include "hk_common_def.h"

#if defined(_WIN32) || defined(_WIN64)

#define HK_RET_API int __stdcall
#define HK_RET_API_BOOL bool __stdcall

#else
#define HK_RET_API int
#define HK_RET_API_BOOL bool
#endif

#ifdef __cplusplus
extern "C"
{
#endif
HK_RET_API hk_get_ad_from_temp_national_grid(float f_temp, unsigned short *pus_ad);
HK_RET_API hk_get_temp_from_ad_national_grid(unsigned short us_ad, float *pf_temp);
HK_RET_API hk_get_exe_path(char *sz_ret, int *pi_count);

HK_RET_API hk_lz77_compress(unsigned char *pc_src, unsigned int ui_src_len, unsigned char *pc_com, unsigned int *pui_com_len);
HK_RET_API hk_lz77_uncompress(unsigned char *pc_com, unsigned int ui_com_len, unsigned char *pc_dst, unsigned int *pui_dst_len);

HK_RET_API hk_high_low_compress(unsigned short *pus_src, unsigned int ui_src_pixel, unsigned short *pus_dst, unsigned int *pui_dst_size);
HK_RET_API hk_high_low_uncompress(unsigned int ui_com_bytes, unsigned char *pc_com, unsigned short* pus_dst, unsigned int ui_dst_pixel);

HK_RET_API hk_pt_hit_pt( unsigned short us_hit_x, unsigned short us_hit_y, unsigned short us_node_x, unsigned short us_node_y, unsigned char c_hit_range);
HK_RET_API hk_pt_hit_line(unsigned short us_hit_x, unsigned short us_hit_y,
    unsigned short us_start_x, unsigned short us_start_y, unsigned short us_end_x, unsigned short us_end_y, unsigned char c_hit_range);

HK_RET_API hk_calc_pts_in_line(S_POINT pt_start, S_POINT pt_end, S_POINT *p_arr_pts, int *pi_pts_count);
HK_RET_API hk_calc_lines_in_ellipse(S_POINT pt_left_top, S_POINT pt_right_bottom, P_S_LINE_TABLE p_arr_lines, int *pi_lines_count);
/**
    @brief 解析单个分析字符串中的顶点坐标

    @param str_ana 单个分析字符串，格式见p_format_ana_str描述
    @param vct_pts 返回字符串中顶点坐标

    @return 成功返回true，否则返回false
*/
HK_RET_API hk_parse_pts_from_ana_str(const char *sz_ana, S_POINT *p_arr_pts, int *pi_pts_count);
/**
    @brief 格式化单个分析字符串，根据类型对应的字符串格式如下
    点：P:10,10;-
    线：L:10,10;20,20;-
    圆：E:10,10;20,20;-
    框：R:10,10;20,20;-
    多边形：A:10,10;20,20;30,30;40,40;-
    折线：S:10,10;20,20;30,30;40,40;-

    @param ana_type 分析类型
    @param p_arr_pts 分析的顶点坐标数组
    @param i_pts_count 分析的顶点个数

    @return 成功格式化的单个分析字符串
*/
HK_RET_API hk_format_ana_str(AnaType ana_type, const S_POINT *p_arr_pts, int i_pts_count, char *sz_ret, int *pi_count);

/**
    @brief 格式化点字符串

    @param i_x, i_y 点的坐标

    @return 返回格式化的字符串，格式是"i_x,i_y;"，没有双引号
*/
HK_RET_API hk_format_point_str(int i_x, int i_y, char *sz_ret, int *pi_count);
/**
    @brief 格式化和解析单个分析索引字符串，根据类型对应的字符串格式如下
    点：P01
    线：L01
    圆：E01
    框：R01
    多边形：A01
    折线：S01

    @param ana_type 分析类型
    @param sz_ana 返回的分析索引字符串

    @return 成功返回true，否则返回false
*/
HK_RET_API hk_format_ana_index(AnaType ana_type, int i_index, char *sz_ret, int *pi_count);
HK_RET_API hk_parse_ana_index(const char *sz_ana, AnaType *p_ana_type, int *pi_index);

HK_RET_API hk_parse_ana_char_of_type(AnaType ana_type, char *pc_type);
HK_RET_API hk_parse_ana_type_of_char(char c_type, AnaType *p_ana_type);

HK_RET_API hk_parse_alias_of_ana_str(const char *sz_ana, char *sz_ret, int *pi_count);

HK_RET_API hk_msec_to_timeval(HKUINT64 i64_time, P_S_TimeVal p_time);
HK_RET_API hk_timeval_to_msec(S_TimeVal tv, HKUINT64 *p_msec);
/**
    @brief 从多个格式化分析字符串中，解析出单个分析字符串


    hk_parse_anas_count_of_anas_str：获取分析字符串的个数
    hk_get_first_ana_from_anas_str：获取第1个分析字符串
    hk_get_next_ana_from_anas_str：获取第2个分析字符串

    @param sz_anas 多个格式化分析字符串
    @param pi_anas_count 分析字符串的个数
    @param pi_loc_flag 获取第1个时，传出下个字符串的开始下标；获取下个分析字符串时是传入和传出参数

    @return 返回分析字符串

    @example
    char *sz_anas = "P:10,10;-P:20,20;-L:10,10;20,20;-L:30,30;40,40;-E:10,10;20,20;-R:10,10;20,20;-
                     A:10,10;20,20;30,30;40,40;-S:10,10;20,20;30,30;40,40;-"

    bool get_anas_from_anas_str(const string &str_anas, std::<vector> &vct_anas){
        int i_anas_count = 0, i_loc_flag = 0;
        if(HK_RET_OK != hk_parse_anas_count_of_anas_str(str_anas.c_str(), &i_anas_count)) return false;

        char sz[128];
        int i_count = 128;
        if(HK_RET_OK != hk_get_first_ana_from_anas_str(str_anas.c_str(), &i_loc_flag, sz, &i_count)) return false;
        do{
            vct_anas.push_back(sz); i_count = 128;
        }while(HK_RET_OK == hk_get_next_ana_from_anas_str(str_anas.c_str(), &i_loc_flag, sz, &i_count));
    }
*/
HK_RET_API hk_parse_anas_count_of_anas_str(const char *sz_anas, int *pi_anas_count);
HK_RET_API hk_get_first_ana_from_anas_str(const char *sz_anas, int *pi_loc_flag, char *sz_ret, int *pi_count);
HK_RET_API hk_get_next_ana_from_anas_str(const char *sz_anas, int *pi_loc_flag, char *sz_ret, int *pi_count);

//< calc formula
HK_RET_API_BOOL hk_calc_formula_init(PHKHANDLE p_h);
HK_RET_API_BOOL hk_calc_formula_uninit(PHKHANDLE p_h);

HK_RET_API_BOOL hk_calc_formula_bool(HKHANDLE h, const char *sz_formula, bool *pb_ret);
HK_RET_API_BOOL hk_calc_formula_float(HKHANDLE h, const char *sz_formula, float *pf_ret);


#ifdef __cplusplus
}
#endif

#endif //< HK_COMMON_HEADER_
