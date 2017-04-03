//gcc test.c -rdynamic $(pkg-config --cflags --libs gtk+-3.0) -lm -Wall -o test

#include <gtk-3.0/gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"
#include <time.h>

funzione f, g, h;
GtkBuilder *builder;
GtkWidget *plot;
GtkTextBuffer *buffer;
GtkStatusbar *status;
extern int x, y;
double **f_array, **g_array, **h_array;
double *convoluzione;
stringa fs, gs, hs;
int mem;
int par, conv;
int f_alen, g_alen, h_alen;
clock_t t1, t2;
int fps;
GtkLabel *speed;


void convol();
void refresh_speed();

void on_convol_clicked (GtkButton *button, gpointer   user_data) {
	conv = 1;
	convol();
}

void on_window_destroy (GtkWidget *widget, gpointer user_data) { 
	//Termina il loop principale alla chiusura della finestra
	gtk_main_quit ();
}

void print(char *c) {
	//Inserisce la stringa c nel buffer, visualizzat
	gtk_text_buffer_insert_at_cursor(buffer, c, length(c));	
}

void refresh_status() {
	//Aggiorna la status bar col nuovo valore di RAM occupata
	char *RAM = (char *) calloc(32, 1);
	sprintf(RAM,"RAM OCCUPIED: %dB", mem);
	gtk_statusbar_push(status, 1, RAM);	
	free(RAM);
}

void CalcolaF() {
	//Aggiorna l'array di valori assunti da f(x)
	par = 0;
	int i;
	for (i = 0; i < f_alen; i++) { 
		//Libera la memoria occupata dal vecchio array
		mem -= sizeof(double)*840;
		free(f_array[i]);
	}
	mem -= sizeof(double *)*f_alen;
	free(f_array);
	//Alloca la nuova memoria
	if (!f->animata) {
		f_array = (double **) malloc(sizeof(double *));
		f_array[0] = (double *) malloc(840*sizeof(double));
		mem += 840*sizeof(double) + sizeof(double *);
		f_alen = 1;
	}
	else {
		f_array = (double **) malloc(840*sizeof(double *));
		for (i = 0; i < 840; i++) {
			f_array[i] = (double *) malloc(840*sizeof(double));		
			mem += 840*sizeof(double);
		}
		mem += 840*sizeof(double *);
		f_alen = 840;
	}
	double incr, val;
	incr = (2*x)/840.0;
	val = -x;
	double k = 644.0/(2*y);
	int m = 26+fs.len+10;
	char *c = (char *) calloc(m, sizeof(char));
	sprintf(c, "calculating %s from -%d to %d...",  fs.str, x, x);
	print(c); //Stampa nell'interfaccia il messaggio contenuto in c
	free(c);
	//Calcola i valori
	if (!f->animata) {
		for (i = 0; i < 840; i++) {
			f_array[0][i] = -k*Calcola(f, val, 0);
			val += incr;
		}
	}
	else {
		int j;
		double param = -x;
		for (i = 0; i < 840; i++) {
			for (j = 0; j < 840; j++) {
				f_array[i][j] = -k*Calcola(f, val, param);
				val += incr;
			}
			val = -x;
			param += incr;
		}
	}
	print(" done!\n");
}

