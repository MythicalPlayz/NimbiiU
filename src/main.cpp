#include <SDL2/SDL.h>
#include "system/SDLSystem.h"
#include "gui/GuiFrame.h"
#include "gui/GuiButton.h"
#include "gui/GuiController.h"
#include "menu/MainWindow.h"
#include "menu/MainComponents.h"
#include "input/SDLController.h"
#include "input/SDLControllerMouse.h"
#include "input/ControllerManager.h"

#include <cstdio>
#include <fcntl.h>

#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>  
#include "resources/proc.hpp"



int main(int argc, char *args[]) {
    auto *system = new SDLSystem();

    ProcInit();
    WHBLogUdpInit();
    WHBLogCafeInit();


    auto * frame = new MainWindow(system->getWidth(), system->getHeight(), system->getRenderer());
    auto * frame2 = new MainComponents(system->getWidth(), system->getHeight(), system->getRenderer());
    auto * controllerM = new ControllerManager(system->getWidth(), system->getHeight());





      while (true) {
bool quit = false;
if(ProcIsRunning() == false){
           exit(0);
            break;
            quit = true;
       }
        // Prepare to process new events.
        controllerM->prepare();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            int32_t channel = -1;
            SDL_JoystickID jId = -1;
            if(e.type == SDL_JOYDEVICEADDED) {
                controllerM->attachJoystick(e.jdevice.which);
                continue;
            }else if(e.type ==  SDL_JOYDEVICEREMOVED) {
                auto j = SDL_JoystickFromInstanceID(e.jdevice.which);
                if (j) {
                    controllerM->detachJoystick(e.jdevice.which);
                    SDL_JoystickClose(j);
                    continue;
                }
            }else if (e.type == SDL_FINGERDOWN || e.type == SDL_FINGERUP || e.type == SDL_FINGERMOTION ||
                e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION){
                channel = GuiTrigger::CHANNEL_1;
            } else if (e.type == SDL_JOYAXISMOTION) {
                jId = e.jaxis.which;
            } else if (e.type == SDL_JOYHATMOTION) {
                jId = e.jhat.which;
            }else if (e.type == SDL_JOYBUTTONDOWN || e.type == SDL_JOYBUTTONUP) {
                jId = e.jbutton.which;
            } else if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
                break;
            }
            controllerM->processEvent(jId, channel, &e);
        }

        if(quit){ exit(0); break; }

        // Finish controller inputs
        controllerM->finish();

        // Update gui elements based on controller inputs
        controllerM->callPerController([frame](GuiController* controller) { frame->update(controller);});
        controllerM->callPerController([frame2](GuiController* controller) { frame2->update(controller);});
        frame->process();
        frame2->process();
        // clear the screen
        SDL_RenderClear(system->getRenderer()->getRenderer());

        frame->draw(system->getRenderer());

        frame->updateEffects();
        frame2->draw(system->getRenderer());

        frame2->updateEffects();
        
        // flip the backbuffer
        // this means that everything that we prepared behind the screens is actually shown
        SDL_RenderPresent(system->getRenderer()->getRenderer());
    }
    //Shutdown the program DOES WORK BUT ONLY WITH THE BUTTON RN
    delete frame;
    delete frame2;
    ProcShutdown();
    return 0;
}