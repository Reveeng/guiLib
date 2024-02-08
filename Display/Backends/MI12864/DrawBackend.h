#ifndef DRAWBACKEND_H
#define DRAWBACKEND_H

#include <AbstractDrawBackend.h>
namespace Display{
    namespace MI12864{
        class DrawBackend : public Abstraction::AbstractDrawBackend
        {
        public:
            DrawBackend();
            ~DrawBackend();

            virtual void drawScene() override final;
        };
    }
}


#endif // DRAWBACKEND_H
