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
#include <stdio.h>
#include <unistd.h>
#include <string.h>
/* DO NOT include defines.h, as protos.h already does... */
#include "protos.h"
#include "globals.h"
#include "runtime_gui.h"


struct v1_2_Runtime_Gui runtime_data;

int build_runtime(GtkWidget *parent_frame)
{
	GtkWidget *vbox;
	GtkWidget *frame;
	GtkWidget *label;
	GtkWidget *entry;
	GtkWidget *table;
	GtkWidget *sep;

	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(parent_frame),vbox);

	frame = gtk_frame_new("Real-Time Variables");
	gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,0);
	gtk_container_set_border_width(GTK_CONTAINER(frame), 5);

	table = gtk_table_new(3,5,FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table),5);
        gtk_table_set_col_spacings(GTK_TABLE(table),10);
        gtk_container_set_border_width (GTK_CONTAINER (table), 20);
	gtk_container_add(GTK_CONTAINER(frame),table);

	label = gtk_label_new("Seconds");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 0, 1, 0, 1,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("MAP (Kpa)");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 0, 1, 1, 2,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Temp (F)");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 0, 1, 2, 3,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Batt Voltage");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 0, 1, 3, 4,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Gamma");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 0, 1, 4, 5,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);


	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 0, 1,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.secl_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 1, 2,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.map_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 2, 3,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.clt_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 3, 4,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.batt_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 4, 5,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.gammae_ent = entry;/*copy pointer to struct for update */

	sep = gtk_vseparator_new();
        gtk_table_attach (GTK_TABLE (table), sep, 2, 3, 0, 5,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Barometer (Kpa)");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 3, 4, 0, 1,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Manifold Air Temp (F)");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 3, 4, 1, 2,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Throttle Pos (%)");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 3, 4, 2, 3,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("RPM");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 3, 4, 3, 4,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Pulse Width (ms)");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 3, 4, 4, 5,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 4, 5, 0, 1,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.baro_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 4, 5, 1, 2,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.mat_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 4, 5, 2, 3,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.tps_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 4, 5, 3, 4,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.rpm_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 4, 5, 4, 5,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.pw_ent = entry;/*copy pointer to struct for update */

	/* Corrections/Enrichments frame */

	frame = gtk_frame_new("Corrections/Enrichments (Percent)");
	gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,0);
	gtk_container_set_border_width(GTK_CONTAINER(frame), 5);

	table = gtk_table_new(3,5,FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table),5);
        gtk_table_set_col_spacings(GTK_TABLE(table),10);
        gtk_container_set_border_width (GTK_CONTAINER (table), 20);
	gtk_container_add(GTK_CONTAINER(frame),table);


	label = gtk_label_new("EGO");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 0, 1, 0, 1,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Barometer    ");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 0, 1, 1, 2,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);
	label = gtk_label_new("Warmup");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 0, 1, 2, 3,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 0, 1,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.egocorr_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 1, 2,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.barocorr_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 2, 3,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.warmcorr_ent = entry;/*copy pointer to struct for update */

	sep = gtk_vseparator_new();
        gtk_table_attach (GTK_TABLE (table), sep, 2, 3, 0, 3,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);

	label = gtk_label_new("Air Density");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 3, 4, 0, 1,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);
	label = gtk_label_new("Volumetric Efficiency");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 3, 4, 1, 2,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);
	label = gtk_label_new("Acceleration (ms)");
	gtk_misc_set_alignment(GTK_MISC(label),0.0,0.5);
	gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (GTK_TABLE (table), label, 3, 4, 2, 3,
                        (GtkAttachOptions) (GTK_FILL),
                        (GtkAttachOptions) (0), 0, 0);

	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry),5);
        gtk_entry_set_width_chars (GTK_ENTRY (entry), 5);
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 4, 5, 0, 1,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.aircorr_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry),5);
        gtk_entry_set_width_chars (GTK_ENTRY (entry), 5);
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 4, 5, 1, 2,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.vecurr_ent = entry;/*copy pointer to struct for update */

	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry),5);
        gtk_entry_set_width_chars (GTK_ENTRY (entry), 5);
	gtk_widget_set_size_request(entry,55,-1);
        gtk_table_attach (GTK_TABLE (table), entry, 4, 5, 2, 3,
                        (GtkAttachOptions) (GTK_EXPAND),
                        (GtkAttachOptions) (0), 0, 0);
	runtime_data.tpsaccel_ent = entry;/*copy pointer to struct for update */

	return TRUE;
}

void update_runtime_vars()
{
	char buff[10];
	struct ms_data_v1_and_v2 *current = &runtime;
	struct ms_data_v1_and_v2 *last = &runtime_last;
	/* test to see if data changed 
	 * Why bother wasting CPU to update the GUI when 
	 * you'd just print the same damn thing?
	 * Makes the code a little uglier, but the gui won't
	 * flicker the text widgets at high update rates
	 */

	gdk_threads_enter();
	if (current->secl != last->secl)
	{
		g_snprintf(buff,10,"%i",current->secl);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.secl_ent),buff);
	}
	if (current->map != last->map)
	{
		g_snprintf(buff,10,"%i",current->map);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.map_ent),buff);
	}
	if (current->clt != last->clt)
	{
		g_snprintf(buff,10,"%i",current->clt);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.clt_ent),buff);
	}
	if (current->batt != last->batt)
	{
		g_snprintf(buff,10,"%.2f",current->batt);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.batt_ent),buff);
	}
	if (current->gammae != last->gammae)
	{
		g_snprintf(buff,10,"%i",current->gammae);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.gammae_ent),buff);
	}
	if (current->baro != last->baro)
	{
		g_snprintf(buff,10,"%i",current->baro);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.baro_ent),buff);
	}
	if (current->mat != last->mat)
	{
		g_snprintf(buff,10,"%i",current->mat);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.mat_ent),buff);
	}
	if (current->tps != last->tps)
	{
		g_snprintf(buff,10,"%i",current->tps);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.tps_ent),buff);
	}
	if (current->rpm != last->rpm)
	{
		g_snprintf(buff,10,"%i",current->rpm);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.rpm_ent),buff);
	}
	if (current->pw != last->pw)
	{
		g_snprintf(buff,10,"%.1f",current->pw);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.pw_ent),buff);
	}
	if (current->egocorr != last->egocorr)
	{
		g_snprintf(buff,10,"%i",current->egocorr);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.egocorr_ent),buff);
	}
	if (current->barocorr != last->barocorr)
	{
		g_snprintf(buff,10,"%i",current->barocorr);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.barocorr_ent),buff);
	}
	if (current->warmcorr != last->warmcorr)
	{
		g_snprintf(buff,10,"%i",current->warmcorr);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.warmcorr_ent),buff);
	}
	if (current->aircorr != last->aircorr)
	{
		g_snprintf(buff,10,"%i",current->aircorr);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.aircorr_ent),buff);
	}
	if (current->vecurr != last->vecurr)
	{
		g_snprintf(buff,10,"%i",current->vecurr);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.vecurr_ent),buff);
	}
	if (current->tpsaccel != last->tpsaccel)
	{
		g_snprintf(buff,10,"%i",current->tpsaccel);
		gtk_entry_set_text(GTK_ENTRY(runtime_data.tpsaccel_ent),buff);
	}
	gdk_threads_leave();
}
	
