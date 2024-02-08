#ifndef DRAWBACKEND_H
#define DRAWBACKEND_H

#include <AbstractDrawBackend.h>
#include <Display/Backends/CLI/DisplayManager.h>

namespace Display{
    namespace CLI{
        class DrawBackend : public Abstraction::AbstractDrawBackend
        {
        public:
            DrawBackend();
            ~DrawBackend();
        private:
            DisplayManager *manager
        };

    }
}


#endif // DRAWBACKEND_H
