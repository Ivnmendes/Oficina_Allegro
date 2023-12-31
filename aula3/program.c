
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h> // Novo include
#include <stdio.h>

#define TAMANHO_TELA_X 1368
#define TAMANHO_TELA_Y 768

int main(void) {
    // Variável representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    // Inicializamos a biblioteca
    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_mouse();

    font = al_create_builtin_font();
    fila_eventos = al_create_event_queue();

    janela = al_create_display(TAMANHO_TELA_X, TAMANHO_TELA_Y);

    //avisamos para a fila de eventos que vamos prestar atenção em eventos da tela
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    int rodando = 1, x = -100, y = TAMANHO_TELA_Y - TAMANHO_TELA_Y / 15, mouseX = 0, mouseY = 0;

    while (rodando) {

        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                rodando = 0;
            }

            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
                mouseX = evento.mouse.x;
                mouseY = evento.mouse.y;
            }

        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_filled_triangle(mouseX, mouseY, mouseX+100, mouseY+100, mouseX+100, mouseY, al_map_rgb(255,0,255));
        al_draw_filled_circle(mouseX+100, mouseY+30, 25, al_map_rgb(255,255,0));
        al_hide_mouse_cursor(janela);
        al_draw_text(font, al_map_rgb(255,255,255), x+=2, y--, ALLEGRO_ALIGN_LEFT, "BOTTOM TEXT");

        // if (x > TAMANHO_TELA_X)
        //     x = -100;
        if (y < 0) {
            x = -100;
            y = TAMANHO_TELA_Y - TAMANHO_TELA_Y / 15;
        }

        // atualiza tela
        al_flip_display();

    }


    // Finaliza a janela
    al_destroy_display(janela);

    return 0;
}