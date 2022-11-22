#include <SDL2/SDL.h>
#include <complex>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

class App {
    public:
    void run() {
        initSDL();
        mainLoop();
        cleanup();
    }

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int isInSet(std::complex<double> c) {
        std::complex<double> z(0, 0);
        for(int i = 0; i < 25; i++) {
            z = std::pow(z, 2) + c;
            if(std::norm(z) > 10) {
                return i;
            }
        }
        return 0;
    }
    void renderSet() {
        for(double x = 0.0; x < 1.0; x += 0.001) {
            for(double y = 0.0; y < 1.0; y += 0.001) {
                double pointX = std::lerp(-2.0, 1.3, x);
                double pointY = std::lerp(-1.3, 2.0, y);
                int iterations = isInSet(std::complex<double>(pointX, pointY));
                if(iterations == 0) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
                    SDL_RenderDrawPointF(renderer, x, y);
                }else {
                    
                    SDL_SetRenderDrawColor(renderer, 2 * iterations % 255, 3 * iterations % 255, 4 * iterations % 255, 0xff);
                    SDL_RenderDrawPointF(renderer, x, y);
                }
            }
        }
    }

    void initSDL() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderSetScale(renderer, WINDOW_WIDTH, WINDOW_WIDTH);
    }
    void mainLoop() {
        SDL_Event e;
        SDL_RenderClear(renderer);
        renderSet();
        SDL_RenderPresent(renderer);
        
        bool quit = false;
        while(!quit) {
            SDL_PollEvent(&e);
            quit = handleEvent(e);
        }
    }
    bool handleEvent(SDL_Event e) {
        bool ret = false;
        if(e.type == SDL_QUIT) {
            ret = true;
        }

        return ret;
    }
    void cleanup() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(int argc, char** argv) {
    App app;
    app.run();
    return 0;
}