void CalcolaG() {
	//Aggiorna l'array di valori assunti da g(x)
	par = 0;
	int i;
	for (i = 0; i < g_alen; i++) { 
		//Libera la memoria occupata dal vecchio array
		mem -= sizeof(double)*840;
		free(g_array[i]);
	}
	mem -= sizeof(g_array)*g_alen;
	free(g_array);
	//Alloca la nuova memoria
	if (!g->animata) {
		g_array = (double **) malloc(sizeof(double *));
		g_array[0] = (double *) malloc(840*sizeof(double));
		mem += 840*sizeof(double) + sizeof(double *);
		g_alen = 1;
	}
	else {
		g_array = (double **) malloc(840*sizeof(double *));
		for (i = 0; i < 840; i++) {
			g_array[i] = (double *) malloc(840*sizeof(double));
			mem += 840*sizeof(double);
		}
		mem += 840*sizeof(double *);
		g_alen = 840;
	}
	double incr, val;
	incr = (2*x)/840.0;
	val = -x;
	double k = 644.0/(2*y);
	int m = 26+gs.len+10;
	char *c = (char *) calloc(m, sizeof(char));
	sprintf(c, "calculating %s from -%d to %d...",  gs.str, x, x);
	print(c); //Stampa nell'interfaccia il messaggio contenuto in c
	free(c);
	//Calcola i valori
	if (!g->animata) {
		for (i = 0; i < 840; i++) {
			g_array[0][i] = -k*Calcola(g, val, 0);
			val += incr;
		}
	}
	else {
		int j;
		double param = -x;
		for (i = 0; i < 840; i++) {
			for (j = 0; j < 840; j++) {
				g_array[i][j] = -k*Calcola(g, val, param);
				val += incr;
			}
			val = -x;
			param += incr;
		}
	}
	print(" done!\n");
}

void CalcolaH() {
	//Aggiorna l'array di valori assunti da h(x)
	par = 0;
	int i;
	for (i = 0; i < h_alen; i++) { 
		//Libera la memoria occupata dal vecchio array
		mem -= sizeof(double)*840;
		free(h_array[i]);
	}
	mem -= sizeof(h_array)*h_alen;;
	free(h_array);
	//Alloca la nuova memoria
	if (!h->animata) {
		h_array = (double **) malloc(sizeof(double *));
		h_array[0] = (double *) malloc(840*sizeof(double));
		mem += 840*sizeof(double) + sizeof(double *);
		h_alen = 1;
	}
	else {
		h_array = (double **) malloc(840*sizeof(double *));
		for (i = 0; i < 840; i++) {
			h_array[i] = (double *) malloc(840*sizeof(double));
			mem += 840*sizeof(double);
		}
		mem += 840*sizeof(double *);
		h_alen = 840;
	}
	double incr, val;
	incr = (2*x)/840.0;
	val = -x;
	double k = 644.0/(2*y);
	int m = 26+hs.len+20;
	char *c = (char *) calloc(m, sizeof(char));
	sprintf(c, "calculating %s from -%d to %d...",  hs.str, x, x);
	print(c); //Stampa nell'interfaccia il messaggio contenuto in c
	free(c);
	//Calcola i valori
	if (!h->animata) {
		for (i = 0; i < 840; i++) {
			h_array[0][i] = -k*Calcola(h, val, 0);
			val += incr;
		}
	}
	else {
		int j;
		double param = -x;
		for (i = 0; i < 840; i++) {
			for (j = 0; j < 840; j++) {
				h_array[i][j] = -k*Calcola(h, val, param);
				val += incr;
			}
			val = -x;
			param += incr;
		}
	}
	print(" done!\n");
}

void on_done4_clicked (GtkButton *button, gpointer   user_data) {
	//Aggiorna l'intervallo di valori rappresentato dall'asse delle y e ricalcola le funzioni 
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "y_axis"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));
	y = (int) valueOf(new_string(a));
	CalcolaF();
	CalcolaG();
	CalcolaH();
	gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
}

void on_done5_clicked (GtkButton *button, gpointer   user_data) {
	//Aggiorna l'intervallo di valori rappresentato dall'asse delle x e ricalcola le funzioni 
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "x_axis"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));
	x = (int) valueOf(new_string(a));
	CalcolaF();
	CalcolaG();
	CalcolaH();
	gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
}

void on_done1_clicked (GtkButton *button, gpointer   user_data) {
	conv = 0;
	//Crea una nuova struttura f(x) dalla stringa inserita dall'utente
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "f"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));
	mem -= Memoria_occupata(fs);
	mem -= fs.len;
	fs = new_string(a);
	free(f);
	f = new_funzione(fs);
	mem += Memoria_occupata(fs);
	mem += fs.len;
	CalcolaF();
	refresh_status();
	if (f->animata && !conv) {
		for (par = 0; par < 840; par++) {
			t1 = clock();
			gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
			while (gtk_events_pending() == TRUE) {
				gtk_main_iteration_do(TRUE);
			}
			par++;
			t2 = clock();
			while ((difftime(t2, t1) / CLOCKS_PER_SEC) < 1.0/fps) {
				t2 = clock();
			}   
		}	
		par = 839;
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	}
	else {
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	}
}

