/*
 * Copyright (C) 2006 by Dave J. Andruczyk <djandruczyk at yahoo dot com>
 *
 * MegaTunix stripchart widget
 * 
 * 
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute etc. this as long as the source code
 * is made available for FREE.
 * 
 * No warranty is made or implied. You use this program at your own risk.
 * This is a the PRIVATE implementation header file for INTERNAL functions
 * of the widget.  Public functions as well the the gauge structure are 
 * defined in the gauge.h header file
 *
 */

#ifndef __STRIPCHART_PRIVATE_H__
#define __STRIPCHART_PRIVATE_H__

#include <gtk/gtk.h>
#include <stripchart.h>

#define MTX_STRIPCHART_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), MTX_TYPE_STRIPCHART, MtxStripChartPrivate))

typedef struct _MtxStripChartPrivate      MtxStripChartPrivate;

struct _MtxStripChartPrivate
{
        GdkPixmap *pixmap;      /*! Update/backing pixmap */
        GdkPixmap *bg_pixmap;   /*! Static rarely changing pixmap */
	gfloat *current;	/*! Array of current values */
        gint w;                 /*! Width of full widget */
        gint h;                 /*! Height of full widget */
	gint num_traces;	/*! Number of active traces */
        gchar *value_font;      /*! Font string for value */
        gfloat value_font_scale;/*! Font scale */
        gchar *valname;         /*! Value text to the let of the number */
        cairo_t *cr;            /*! Cairo context,  not sure if this is good
                                   too hold onto or not */
        cairo_font_options_t * font_options;
        GdkGC * gc;             /*! Graphics Context for drawing */
        GdkColormap *colormap;  /*! Colormap for GC's */
        GdkColor colors[NUM_COLORS];

};


gboolean mtx_stripchart_configure (GtkWidget *, GdkEventConfigure *);
gboolean mtx_stripchart_expose (GtkWidget *, GdkEventExpose *);
/* Not needed yet
* gboolean mtx_stripchart_button_press (GtkWidget *,GdkEventButton *);
* gboolean mtx_stripchart_motion_event (GtkWidget *,GdkEventMotion *);
*/
void mtx_stripchart_size_request (GtkWidget *, GtkRequisition *);
void mtx_stripchart_class_init (MtxStripChartClass *class_name);
void mtx_stripchart_init (MtxStripChart *gauge);
gboolean mtx_stripchart_button_release (GtkWidget *,GdkEventButton *);
void generate_stripchart_background(MtxStripChart *);
void update_stripchart_position (MtxStripChart *);
void mtx_stripchart_init_colors(MtxStripChart *);
void mtx_stripchart_redraw (MtxStripChart *gauge);


#endif
