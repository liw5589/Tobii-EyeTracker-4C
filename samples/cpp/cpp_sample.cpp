/*
COPYRIGHT 2018-2020  - PROPERTY OF TOBII AB
-------------------------------------
2018-2020 TOBII AB - KARLSROVAGEN 2D, DANDERYD 182 53, SWEDEN - All Rights Reserved.

NOTICE:  All information contained herein is, and remains, the property of Tobii AB and its suppliers, if any.
The intellectual and technical concepts contained herein are proprietary to Tobii AB and its suppliers and may be
covered by U.S.and Foreign Patents, patent applications, and are protected by trade secret or copyright law.
Dissemination of this information or reproduction of this material is strictly forbidden unless prior written
permission is obtained from Tobii AB.
*/

#include <iostream>
#include <interaction_lib/InteractionLib.h>
#include <interaction_lib/misc/InteractionLibPtr.h>

int main()
{
    // create the interaction library
    IL::UniqueInteractionLibPtr intlib(IL::CreateInteractionLib(IL::FieldOfUse::Interactive));

    // assume single screen with size 2560x1440 and use full screen (not window local) coordinates
    constexpr float width  = 2560.0f;
    constexpr float height = 1440.0f;
    constexpr float offset = 0.0f;

    intlib->CoordinateTransformAddOrUpdateDisplayArea(width, height);
    intlib->CoordinateTransformSetOriginOffset(offset, offset);

    // setup ids and rectangles that define the interactors we want to use (one in each corner of the screen),
    // then add them to the interaction library
    constexpr IL::InteractorId idA = 0;
    constexpr IL::InteractorId idB = 1;
    constexpr IL::InteractorId idC = 2;
    constexpr IL::InteractorId idD = 3;

    constexpr float size = 500.0f;
    constexpr IL::Rectangle rectA = {            0,             0, size, size };
    constexpr IL::Rectangle rectB = { width - size,             0, size, size };
    constexpr IL::Rectangle rectC = {            0, height - size, size, size };
    constexpr IL::Rectangle rectD = { width - size, height - size, size, size };

    constexpr float z = 0.0f;


    intlib->BeginInteractorUpdates();

    intlib->AddOrUpdateInteractor(idA, rectA, z);
    intlib->AddOrUpdateInteractor(idB, rectB, z);
    intlib->AddOrUpdateInteractor(idC, rectC, z);
    intlib->AddOrUpdateInteractor(idD, rectD, z);

    intlib->CommitInteractorUpdates();

    // this struct is used to maintain a focus count (see below)
    struct Focus
    {
        IL::InteractorId id    = IL::EmptyInteractorId();
        size_t           count = 0;
    };
    Focus focus;

    // subscribe to gaze focus events
    // print event data to std out when called and count the number of consecutive focus events
    intlib->SubscribeGazeFocusEvents([](IL::GazeFocusEvent evt, void* context)
    {
        Focus& focus = *static_cast<Focus*>(context);
        std::cout
            << "Interactor: " << evt.id
            << ", focused: " << std::boolalpha << evt.hasFocus
            << ", timestamp: " << evt.timestamp_us << " us"
            << "\n";

        if (evt.hasFocus)
        {
            focus.count = focus.id == evt.id ? focus.count + 1 : 1;
            focus.id = evt.id;
        }
    }, &focus);

    // setup and maintain device connection, wait for device data between events and 
    // update interaction library to trigger all callbacks
    // stop after 3 consecutive focus events on the same interactor
    std::cout << "Starting interaction library update loop.\n";

    constexpr size_t max_focus_count = 3;

    while (focus.count < max_focus_count)
    {
        intlib->WaitAndUpdate();
    }

    std::cout << "Interactor " << focus.id << " got focused " << focus.count << " times\n";
}
