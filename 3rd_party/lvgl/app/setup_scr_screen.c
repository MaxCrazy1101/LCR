/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
// #include "custom.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	if (style_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_main_default);
	else
		lv_style_init(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_text
	ui->screen_main_text = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_main_text, 50, 64);
	lv_obj_set_size(ui->screen_main_text, 147, 35);
	lv_obj_set_scrollbar_mode(ui->screen_main_text, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_main_text, "测试测试你好呀");
	lv_label_set_long_mode(ui->screen_main_text, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_text_main_main_default
	static lv_style_t style_screen_main_text_main_main_default;
	if (style_screen_main_text_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_text_main_main_default);
	else
		lv_style_init(&style_screen_main_text_main_main_default);
	lv_style_set_radius(&style_screen_main_text_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_text_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_main_text_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_main_text_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_main_text_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_main_text_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_main_text_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_main_text_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_main_text_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_main_text_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_main_text_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_text_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_main_text_main_main_default, &lv_font_montserratMedium_16);
	lv_style_set_text_letter_space(&style_screen_main_text_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_main_text_main_main_default, 0);
	lv_style_set_text_align(&style_screen_main_text_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_main_text_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_text_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_text_main_main_default, 8);
	lv_style_set_pad_bottom(&style_screen_main_text_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_text, &style_screen_main_text_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_battery_bar
	ui->screen_battery_bar = lv_bar_create(ui->screen);
	lv_obj_set_pos(ui->screen_battery_bar, 178, 3);
	lv_obj_set_size(ui->screen_battery_bar, 57, 16);
	lv_obj_set_scrollbar_mode(ui->screen_battery_bar, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_battery_bar_main_main_default
	static lv_style_t style_screen_battery_bar_main_main_default;
	if (style_screen_battery_bar_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_battery_bar_main_main_default);
	else
		lv_style_init(&style_screen_battery_bar_main_main_default);
	lv_style_set_radius(&style_screen_battery_bar_main_main_default, 10);
	lv_style_set_bg_color(&style_screen_battery_bar_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_battery_bar_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_battery_bar_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_battery_bar_main_main_default, 60);
	lv_style_set_shadow_width(&style_screen_battery_bar_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_battery_bar_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_battery_bar_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_battery_bar_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_battery_bar_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_battery_bar_main_main_default, 0);
	lv_obj_add_style(ui->screen_battery_bar, &style_screen_battery_bar_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_battery_bar_main_indicator_default
	static lv_style_t style_screen_battery_bar_main_indicator_default;
	if (style_screen_battery_bar_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_screen_battery_bar_main_indicator_default);
	else
		lv_style_init(&style_screen_battery_bar_main_indicator_default);
	lv_style_set_radius(&style_screen_battery_bar_main_indicator_default, 10);
	lv_style_set_bg_color(&style_screen_battery_bar_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_battery_bar_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_battery_bar_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_battery_bar_main_indicator_default, 255);
	lv_obj_add_style(ui->screen_battery_bar, &style_screen_battery_bar_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_anim_time(ui->screen_battery_bar, 1000, 0);
	lv_bar_set_mode(ui->screen_battery_bar, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_battery_bar, 50, LV_ANIM_OFF);

	//Write codes screen_spangroup_1
	ui->screen_spangroup_1 = lv_spangroup_create(ui->screen);
	lv_obj_set_pos(ui->screen_spangroup_1, 20, 122);
	lv_obj_set_size(ui->screen_spangroup_1, 200, 100);
	lv_obj_set_scrollbar_mode(ui->screen_spangroup_1, LV_SCROLLBAR_MODE_OFF);
	lv_spangroup_set_align(ui->screen_spangroup_1, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_1, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_1, LV_SPAN_MODE_BREAK);

	//Write style state: LV_STATE_DEFAULT for style_screen_spangroup_1_main_main_default
	static lv_style_t style_screen_spangroup_1_main_main_default;
	if (style_screen_spangroup_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_spangroup_1_main_main_default);
	else
		lv_style_init(&style_screen_spangroup_1_main_main_default);
	lv_style_set_radius(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_spangroup_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_spangroup_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_spangroup_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_spangroup_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_spangroup_1_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_border_color(&style_screen_spangroup_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_spangroup_1_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_1, &style_screen_spangroup_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//create spans
	lv_span_t *screen_spangroup_1_span;

	//create a new span
	screen_spangroup_1_span = lv_spangroup_new_span(ui->screen_spangroup_1);
	lv_span_set_text(screen_spangroup_1_span, "fc=   ");
	lv_style_set_text_color(&screen_spangroup_1_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&screen_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_1_span->style, &lv_font_montserratMedium_12);

	//create a new span
	screen_spangroup_1_span = lv_spangroup_new_span(ui->screen_spangroup_1);
	lv_span_set_text(screen_spangroup_1_span, "hello");
	lv_style_set_text_color(&screen_spangroup_1_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&screen_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_1_span->style, &lv_font_simsun_12);

	//create a new span
	screen_spangroup_1_span = lv_spangroup_new_span(ui->screen_spangroup_1);
	lv_span_set_text(screen_spangroup_1_span, "  KHz");
	lv_style_set_text_color(&screen_spangroup_1_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&screen_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_1_span->style, &lv_font_simsun_12);
	lv_spangroup_refr_mode(ui->screen_spangroup_1);

	//Write codes screen_label_2
	ui->screen_label_2 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_2, 260, 297);
	lv_obj_set_size(ui->screen_label_2, 100, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_2, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_2, "Label");
	lv_label_set_long_mode(ui->screen_label_2, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_2_main_main_default
	static lv_style_t style_screen_label_2_main_main_default;
	if (style_screen_label_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_label_2_main_main_default);
	else
		lv_style_init(&style_screen_label_2_main_main_default);
	lv_style_set_radius(&style_screen_label_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_label_2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_label_2_main_main_default, 255);
	lv_style_set_shadow_width(&style_screen_label_2_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_label_2_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_label_2_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_label_2_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_label_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_label_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_label_2_main_main_default, &lv_font_montserratMedium_16);
	lv_style_set_text_letter_space(&style_screen_label_2_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_label_2_main_main_default, 0);
	lv_style_set_text_align(&style_screen_label_2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_label_2_main_main_default, 8);
	lv_style_set_pad_bottom(&style_screen_label_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_label_2, &style_screen_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label_3
	ui->screen_label_3 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_3, 50, 156);
	lv_obj_set_size(ui->screen_label_3, 100, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_3, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_3, "Label");
	lv_label_set_long_mode(ui->screen_label_3, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_3_main_main_default
	static lv_style_t style_screen_label_3_main_main_default;
	if (style_screen_label_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_label_3_main_main_default);
	else
		lv_style_init(&style_screen_label_3_main_main_default);
	lv_style_set_radius(&style_screen_label_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_label_3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_label_3_main_main_default, 255);
	lv_style_set_shadow_width(&style_screen_label_3_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_label_3_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_label_3_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_label_3_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_label_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_label_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_label_3_main_main_default, &lv_font_montserratMedium_16);
	lv_style_set_text_letter_space(&style_screen_label_3_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_label_3_main_main_default, 0);
	lv_style_set_text_align(&style_screen_label_3_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_label_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_label_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_label_3_main_main_default, 8);
	lv_style_set_pad_bottom(&style_screen_label_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_label_3, &style_screen_label_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_battery_text
	ui->screen_battery_text = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_battery_text, 137, 0);
	lv_obj_set_size(ui->screen_battery_text, 41, 19);
	lv_obj_set_scrollbar_mode(ui->screen_battery_text, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_battery_text, "100%");
	lv_label_set_long_mode(ui->screen_battery_text, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_battery_text_main_main_default
	static lv_style_t style_screen_battery_text_main_main_default;
	if (style_screen_battery_text_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_battery_text_main_main_default);
	else
		lv_style_init(&style_screen_battery_text_main_main_default);
	lv_style_set_radius(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_battery_text_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_battery_text_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_battery_text_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_battery_text_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_battery_text_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_text_color(&style_screen_battery_text_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_battery_text_main_main_default, &lv_font_montserratMedium_10);
	lv_style_set_text_letter_space(&style_screen_battery_text_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_text_align(&style_screen_battery_text_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_battery_text_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_battery_text_main_main_default, 8);
	lv_style_set_pad_bottom(&style_screen_battery_text_main_main_default, 0);
	lv_obj_add_style(ui->screen_battery_text, &style_screen_battery_text_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_vref
	ui->screen_vref = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_vref, 3, 0);
	lv_obj_set_size(ui->screen_vref, 41, 19);
	lv_obj_set_scrollbar_mode(ui->screen_vref, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_vref, "1.8V");
	lv_label_set_long_mode(ui->screen_vref, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_vref_main_main_default
	static lv_style_t style_screen_vref_main_main_default;
	if (style_screen_vref_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_vref_main_main_default);
	else
		lv_style_init(&style_screen_vref_main_main_default);
	lv_style_set_radius(&style_screen_vref_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_vref_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_vref_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_vref_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_vref_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_vref_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_vref_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_vref_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_vref_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_vref_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_vref_main_main_default, 0);
	lv_style_set_text_color(&style_screen_vref_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_vref_main_main_default, &lv_font_montserratMedium_10);
	lv_style_set_text_letter_space(&style_screen_vref_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_vref_main_main_default, 0);
	lv_style_set_text_align(&style_screen_vref_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_vref_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_vref_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_vref_main_main_default, 8);
	lv_style_set_pad_bottom(&style_screen_vref_main_main_default, 0);
	lv_obj_add_style(ui->screen_vref, &style_screen_vref_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_temperature
	ui->screen_temperature = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_temperature, 80, 0);
	lv_obj_set_size(ui->screen_temperature, 41, 19);
	lv_obj_set_scrollbar_mode(ui->screen_temperature, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_temperature, "18℃");
	lv_label_set_long_mode(ui->screen_temperature, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_temperature_main_main_default
	static lv_style_t style_screen_temperature_main_main_default;
	if (style_screen_temperature_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_temperature_main_main_default);
	else
		lv_style_init(&style_screen_temperature_main_main_default);
	lv_style_set_radius(&style_screen_temperature_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_temperature_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_temperature_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_temperature_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_temperature_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_temperature_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_temperature_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_temperature_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_temperature_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_temperature_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_temperature_main_main_default, 0);
	lv_style_set_text_color(&style_screen_temperature_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_temperature_main_main_default, &lv_font_montserratMedium_10);
	lv_style_set_text_letter_space(&style_screen_temperature_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_temperature_main_main_default, 0);
	lv_style_set_text_align(&style_screen_temperature_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_temperature_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_temperature_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_temperature_main_main_default, 8);
	lv_style_set_pad_bottom(&style_screen_temperature_main_main_default, 0);
	lv_obj_add_style(ui->screen_temperature, &style_screen_temperature_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}