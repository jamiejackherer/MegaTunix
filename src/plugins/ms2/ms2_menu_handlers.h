/*
 * Copyright (C) 2003 by Dave J. Andruczyk <djandruczyk at yahoo dot com>
 *
 * Linux Megasquirt tuning software
 * 
 * 
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute, etc. this as long as all the source code
 * is made available for FREE.
 * 
 * No warranty is made or implied. You use this program at your own risk.
 */

#ifndef __MS2_MENU_HANDLERS_H__
#define __MS2_MENU_HANDLERS_H__

#include <defines.h>
#include <glade/glade.h>
#include <gtk/gtk.h>
#include <threads.h>

/* Externs */
extern GtkWidget *(*lookup_widget_f)(const gchar *);
extern void (*register_widget_f)(gchar *, GtkWidget *);
extern gboolean (*get_symbol_f)(const gchar *, void **);
extern void (*bind_to_lists_f)(GtkWidget * , gchar * );
extern void (*add_additional_rtt_f)(GtkWidget *);
extern void (*io_cmd_f)(const gchar *, void *);
/* Exnerns */

/* Prototypes */
void ecu_plugin_menu_setup(GladeXML *);
gboolean show_tps_calibrator_window(GtkWidget *, gpointer);
gboolean show_ms2_afr_calibrator_window(GtkWidget *, gpointer);
gboolean show_table_generator_window(GtkWidget *, gpointer);
gboolean show_sensor_calibration_help(GtkWidget *, gpointer);
gboolean ms2_reinit(GtkWidget *, gpointer);
gboolean ms2_reboot(GtkWidget *, gpointer);
/* Prototypes */

#endif
