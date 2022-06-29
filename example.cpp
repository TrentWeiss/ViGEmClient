//
// Windows basic types 'n' fun
//
#include <windows.h>

//
// Optional depending on your use case
//
#include <Xinput.h>

//
// The ViGEm API
//
#include <ViGEm/Client.h>

#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char** argv)
{
    const auto client = vigem_alloc();

    if (client == nullptr)
    {
        std::cerr << "Uh, not enough memory to do that?!" << std::endl;
        return -1;
    }
    const auto retval = vigem_connect(client);

    if (!VIGEM_SUCCESS(retval))
    {
        std::cerr << "ViGEm Bus connection failed with error code: 0x" << std::hex << retval << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Successfully connected to ViGEm bus"<<std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //
    // Allocate handle to identify new pad
    //
    const auto pad = vigem_target_x360_alloc();

    //
    // Add client to the bus, this equals a plug-in event
    //
    const auto pir = vigem_target_add(client, pad);

    //
    // Error handling
    //
    if (!VIGEM_SUCCESS(pir))
    {
        std::cerr << "Target plugin failed with error code: 0x" << std::hex << pir << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Added virtual Xbox 360 Controller"<<std::endl;
    }

    XUSB_REPORT out;

    //
    // The XINPUT_GAMEPAD structure is identical to the XUSB_REPORT structure
    // so we can simply take it "as-is" and cast it.
    //
    // Call this function on every input state change e.g. in a loop polling
    // another joystick or network device or thermometer or... you get the idea.
    //
    vigem_target_x360_update(client, pad, out);
    std::this_thread::sleep_for(std::chrono::seconds(1));



    //
    // We're done with this pad, free resources (this disconnects the virtual device)
    //
    vigem_target_remove(client, pad);
    vigem_target_free(pad);
}