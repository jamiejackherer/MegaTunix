/*
 * Copyright (C) 2003 by Dave J. Andruczyk <djandruczyk at yahoo dot com>
 *
 * Linux Megasquirt tuning software
 * 
 * 
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute etc. this as long as the source code
 * is made available for FREE.
 * 
 * No warranty is made or implied. You use this program at your own risk.
 */

#include <config.h>
#include <debugging.h>
#include <defines.h>
#include <enums.h>
#include <firmware.h>
#include <ms2_menu_handlers.h>
#include <ms2_plugin.h>

extern gconstpointer *global_data;


G_MODULE_EXPORT void ecu_plugin_menu_setup(GladeXML *xml)
{
	Firmware_Details *firmware = NULL;
	GtkWidget *menu = NULL;
	GtkWidget *item = NULL;
	GtkWidget *image = NULL;

	firmware = DATA_GET(global_data,"firmware");

	gdk_threads_enter();
	if (firmware->capabilities & MS2)
	{
		menu = glade_xml_get_widget (xml, "tools_menu_menu");
		item = gtk_image_menu_item_new_with_mnemonic("Sensor _Calibration (MAP/Baro)");
		image = gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU);
		g_object_set(item,"image",image,NULL);
		if (gtk_minor_version >= 16)
			g_object_set(item,"always-show-image",TRUE,NULL);
		g_signal_connect(G_OBJECT(item),"activate",G_CALLBACK(show_sensor_calibrator_window),NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);

		item = gtk_image_menu_item_new_with_mnemonic("Calibrate Ther_mistor Tables");
		image = gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU);
		g_object_set(item,"image",image,NULL);
		if (gtk_minor_version >= 16)
			g_object_set(item,"always-show-image",TRUE,NULL);
		g_signal_connect(G_OBJECT(item),"activate",G_CALLBACK(show_table_generator_window),NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);

		item = gtk_image_menu_item_new_with_mnemonic("MS-2 _AFR Calibrator");
		image = gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU);
		g_object_set(item,"image",image,NULL);
		if (gtk_minor_version >= 16)
			g_object_set(item,"always-show-image",TRUE,NULL);
		g_signal_connect(G_OBJECT(item),"activate",G_CALLBACK(show_ms2_afr_calibrator_window),NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);

		item = gtk_image_menu_item_new_with_mnemonic("MS-2 _TPS Calibrator");
		image = gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU);
		g_object_set(item,"image",image,NULL);
		if (gtk_minor_version >= 16)
			g_object_set(item,"always-show-image",TRUE,NULL);
		g_signal_connect(G_OBJECT(item),"activate",G_CALLBACK(show_tps_calibrator_window),NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);

		item = gtk_image_menu_item_new_with_mnemonic("MS-2 Re-Init (WarmBoot)");
		image = gtk_image_new_from_stock("gtk-redo",GTK_ICON_SIZE_MENU);
		g_object_set(item,"image",image,NULL);
		if (gtk_minor_version >= 16)
			g_object_set(item,"always-show-image",TRUE,NULL);
		g_signal_connect(G_OBJECT(item),"activate",G_CALLBACK(ms2_reinit),NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);

		item = gtk_image_menu_item_new_with_mnemonic("MS-2 ReBoot (ColdBoot)");
		image = gtk_image_new_from_stock("gtk-refresh",GTK_ICON_SIZE_MENU);
		g_object_set(item,"image",image,NULL);
		if (gtk_minor_version >= 16)
			g_object_set(item,"always-show-image",TRUE,NULL);
		g_signal_connect(G_OBJECT(item),"activate",G_CALLBACK(ms2_reboot),NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu),item);
		gtk_widget_show_all(menu);
	}
	gdk_threads_leave();
	return;
}


/*!
   \brief General purpose handler to hide/show Sensor calibrate window
    */
