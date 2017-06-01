#include <SDL2/SDL.h>
#include <assert.h>

#define LADO_QUADRADO1 50
#define LADO_QUADRADO2 30

#define VELOCIDADE_INICIAL_QUADRADO1 1
#define VELOCIDADE_INICIAL_QUADRADO2 2

#define X_INICIAL_QUADRADO1 300
#define Y_INICIAL_QUADRADO1 100
#define X_SOMA_MAXIMA_QUADRADO1 200
#define Y_SOMA_MAXIMA_QUADRADO1 200

#define X_INICIAL_QUADRADO2 250
#define Y_INICIAL_QUADRADO2 400
#define X_SOMA_MAXIMA_QUADRADO2 300
#define Y_SOMA_MAXIMA_QUADRADO2 300

void moveSentidoHorario(SDL_Rect* q, int velocidade, unsigned long long DT);
void moveSentidoAntiHorario(SDL_Rect* q, int velocidade, unsigned long long DT);

int main (int argc, char* args[])
{
    /* INITIALIZATION */

    int err = SDL_Init(SDL_INIT_EVERYTHING);
    assert(err == 0);

    SDL_Window* window = SDL_CreateWindow("Quadrados Animados",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            800, 800, SDL_WINDOW_SHOWN);
    assert(window != NULL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
    assert(renderer != NULL);

    SDL_Rect q1 = { X_INICIAL_QUADRADO1, Y_INICIAL_QUADRADO1, LADO_QUADRADO1, LADO_QUADRADO1 };
    SDL_Rect q2 = { X_INICIAL_QUADRADO2, Y_INICIAL_QUADRADO2, LADO_QUADRADO2, LADO_QUADRADO2 };
    SDL_Event e;

	int velocidadeQuadrado1 = VELOCIDADE_INICIAL_QUADRADO1, velocidadeQuadrado2 = VELOCIDADE_INICIAL_QUADRADO2;
	unsigned long long tempoAnterior = SDL_GetTicks(), DT = 0;

    /* EXECUTION */

    while (1)
    {
		SDL_PollEvent(&e);    
		DT = SDL_GetTicks() - tempoAnterior;
		tempoAnterior = SDL_GetTicks();

		if (e.type == SDL_QUIT) {
			break;
		} 
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_MouseButtonEvent* click = (SDL_MouseButtonEvent*) &e;
			if ((click->x > q1.x) && (click->x <= q1.x + LADO_QUADRADO1) 
				&& (click->y > q1.y) && (click->y <= q1.y + LADO_QUADRADO1)) {
				velocidadeQuadrado1 = 0;		
			}	
			else if ((click->x > q2.x) && (click->x <= q2.x + LADO_QUADRADO2) 
				&& (click->y > q2.y) && (click->y <= q2.y + LADO_QUADRADO2)) {
				velocidadeQuadrado2 = 0;	
			}	
		}

		if (velocidadeQuadrado1) {
			moveSentidoHorario(&q1, velocidadeQuadrado1, DT);
		}
		if (velocidadeQuadrado2) {
			moveSentidoAntiHorario(&q2, velocidadeQuadrado2, DT);
		}
	
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
        SDL_RenderFillRect(renderer, NULL);

        SDL_SetRenderDrawColor(renderer,0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(renderer, &q1);

        SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,0x00);
        SDL_RenderFillRect(renderer, &q2);

        SDL_RenderPresent(renderer);  
    }

    /* FINALIZATION */

    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}

void moveSentidoHorario(SDL_Rect* q, int velocidade, unsigned long long DT) {
	if (q->x < X_INICIAL_QUADRADO1 + X_SOMA_MAXIMA_QUADRADO1 && q->y == Y_INICIAL_QUADRADO1) { // direita
		q->x += DT * velocidade;
		if (q->x > X_INICIAL_QUADRADO1 + X_SOMA_MAXIMA_QUADRADO1){
			q->x = X_INICIAL_QUADRADO1 + X_SOMA_MAXIMA_QUADRADO1;
		}
	}
	else if (q->x == X_INICIAL_QUADRADO1 + X_SOMA_MAXIMA_QUADRADO1 && q->y < Y_INICIAL_QUADRADO1 + Y_SOMA_MAXIMA_QUADRADO1) { // baixo
		q->y += DT * velocidade;
		if (q->y > Y_INICIAL_QUADRADO1 + X_SOMA_MAXIMA_QUADRADO1){
			q->y = Y_INICIAL_QUADRADO1 + X_SOMA_MAXIMA_QUADRADO1;
		}
	}
	else if (q->x > X_INICIAL_QUADRADO1 && q->y == Y_INICIAL_QUADRADO1 + Y_SOMA_MAXIMA_QUADRADO1) { // esquerda
		q->x -= DT * velocidade;
		if (q->x < X_INICIAL_QUADRADO1){
			q->x = X_INICIAL_QUADRADO1;
		}
	}
	else if (q->x == X_INICIAL_QUADRADO1 && q->y > Y_INICIAL_QUADRADO1) { // cima
		q->y -= DT * velocidade;
		if (q->y < Y_INICIAL_QUADRADO1){
			q->y = Y_INICIAL_QUADRADO1;
		}
	}
}

void moveSentidoAntiHorario(SDL_Rect* q, int velocidade, unsigned long long DT) {
	if (q->x == X_INICIAL_QUADRADO2 && q->y < Y_INICIAL_QUADRADO2 + Y_SOMA_MAXIMA_QUADRADO2) { // baixo
		q->y += DT * velocidade;
		if (q->y > Y_INICIAL_QUADRADO2 + X_SOMA_MAXIMA_QUADRADO2){
			q->y = Y_INICIAL_QUADRADO2 + X_SOMA_MAXIMA_QUADRADO2;
		}
	}
	else if (q->x < X_INICIAL_QUADRADO2 + X_SOMA_MAXIMA_QUADRADO2 && q->y == Y_INICIAL_QUADRADO2 + Y_SOMA_MAXIMA_QUADRADO2) { // direita
		q->x += DT * velocidade;
		if (q->x > X_INICIAL_QUADRADO2 + X_SOMA_MAXIMA_QUADRADO2){
			q->x = X_INICIAL_QUADRADO2 + X_SOMA_MAXIMA_QUADRADO2;
		}
	}
	else if (q->x == X_INICIAL_QUADRADO2 + X_SOMA_MAXIMA_QUADRADO2 && q->y > Y_INICIAL_QUADRADO2) { // cima
		q->y -= DT * velocidade;
		if (q->y < Y_INICIAL_QUADRADO2){
			q->y = Y_INICIAL_QUADRADO2;
		}
	}
	else if (q->x > X_INICIAL_QUADRADO2 && q->y == Y_INICIAL_QUADRADO2) { // esquerda
		q->x -= DT * velocidade;
		if (q->x < X_INICIAL_QUADRADO2){
			q->x = X_INICIAL_QUADRADO2;
		}
	}

}
