# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=240,h=240)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(240*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 240
disp_drv.ver_res = 240
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)



# create screen
screen = lv.obj()
screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_main_main_default
style_screen_main_main_default = lv.style_t()
style_screen_main_main_default.init()
style_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_main_default.set_bg_opa(255)

# add style for screen
screen.add_style(style_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_main_text
screen_main_text = lv.label(screen)
screen_main_text.set_pos(int(50),int(64))
screen_main_text.set_size(147,35)
screen_main_text.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_text.set_text("测试测试你好呀")
screen_main_text.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_text_main_main_default
style_screen_main_text_main_main_default = lv.style_t()
style_screen_main_text_main_main_default.init()
style_screen_main_text_main_main_default.set_radius(0)
style_screen_main_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_text_main_main_default.set_bg_opa(0)
style_screen_main_text_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_main_text_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_main_text_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_main_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_text_main_main_default.set_text_letter_space(2)
style_screen_main_text_main_main_default.set_text_line_space(0)
style_screen_main_text_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_text_main_main_default.set_pad_left(0)
style_screen_main_text_main_main_default.set_pad_right(0)
style_screen_main_text_main_main_default.set_pad_top(8)
style_screen_main_text_main_main_default.set_pad_bottom(0)

# add style for screen_main_text
screen_main_text.add_style(style_screen_main_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_battery_bar
screen_battery_bar = lv.bar(screen)
screen_battery_bar.set_pos(int(178),int(3))
screen_battery_bar.set_size(57,16)
screen_battery_bar.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_battery_bar.set_style_anim_time(1000, 0)
screen_battery_bar.set_mode(lv.bar.MODE.NORMAL)
screen_battery_bar.set_value(50, lv.ANIM.OFF)
# create style style_screen_battery_bar_main_main_default
style_screen_battery_bar_main_main_default = lv.style_t()
style_screen_battery_bar_main_main_default.init()
style_screen_battery_bar_main_main_default.set_radius(10)
style_screen_battery_bar_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_battery_bar_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_battery_bar_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_battery_bar_main_main_default.set_bg_opa(60)

# add style for screen_battery_bar
screen_battery_bar.add_style(style_screen_battery_bar_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_battery_bar_main_indicator_default
style_screen_battery_bar_main_indicator_default = lv.style_t()
style_screen_battery_bar_main_indicator_default.init()
style_screen_battery_bar_main_indicator_default.set_radius(10)
style_screen_battery_bar_main_indicator_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_battery_bar_main_indicator_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_battery_bar_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_battery_bar_main_indicator_default.set_bg_opa(255)

# add style for screen_battery_bar
screen_battery_bar.add_style(style_screen_battery_bar_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)


# create screen_spangroup_1
screen_spangroup_1 = lv.spangroup(screen)
screen_spangroup_1.set_pos(int(20),int(122))
screen_spangroup_1.set_size(200,100)
screen_spangroup_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_spangroup_1.set_align(lv.TEXT_ALIGN.LEFT)
screen_spangroup_1.set_overflow(lv.SPAN_OVERFLOW.CLIP)
screen_spangroup_1.set_mode(lv.SPAN_MODE.BREAK)
screen_spangroup_1_span = screen_spangroup_1.new_span()
screen_spangroup_1_span.set_text("fc=   ")
screen_spangroup_1_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
screen_spangroup_1_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    screen_spangroup_1_span.style.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        screen_spangroup_1_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        screen_spangroup_1_span.style.set_text_font(lv.font_montserrat_16)
screen_spangroup_1_span = screen_spangroup_1.new_span()
screen_spangroup_1_span.set_text("hello")
screen_spangroup_1_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
screen_spangroup_1_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    screen_spangroup_1_span.style.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        screen_spangroup_1_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        screen_spangroup_1_span.style.set_text_font(lv.font_montserrat_16)
screen_spangroup_1_span = screen_spangroup_1.new_span()
screen_spangroup_1_span.set_text("  KHz")
screen_spangroup_1_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
screen_spangroup_1_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    screen_spangroup_1_span.style.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        screen_spangroup_1_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        screen_spangroup_1_span.style.set_text_font(lv.font_montserrat_16)
screen_spangroup_1.refr_mode()
# create style style_screen_spangroup_1_main_main_default
style_screen_spangroup_1_main_main_default = lv.style_t()
style_screen_spangroup_1_main_main_default.init()
style_screen_spangroup_1_main_main_default.set_radius(0)
style_screen_spangroup_1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_spangroup_1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_spangroup_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_spangroup_1_main_main_default.set_bg_opa(0)
style_screen_spangroup_1_main_main_default.set_border_color(lv.color_make(0x00,0x00,0x00))
style_screen_spangroup_1_main_main_default.set_border_width(0)
style_screen_spangroup_1_main_main_default.set_border_opa(255)
style_screen_spangroup_1_main_main_default.set_pad_left(0)
style_screen_spangroup_1_main_main_default.set_pad_right(0)
style_screen_spangroup_1_main_main_default.set_pad_top(0)
style_screen_spangroup_1_main_main_default.set_pad_bottom(0)

# add style for screen_spangroup_1
screen_spangroup_1.add_style(style_screen_spangroup_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_label_2
screen_label_2 = lv.label(screen)
screen_label_2.set_pos(int(260),int(297))
screen_label_2.set_size(100,32)
screen_label_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_label_2.set_text("Label")
screen_label_2.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_label_2_main_main_default
style_screen_label_2_main_main_default = lv.style_t()
style_screen_label_2_main_main_default.init()
style_screen_label_2_main_main_default.set_radius(0)
style_screen_label_2_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_2_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_label_2_main_main_default.set_bg_opa(255)
style_screen_label_2_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_label_2_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_label_2_main_main_default.set_text_letter_space(2)
style_screen_label_2_main_main_default.set_text_line_space(0)
style_screen_label_2_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_label_2_main_main_default.set_pad_left(0)
style_screen_label_2_main_main_default.set_pad_right(0)
style_screen_label_2_main_main_default.set_pad_top(8)
style_screen_label_2_main_main_default.set_pad_bottom(0)

# add style for screen_label_2
screen_label_2.add_style(style_screen_label_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_label_3
screen_label_3 = lv.label(screen)
screen_label_3.set_pos(int(50),int(156))
screen_label_3.set_size(100,32)
screen_label_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_label_3.set_text("Label")
screen_label_3.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_label_3_main_main_default
style_screen_label_3_main_main_default = lv.style_t()
style_screen_label_3_main_main_default.init()
style_screen_label_3_main_main_default.set_radius(0)
style_screen_label_3_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_3_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_label_3_main_main_default.set_bg_opa(255)
style_screen_label_3_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_label_3_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_label_3_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_label_3_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_label_3_main_main_default.set_text_letter_space(2)
style_screen_label_3_main_main_default.set_text_line_space(0)
style_screen_label_3_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_label_3_main_main_default.set_pad_left(0)
style_screen_label_3_main_main_default.set_pad_right(0)
style_screen_label_3_main_main_default.set_pad_top(8)
style_screen_label_3_main_main_default.set_pad_bottom(0)

# add style for screen_label_3
screen_label_3.add_style(style_screen_label_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_battery_text
screen_battery_text = lv.label(screen)
screen_battery_text.set_pos(int(137),int(0))
screen_battery_text.set_size(41,19)
screen_battery_text.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_battery_text.set_text("100%")
screen_battery_text.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_battery_text_main_main_default
style_screen_battery_text_main_main_default = lv.style_t()
style_screen_battery_text_main_main_default.init()
style_screen_battery_text_main_main_default.set_radius(0)
style_screen_battery_text_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_battery_text_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_battery_text_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_battery_text_main_main_default.set_bg_opa(0)
style_screen_battery_text_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_battery_text_main_main_default.set_text_font(lv.font_montserratMedium_10)
except AttributeError:
    try:
        style_screen_battery_text_main_main_default.set_text_font(lv.font_montserrat_10)
    except AttributeError:
        style_screen_battery_text_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_battery_text_main_main_default.set_text_letter_space(2)
style_screen_battery_text_main_main_default.set_text_line_space(0)
style_screen_battery_text_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_battery_text_main_main_default.set_pad_left(0)
style_screen_battery_text_main_main_default.set_pad_right(0)
style_screen_battery_text_main_main_default.set_pad_top(8)
style_screen_battery_text_main_main_default.set_pad_bottom(0)

# add style for screen_battery_text
screen_battery_text.add_style(style_screen_battery_text_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_vref
screen_vref = lv.label(screen)
screen_vref.set_pos(int(3),int(0))
screen_vref.set_size(41,19)
screen_vref.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_vref.set_text("1.8V")
screen_vref.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_vref_main_main_default
style_screen_vref_main_main_default = lv.style_t()
style_screen_vref_main_main_default.init()
style_screen_vref_main_main_default.set_radius(0)
style_screen_vref_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_vref_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_vref_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_vref_main_main_default.set_bg_opa(0)
style_screen_vref_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_vref_main_main_default.set_text_font(lv.font_montserratMedium_10)
except AttributeError:
    try:
        style_screen_vref_main_main_default.set_text_font(lv.font_montserrat_10)
    except AttributeError:
        style_screen_vref_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_vref_main_main_default.set_text_letter_space(2)
style_screen_vref_main_main_default.set_text_line_space(0)
style_screen_vref_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_vref_main_main_default.set_pad_left(0)
style_screen_vref_main_main_default.set_pad_right(0)
style_screen_vref_main_main_default.set_pad_top(8)
style_screen_vref_main_main_default.set_pad_bottom(0)

# add style for screen_vref
screen_vref.add_style(style_screen_vref_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_temperature
screen_temperature = lv.label(screen)
screen_temperature.set_pos(int(80),int(0))
screen_temperature.set_size(41,19)
screen_temperature.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_temperature.set_text("18℃")
screen_temperature.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_temperature_main_main_default
style_screen_temperature_main_main_default = lv.style_t()
style_screen_temperature_main_main_default.init()
style_screen_temperature_main_main_default.set_radius(0)
style_screen_temperature_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_temperature_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_temperature_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_temperature_main_main_default.set_bg_opa(0)
style_screen_temperature_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_screen_temperature_main_main_default.set_text_font(lv.font_montserratMedium_10)
except AttributeError:
    try:
        style_screen_temperature_main_main_default.set_text_font(lv.font_montserrat_10)
    except AttributeError:
        style_screen_temperature_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_temperature_main_main_default.set_text_letter_space(2)
style_screen_temperature_main_main_default.set_text_line_space(0)
style_screen_temperature_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_temperature_main_main_default.set_pad_left(0)
style_screen_temperature_main_main_default.set_pad_right(0)
style_screen_temperature_main_main_default.set_pad_top(8)
style_screen_temperature_main_main_default.set_pad_bottom(0)

# add style for screen_temperature
screen_temperature.add_style(style_screen_temperature_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)




# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)