G_MODULE_EXPORT gboolean show_table_generator_window(GtkWidget *widget, gpointer data)
{
	static GtkWidget *window = NULL;
	GtkWidget *item = NULL;
	GladeXML *main_xml = NULL;
	GladeXML *xml = NULL;
	Firmware_Details *firmware = NULL;

	firmware = DATA_GET(global_data,"firmware");
	main_xml = (GladeXML *)DATA_GET(global_data,"main_xml");
	if ((!main_xml) || (DATA_GET(global_data,"leaving")))
		return TRUE;

	if (!GTK_IS_WIDGET(window))
	{
		xml = glade_xml_new(main_xml->filename,"table_generator_window",NULL);
		window = glade_xml_get_widget(xml,"table_generator_window");
		glade_xml_signal_autoconnect(xml);

		item = glade_xml_get_widget(xml,"sensor_combo");
		gtk_combo_box_set_active(GTK_COMBO_BOX(item),0);
		register_widget_f("thermister_sensor_combo",item);
		item = glade_xml_get_widget(xml,"temp_label");
		OBJ_SET(item,"c_label",g_strdup("Temperature(\302\260 C)"));
		OBJ_SET(item,"f_label",g_strdup("Temperature(\302\260 F)"));
		register_widget_f("temp_label",item);
		if (firmware->capabilities & PIS)
			gtk_widget_destroy(glade_xml_get_widget(xml,"bias_resistor_table"));
		else
		{
			item = glade_xml_get_widget(xml,"bias_entry");
			register_widget_f("bias_entry",item);
			OBJ_SET(item,"raw_lower",g_strdup("0"));
			OBJ_SET(item,"raw_upper",g_strdup("100000"));
			OBJ_SET(item,"precision",GINT_TO_POINTER(1));
		}

		item = glade_xml_get_widget(xml,"temp1_entry");
		register_widget_f("temp1_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("-40"));
		OBJ_SET(item,"raw_upper",g_strdup("300"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"temp2_entry");
		register_widget_f("temp2_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("-40"));
		OBJ_SET(item,"raw_upper",g_strdup("300"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"temp3_entry");
		register_widget_f("temp3_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("-40"));
		OBJ_SET(item,"raw_upper",g_strdup("300"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"resistance1_entry");
		register_widget_f("resistance1_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("0"));
		OBJ_SET(item,"raw_upper",g_strdup("500000"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"resistance2_entry");
		register_widget_f("resistance2_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("0"));
		OBJ_SET(item,"raw_upper",g_strdup("500000"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"resistance3_entry");
		register_widget_f("resistance3_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("0"));
		OBJ_SET(item,"raw_upper",g_strdup("500000"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"celsius_radiobutton");
		register_widget_f("thermister_celsius_radiobutton",item);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(item),FALSE);
		g_signal_emit_by_name(item,"toggled",NULL);
		gtk_window_set_transient_for(GTK_WINDOW(window),GTK_WINDOW(lookup_widget_f("main_window")));
		gtk_widget_show_all(GTK_WIDGET(window));
		return TRUE;
	}
#if GTK_MINOR_VERSION >= 18
	if (gtk_widget_get_visible(GTK_WIDGET(window)))
#else
	if (GTK_WIDGET_VISIBLE(GTK_WIDGET(window)))
#endif
		gtk_widget_hide_all(GTK_WIDGET(window));
	else
		gtk_widget_show_all(GTK_WIDGET(window));
	return TRUE;
}


/*!
   \brief General purpose handler to hide/show Sensor calibrate window
    */
G_MODULE_EXPORT gboolean show_ms2_afr_calibrator_window(GtkWidget *widget, gpointer data)
{
	static GtkWidget *window = NULL;
	GtkWidget *item = NULL;
	GtkWidget *item2 = NULL;
	GladeXML *main_xml = NULL;
	GladeXML *xml = NULL;
	Firmware_Details *firmware = NULL;
	gboolean (*populate_afr_calibrator_combo_f)(GtkWidget *) = NULL;

	firmware = DATA_GET(global_data,"firmware");

	main_xml = (GladeXML *)DATA_GET(global_data,"main_xml");
	if ((!main_xml) || (DATA_GET(global_data,"leaving")))
		return TRUE;

	if (!GTK_IS_WIDGET(window))
	{
		xml = glade_xml_new(main_xml->filename,"ms2_afr_calibrator_window",NULL);
		window = glade_xml_get_widget(xml,"ms2_afr_calibrator_window");
		glade_xml_signal_autoconnect(xml);

		item = glade_xml_get_widget(xml,"ego_sensor_combo");
		register_widget_f("afr_calibrate_ego_sensor_combo",item);
		if (get_symbol_f("populate_afr_calibrator_combo",(void *)&populate_afr_calibrator_combo_f))
			populate_afr_calibrator_combo_f(item);
		item2 = glade_xml_get_widget(xml,"generic_wideband_frame");
		OBJ_SET(item,"generic_controls",item2);

		item = glade_xml_get_widget(xml,"voltage1_entry");
		register_widget_f("voltage1_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("0"));
		OBJ_SET(item,"raw_upper",g_strdup("5"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"voltage2_entry");
		register_widget_f("voltage2_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("0"));
		OBJ_SET(item,"raw_upper",g_strdup("5"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"afr1_entry");
		register_widget_f("afr1_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("0"));
		OBJ_SET(item,"raw_upper",g_strdup("99"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		item = glade_xml_get_widget(xml,"afr2_entry");
		register_widget_f("afr2_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("0"));
		OBJ_SET(item,"raw_upper",g_strdup("99"));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));

		gtk_window_set_transient_for(GTK_WINDOW(window),GTK_WINDOW(lookup_widget_f("main_window")));
		gtk_widget_show_all(GTK_WIDGET(window));
		return TRUE;
	}
#if GTK_MINOR_VERSION >= 18
	if (gtk_widget_get_visible(GTK_WIDGET(window)))
#else
	if (GTK_WIDGET_VISIBLE(GTK_WIDGET(window)))
#endif
		gtk_widget_hide_all(GTK_WIDGET(window));
	else
		gtk_widget_show_all(GTK_WIDGET(window));
	return TRUE;
}


/*!
   \brief General purpose handler to hide/show Sensor calibrate window
    */
G_MODULE_EXPORT gboolean show_sensor_calibrator_window(GtkWidget *widget, gpointer data)
{
	static GtkWidget *window = NULL;
	GtkWidget *item = NULL;
	GladeXML *main_xml = NULL;
	GladeXML *xml = NULL;
	Firmware_Details *firmware = NULL;
	GList ***ecu_widgets;
	void (*update_widget_f)(gpointer, gpointer) = NULL;

	if (!update_widget_f)
		get_symbol_f("update_widget",(void *)&update_widget_f);

	ecu_widgets = DATA_GET(global_data,"ecu_widgets");
	firmware = DATA_GET(global_data,"firmware");
	main_xml = (GladeXML *)DATA_GET(global_data,"main_xml");
	if ((!main_xml) || (DATA_GET(global_data,"leaving")))
		return TRUE;

	if (!GTK_IS_WIDGET(window))
	{
		xml = glade_xml_new(main_xml->filename,"sensor_calibration_window",NULL);
		window = glade_xml_get_widget(xml,"sensor_calibration_window");
		glade_xml_signal_autoconnect(xml);

		item = glade_xml_get_widget(xml,"map0_entry");
		register_widget_f("map0_entry",item);
		if (firmware->capabilities & PIS)
		{
			OBJ_SET(item,"raw_lower",g_strdup("0"));
			OBJ_SET(item,"raw_upper",g_strdup("600"));
			OBJ_SET(item,"page",GINT_TO_POINTER(0));
			OBJ_SET(item,"offset",GINT_TO_POINTER(2702));
			OBJ_SET(item,"size",GINT_TO_POINTER(MTX_U16));
			OBJ_SET(item,"dl_conv_expr",g_strdup("x/1"));
			OBJ_SET(item,"ul_conv_expr",g_strdup("x*1"));
			ecu_widgets[0][2702] = g_list_prepend(
					ecu_widgets[0][2702],
					(gpointer)item);
		}
		else
		{
			OBJ_SET(item,"raw_lower",g_strdup("-1"));
			OBJ_SET(item,"raw_upper",g_strdup("327"));
			OBJ_SET(item,"page",GINT_TO_POINTER(0));
			OBJ_SET(item,"offset",GINT_TO_POINTER(506));
			OBJ_SET(item,"precision",GINT_TO_POINTER(1));
			OBJ_SET(item,"size",GINT_TO_POINTER(MTX_S16));
			OBJ_SET(item,"dl_conv_expr",g_strdup("x*10"));
			OBJ_SET(item,"ul_conv_expr",g_strdup("x/10"));
			ecu_widgets[0][506] = g_list_prepend(
					ecu_widgets[0][506],
					(gpointer)item);
		}

		item = glade_xml_get_widget(xml,"map5_entry");
		register_widget_f("map5_entry",item);
		if (firmware->capabilities & PIS)
		{
			OBJ_SET(item,"raw_lower",g_strdup("0"));
			OBJ_SET(item,"raw_upper",g_strdup("600"));
			OBJ_SET(item,"page",GINT_TO_POINTER(0));
			OBJ_SET(item,"offset",GINT_TO_POINTER(2704));
			OBJ_SET(item,"size",GINT_TO_POINTER(MTX_U16));
			OBJ_SET(item,"dl_conv_expr",g_strdup("x/1"));
			OBJ_SET(item,"ul_conv_expr",g_strdup("x*1"));
			ecu_widgets[0][2704] = g_list_prepend(
					ecu_widgets[0][2704],
					(gpointer)item);
		}
		else
		{
			OBJ_SET(item,"raw_lower",g_strdup("-1"));
			OBJ_SET(item,"raw_upper",g_strdup("327"));
			OBJ_SET(item,"page",GINT_TO_POINTER(0));
			OBJ_SET(item,"offset",GINT_TO_POINTER(508));
			OBJ_SET(item,"precision",GINT_TO_POINTER(1));
			OBJ_SET(item,"size",GINT_TO_POINTER(MTX_S16));
			OBJ_SET(item,"dl_conv_expr",g_strdup("x*10"));
			OBJ_SET(item,"ul_conv_expr",g_strdup("x/10"));
			ecu_widgets[0][508] = g_list_prepend(
					ecu_widgets[0][508],
					(gpointer)item);
		}

		item = glade_xml_get_widget(xml,"baro0_entry");
		register_widget_f("baro0_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("-1"));
		OBJ_SET(item,"raw_upper",g_strdup("327"));
		OBJ_SET(item,"page",GINT_TO_POINTER(0));
		OBJ_SET(item,"offset",GINT_TO_POINTER(530));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));
		OBJ_SET(item,"size",GINT_TO_POINTER(MTX_S16));
		OBJ_SET(item,"dl_conv_expr",g_strdup("x*10"));
		OBJ_SET(item,"ul_conv_expr",g_strdup("x/10"));
		ecu_widgets[0][530] = g_list_prepend(
				ecu_widgets[0][530],
				(gpointer)item);

		if (firmware->capabilities & PIS)
			gtk_widget_destroy(item);

		item = glade_xml_get_widget(xml,"baro5_entry");
		register_widget_f("baro5_entry",item);
		OBJ_SET(item,"raw_lower",g_strdup("-1"));
		OBJ_SET(item,"raw_upper",g_strdup("327"));
		OBJ_SET(item,"page",GINT_TO_POINTER(0));
		OBJ_SET(item,"offset",GINT_TO_POINTER(532));
		OBJ_SET(item,"precision",GINT_TO_POINTER(1));
		OBJ_SET(item,"size",GINT_TO_POINTER(MTX_S16));
		OBJ_SET(item,"dl_conv_expr",g_strdup("x*10"));
		OBJ_SET(item,"ul_conv_expr",g_strdup("x/10"));
		ecu_widgets[0][532] = g_list_prepend(
				ecu_widgets[0][532],
				(gpointer)item);

		if (firmware->capabilities & PIS)
		{
			gtk_widget_destroy(item);
			g_list_foreach(ecu_widgets[0][2702],update_widget_f,NULL);
			g_list_foreach(ecu_widgets[0][2704],update_widget_f,NULL);
		}
		else
		{
			/* Force them to update */
			g_list_foreach(ecu_widgets[0][506],update_widget_f,NULL);
			g_list_foreach(ecu_widgets[0][508],update_widget_f,NULL);
			g_list_foreach(ecu_widgets[0][530],update_widget_f,NULL);
			g_list_foreach(ecu_widgets[0][532],update_widget_f,NULL);
		}

		item = glade_xml_get_widget(xml,"get_data_button");
		OBJ_SET(item,"handler",GINT_TO_POINTER(READ_VE_CONST));
		OBJ_SET(item,"bind_to_list",g_strdup("get_data_buttons"));

		item = glade_xml_get_widget(xml,"burn_data_button");
		OBJ_SET(item,"handler",GINT_TO_POINTER(BURN_MS_FLASH));
		OBJ_SET(item,"bind_to_list",g_strdup("burners"));
		bind_to_lists_f(item,"burners");
		gtk_window_set_transient_for(GTK_WINDOW(window),GTK_WINDOW(lookup_widget_f("main_window")));
		gtk_widget_show_all(GTK_WIDGET(window));

		return TRUE;
	}
#if GTK_MINOR_VERSION >= 18
	if (gtk_widget_get_visible(GTK_WIDGET(window)))
#else
	if (GTK_WIDGET_VISIBLE(GTK_WIDGET(window)))
#endif
		gtk_widget_hide_all(GTK_WIDGET(window));
	else
		gtk_widget_show_all(GTK_WIDGET(window));
	return TRUE;
}


G_MODULE_EXPORT gboolean show_sensor_calibration_help(GtkWidget *widhet, gpointer data)
{
	GtkWidget *window;
	GtkWidget *view;
	gchar * text = NULL;
	GtkTextBuffer *buffer;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	view = gtk_text_view_new ();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(view),FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view),FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(view),5);

	gtk_container_add(GTK_CONTAINER(window),view);
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

	text = g_strdup("MAP Sensor Calibration\n\nFor the      MPX4115   use   10.6 and        121.7\nMPX4250          10.0    260.0\nMPXH6300 1.1     315.5\nGM 3-BAR 1.1     315.5\nMPXH6400 3.5     416.5\n\n(GM 3-bar data from Dave Hartnell, http://www.not2fast.com/electronics/component_docs/MAP_12223861.pdf)\n\n    Sensor type     vLo     pLo     vHi     pHi     vRef\n  MPX4115         0.204 v 15 kPa  4.794 v 115 kPa 5.100 v\n       MPX4250         0.204 v 20 kPa  4.896 v 250 kPa 5.100 v\n       MPXH6300        0.306 v 20 kPa  4.913 v 304 kPa 5.100 v\n       GM 3-BAR        0.631 v 40 kPa  4.914 v 304 kPa 5.100 v\n       MPXH6400        0.200 v 20 kPa  4.800 v 400 kPa 5.000 v\n\nIn general, use values derived from these equations:\n\n     m = (pHi-pLo)/(vHi-vLo)\n       pv1 = pLo - m * vLo\n   pv2 = pv1 + m * vRef\n\nReferences:\n   http://www.freescale.com/files/sensors/doc/data_sheet/MPX4115A.pdf\n    http://www.freescale.com/files/sensors/doc/data_sheet/MPX4250A.pdf\n    http://www.freescale.com/files/sensors/doc/data_sheet/MPXH6300A.pdf\n   http://www.freescale.com/files/sensors/doc/data_sheet/MPXH6400A.pdf\n\nBarometer Sensor Calibration\n\nIf your system has an external barometer sensor, separate from the MAP sensor,\nthen use these values to calibrate it properly.  If you have a standard MS installation, then copy your MAP sensor values here.\n\nBarometric Correction Calibration\n\nCorrection for barometric effects is performed using the linear function below.\n\n      correction = correction_0 + (rate * barometer) / 100\n'At total vacuum' contains the total correction at a barometer reading of 0 kPa (you are on the moon).\nThe 'Rate' contains the percentage per 100 kPa to scale the barometer value.\nUsing the default values of 147 and -47, we see that for a barometer of 100 kPa,\nwe have 100% correction.\ncorrection = 147 + (-47*100) / 100 = 100%\n ");
	gtk_text_buffer_set_text (buffer, text, -1);


	g_free(text);
	gtk_window_set_transient_for(GTK_WINDOW(window),GTK_WINDOW(lookup_widget_f("main_window")));
	gtk_widget_show_all(window);


	return TRUE;
}



/*! \brief tell ms2 to reinitialize */
G_MODULE_EXPORT gboolean ms2_reinit(GtkWidget *widget, gpointer data)
{
	io_cmd_f("ms2_reinit",NULL);
	return TRUE;
}


/*! \brief tell ms2 to fully reboot */
G_MODULE_EXPORT gboolean ms2_reboot(GtkWidget *widget, gpointer data)
{
	io_cmd_f("ms2_reboot",NULL);
	return TRUE;
}