void on_done2_clicked (GtkButton *button, gpointer   user_data) {
	conv = 0;
	//Crea una nuova struttura g(x) dalla stringa inserita dall'utente
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "g"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));
	mem -= Memoria_occupata(gs);
	mem -= gs.len;
	gs = new_string(a);
	free(g);
	g = new_funzione(gs);
	mem += Memoria_occupata(gs);
	mem += gs.len;
	CalcolaG();
	refresh_status();
	if (g->animata) {
		for (par = 0; par < 840; par++) {
			t1 = clock();
			gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
			while (gtk_events_pending() == TRUE) {
				gtk_main_iteration_do(TRUE);
			}
			par++;
			t2 = clock();
			while ((difftime(t2, t1) / CLOCKS_PER_SEC) < 1.0/fps) {
				t2 = clock();
			}   
		}
		par = 839;
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	}
	else {
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	}
}

void on_speed_up_clicked (GtkButton *button, gpointer   user_data) {
	fps+=10;
	refresh_speed();
}

void on_speed_down_clicked (GtkButton *button, gpointer   user_data) {
	fps-=10;
	refresh_speed();
}

void on_done3_clicked (GtkButton *button, gpointer   user_data) {
	conv = 0;
	//Crea una nuova struttura h(x) dalla stringa inserita dall'utente
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "h"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));
	mem -= Memoria_occupata(hs);
	mem -= hs.len;
	hs = new_string(a);
	free(h);
	h = new_funzione(hs);
	mem += Memoria_occupata(hs);
	mem += hs.len;
	CalcolaH();
	refresh_status();
	if (h->animata) {
		for (par = 0; par < 840; par++) {
			t1 = clock();
			gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
			while (gtk_events_pending() == TRUE) {
				gtk_main_iteration_do(TRUE);
			}
			par++;
			t2 = clock();
			while ((difftime(t2, t1) / CLOCKS_PER_SEC) < 1.0/fps) {
				t2 = clock();
			}    
		}	
		par = 839;
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	}
	else {
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	}
}

void assi_cartesiani(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
	//Rappresenta gli assi cartesiani e la griglia
	cairo_set_source_rgb (cr, 255, 255, 255);
	cairo_rectangle (cr, 0, 0, 850, 650);
	cairo_fill(cr);
	
	cairo_set_source_rgba (cr, 0, 0, 0, 0.3);
	int i, j;
	int c = 0, d = 0;
	//Linee orizzontali della griglia
	for (i = 0; i < 20; i++) {		
		cairo_move_to(cr, c, 0);
		cairo_line_to(cr, c, 644);
		c+=42;		
	}
	
	//Linee verticali della griglia
	for (j = 0; j <	14; j++) {
		cairo_move_to(cr, 0, d);
		cairo_line_to(cr, 840, d);
		d+=46;
	}
	
	cairo_set_line_width(cr, 1);
	cairo_stroke (cr);
	
	cairo_set_source_rgba (cr, 0, 0, 0, 0.1);
	c = 21;
	d = 23;
	for (i = 0; i < 20; i++) {		
		cairo_move_to(cr, c, 0);
		cairo_line_to(cr, c, 650);
		c+=42;		
	}
						  
	for (j = 0; j <	14; j++) {
		cairo_move_to(cr, 0, d);
		cairo_line_to(cr, 850, d);
		d+=46;
	}
	
	cairo_set_line_width(cr, 1);
	cairo_stroke (cr);	
	
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_move_to (cr, 0, 322);
	cairo_line_to (cr, 840, 322); //Asse x
	cairo_move_to (cr, 420, 0);
	cairo_line_to (cr, 420, 645); //Asse y
	
	cairo_set_line_width (cr, 2);		
	cairo_stroke (cr);	
}

