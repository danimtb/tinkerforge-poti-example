#include <iostream>
#include <string>

#include <CLI/CLI.hpp>
#include <fmt/core.h>

#include "ip_connection.h"
#include "bricklet_linear_poti_v2.h"

#define VERSION "0.0.0"


// Callback function for position callback
void cb_position(uint8_t position, void *user_data) {
    (void)user_data; // avoid unused parameter warning

    std::cout << fmt::format("Position: {pos}", fmt::arg("pos", position)) << std::endl;
}

int main(int argc, char** argv) {
    CLI::App app{"Tinkerforge poti example"};
    app.set_version_flag("-v,--version", std::string(VERSION));

    std::string host = "localhost";
    app.add_option("-j,--host", host, "Host address");
    int port = 4223;
    app.add_option("-p,--port", port, "Port address");
    std::string uid = "XYZ";
    app.add_option("uid", uid, "Device UID");

    CLI11_PARSE(app, argc, argv);
    std::cout << fmt::format("Connecting to device '{uid}' at {host}:{port}",
                             fmt::arg("uid", uid), fmt::arg("host", host), fmt::arg("port", port))
                             << std::endl;

    // Create IP connection
    IPConnection ipcon;
    ipcon_create(&ipcon);

    // Create device object
    LinearPotiV2 lp;
    linear_poti_v2_create(&lp, uid.c_str(), &ipcon);

    // Connect to brickd
    if(ipcon_connect(&ipcon, host.c_str(), port) < 0) {
        std::cout << "Could not connect" << std::endl;
        return 1;
    }
    // Don't use device before ipcon is connected
    std::cout << "Connected!" << std::endl;


    // Register position callback to function cb_position
    linear_poti_v2_register_callback(&lp,
                                     LINEAR_POTI_V2_CALLBACK_POSITION,
                                     (void (*)(void))cb_position,
                                     NULL);

    // Set period for position callback to 0.01s (10ms) without a threshold
    linear_poti_v2_set_position_callback_configuration(&lp, 10, true, 'x', 0, 0);

    printf("Press any key to exit\n");
    getchar();
    linear_poti_v2_destroy(&lp);
    ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
    return 0;
}
