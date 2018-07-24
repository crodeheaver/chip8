#include "include/app.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


App app;

void render_func(void)
{
    app.OnExecute();
}

int main()
{
    if(!app.OnInit()) {
       return -1;
    }

    #ifdef EMSCRIPTEN
    emscripten_set_main_loop(render_func, -1, 0);
    #else
    while(app.running)
    {
        app.OnExecute();
    }
    #endif
}