gboolean draw (GtkWidget *widget, cairo_t *cr, gpointer user_data) {
	//Disegna le funzioni
	double k = 644.0/(2*y);
	assi_cartesiani(widget, cr, user_data);
	int i;
	
	if (!conv) {
		for (i = 1; i < 840; i++) {
			cairo_set_source_rgb (cr, 1, 0, 0);
			if (f->animata) {
				if (par < 840 && !isnan(f_array[par][i-1]) && !isnan(f_array[par][i]) && f_array[par][i-1]/k<=y*1000 && f_array[par][i]/k<=y*1000 && f_array[par][i-1]/k>=-y*1000 && f_array[par][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (f_array[par][i-1])+322);
					cairo_line_to (cr, i, (f_array[par][i])+322);
				}
			}
			else {
				if (!isnan(f_array[0][i-1]) && !isnan(f_array[0][i]) && f_array[0][i-1]/k<=y*1000 && f_array[0][i]/k<=y*1000 && f_array[0][i-1]/k>=-y*1000 && f_array[0][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (f_array[0][i-1])+322);
					cairo_line_to (cr, i, (f_array[0][i])+322);
				}	
			}
			cairo_set_line_width (cr, 2);		
			cairo_stroke (cr);

			cairo_set_source_rgb (cr, 0, 1, 0);
			if (g->animata) {
				if (!isnan(g_array[par][i]) && !isnan(g_array[par][i-1]) && g_array[par][i-1]/k<=y*1000 && g_array[par][i]/k<=y*1000 && g_array[par][i-1]/k>=-y*1000 && g_array[par][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (g_array[par][i-1])+322);
					cairo_line_to (cr, i, (g_array[par][i])+322);
				}
			}
			else {
				if (!isnan(g_array[0][i]) && !isnan(g_array[0][i-1]) && g_array[0][i-1]/k<=y*1000 && g_array[0][i]/k<=y*1000 && g_array[0][i-1]/k>=-y*1000 && g_array[0][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (g_array[0][i-1])+322);
					cairo_line_to (cr, i, (g_array[0][i])+322);
				}
			}
			cairo_set_line_width (cr, 2);		
			cairo_stroke (cr);

			cairo_set_source_rgb (cr, 0, 0, 1);
			if (h->animata) {
				if (!isnan(h_array[par][i]) && !isnan(h_array[par][i-1]) && h_array[par][i-1]/k<=y*1000 && h_array[par][i]/k<=y*1000 && h_array[par][i-1]/k>=-y*1000 && h_array[par][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (h_array[par][i-1])+322);
					cairo_line_to (cr, i, (h_array[par][i])+322);
				}
			}
			else {
				if (!isnan(h_array[0][i]) && !isnan(h_array[0][i-1]) && h_array[0][i-1]/k<=y*1000 && h_array[0][i]/k<=y*1000 && h_array[0][i-1]/k>=-y*1000 && h_array[0][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (h_array[0][i-1])+322);
					cairo_line_to (cr, i, (h_array[0][i])+322);
				}	
			}
			cairo_set_line_width (cr, 2);		
			cairo_stroke (cr);
		}
	}
	else {
		if (par > 0) {
			for (i = 1; i < 840; i++) {
				cairo_set_source_rgb (cr, 1, 0, 0);
				if (par < 840 && !isnan(f_array[par][i-1]) && !isnan(f_array[par][i]) && f_array[par][i-1]/k<=y*1000 && f_array[par][i]/k<=y*1000 && f_array[par][i-1]/k>=-y*1000 && f_array[par][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (f_array[par][i-1])+322);
					cairo_line_to (cr, i, (f_array[par][i])+322);
				}

				cairo_set_line_width (cr, 2);		
				cairo_stroke (cr);

				cairo_set_source_rgb (cr, 0, 1, 0);			

				if (!isnan(g_array[0][i]) && !isnan(g_array[0][i-1]) && g_array[0][i-1]/k<=y*1000 && g_array[0][i]/k<=y*1000 && g_array[0][i-1]/k>=-y*1000 && g_array[0][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (g_array[0][i-1])+322);
					cairo_line_to (cr, i, (g_array[0][i])+322);
				}

				cairo_set_line_width (cr, 2);		
				cairo_stroke (cr);

				cairo_set_source_rgb (cr, 0, 0, 1);
				cairo_set_line_width (cr, 2);
				if (i <= par) {
					cairo_move_to (cr, i-1, (convoluzione[i-1])+322);
					cairo_line_to (cr, i, (convoluzione[i])+322);
				}

				cairo_stroke (cr);
			}
		}
	}
	
	return TRUE;
}

void convol() {
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "f"));
	fs = aggiungipar(fs);
	fs = Pulisci(fs);
	gtk_entry_set_text(GTK_ENTRY(box), fs.str);
	f = new_funzione(fs);
	CalcolaF();
	
	double incr = (2*x)/840.0;
	int i;
	par = 0;
	for (i = 0; i < 840; i++) {		
		convoluzione[i] = -areatot(f_array[i], g_array[0], incr);
	}	
	
	for (par = 0; par < 840; par++) {
		t1 = clock();
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
		while (gtk_events_pending() == TRUE) {
			gtk_main_iteration_do(TRUE);
		}
		t2 = clock();
		while ((difftime(t2, t1) / CLOCKS_PER_SEC) < 1.0/fps) {
			t2 = clock();
		}  
	}
	par = 839;	
	
	for (i = 0; i < h_alen; i++) {
		mem -= 840*sizeof(double);
		free(h_array[i]);
	}
	h_alen = 0;
	mem -= h_alen*sizeof(double *);
	free(h_array);
	mem += sizeof(double *);
	h_array = (double **) malloc(sizeof(double *));
	mem += 840*sizeof(double);
	h_array[0] = (double *) malloc(840*sizeof(double));
	refresh_status();
	for (i = 0; i < 840; i++) {
		h_array[0][i] = convoluzione[i];	
	}
	gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	conv = 0;
}

void refresh_speed() {
	char *c = (char *) malloc(32);
	sprintf(c, "Speed: %d fps", fps);
	gtk_label_set_text(speed, c);
	free(c);
}

int main (int argc, char *argv[]) {
	fps = 120;
	conv = 0;
	convoluzione = (double *) malloc(840*sizeof(double));
	par = 0;
	x = 10;
	y = 7;
	stringa arg = new_string("0");
	fs = new_string(arg.str);
	hs = new_string(arg.str);
	gs = new_string(arg.str);
	f = new_funzione(arg);
	g = new_funzione(arg);
	h = new_funzione(arg);
	mem = 840*sizeof(double);
	f_array = (double **) calloc(840, sizeof(double *));
	f_array[0] = (double *) calloc(840, sizeof(double));
	mem += 840*sizeof(double) + 840*sizeof(double *);
	f_alen = 1;
	g_array = (double **) calloc(1, sizeof(double *));
	g_array[0] = (double *) calloc(840, sizeof(double));
	mem += 840*sizeof(double) + sizeof(double *);
	g_alen = 1;
	h_array = (double **) calloc(1, sizeof(double *));
	h_array[0] = (double *) calloc(840, sizeof(double));
	mem += 840*sizeof(double) + sizeof(double *);
	h_alen = 1;
	
	mem += 3 + 12 + 3*17;
	
    GtkWidget *window;	
    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "plotter.glade", NULL);
	
	speed = GTK_LABEL(GTK_WIDGET (gtk_builder_get_object (builder, "fps")));
	refresh_speed();
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
	plot = GTK_WIDGET (gtk_builder_get_object (builder, "plot"));
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtk_builder_get_object (builder, "log")));
	status = GTK_STATUSBAR(gtk_builder_get_object (builder, "status"));
	gtk_builder_connect_signals (builder, NULL);
	refresh_status();
	CalcolaF();
	CalcolaG();
	CalcolaH();
	
    gtk_widget_show_all (window);       
    gtk_main ();

    return 0;
}